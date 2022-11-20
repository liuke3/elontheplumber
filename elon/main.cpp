#include <SFML/Graphics.hpp>

#include "map.hpp"

using namespace std;




#define NORTH   0
#define SOUTH   1
#define RIGHT   2
#define LEFT    3



//
//  Variabili Globali
//

#pragma region Variabili Globali

//////////////////////////////////////////////////
//////////////////////////////////////////////////

// Stato Strumenti.
bool tools[4] = {
    true,
    true,
    true,
    true,
};

int selectedTool = 0;

// Descrizione Strumenti.
string toolsAbout[4] = {
    "Chiave Tedesca",
    "Nastro Adesivo",
    "Panno Magico",
    "Spugna Grossa alias spongebob",
};

#define CHIAVE 0
#define NASTRO 1
#define PANNO 2
#define SPUGNA 3

// Mappa Corrente.
MAP currentMap;

//////////////////////////////////////////////////
//////////////////////////////////////////////////

#pragma endregion



bool canMove(int playerX, int playerY, MAP map)
{
    return (!evaluateCol(map.col[playerY - 1], playerX));
}



void clickOnWindow(int x, int y, sf::RenderWindow& window)
{
    
}



bool hoToccatoOggetto(int playerX, int playerY, int dir, MAP map)
{
    // tocco fuori dalla mappa.
    if (playerY - 1 < 0 || playerY + 1 > 7 ||
        playerX - 1 < 0 || playerX + 1 > 11)
    {
        return false;
    }

    // spugnannn
    if (selectedTool == SPUGNA)
    {
        return true;
    }

    // controllo oggetto in direzione nord.
    if (dir == NORTH)
    {
        // diverso da 0 == oggetto
        if (map.obj[playerY - 1][playerX] != 0)
        {
            return true;
        }
    }

    // controllo oggetto in direzione nord.
    if (dir == SOUTH)
    {
        // diverso da 0 == oggetto
        if (map.obj[playerY + 1][playerX] != 0)
        {
            return true;
        }
    }

    // controllo oggetto in direzione nord.
    if (dir == LEFT)
    {
        // diverso da 0 == oggetto
        if (map.obj[playerY][playerX - 1] != 0)
        {
            return true;
        }
    }

    // controllo oggetto in direzione nord.
    if (dir == RIGHT)
    {
        // diverso da 0 == oggetto
        if (map.obj[playerY][playerX + 1] != 0)
        {
            return true;
        }
    }

    return false;
}


bool interagisci(int playerX, int playerY, int dir, MAP &map)
{
    if (playerY - 1 < 0 || playerY + 1 > 7 || playerX - 1 < 0 || playerX + 1 > 11)
        return false;

    if (dir == NORTH)
    {
        if (map.obj[playerY - 1][playerX] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    if (dir == SOUTH)
    {
        if (map.obj[playerY + 1][playerX] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    if (dir == LEFT)
    {
        if (map.obj[playerY][playerX - 1] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    if (dir == RIGHT)
    {
        if (map.obj[playerY][playerX + 1] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    if (selectedTool == SPUGNA)
    {
        if (map.valvola)
        {
            map.acqua = false;
        }
        else
        {
            cout << "chiudi prima la valvola!!!" << endl;
        }
    }

    return true;
}





string getToolAbout(int x, int y, sf::RenderWindow& window)
{
    // Descrizione Strumenti.
    if (y >= 640 && y <= 640 + 64)
        return toolsAbout[(x / 64) - 5];

    return "";
}



void drawToolBar(sf::RenderWindow &window)
{
    sf::RectangleShape shape(sf::Vector2f(64.0F, 64.0F));   
    sf::Color redondi(100, 100, 100, 100);
    shape.setFillColor(redondi);

    sf::Sprite Obj_exhibition;

    sf::Texture Obj_exhibition_texture;
    Obj_exhibition_texture.loadFromFile("assets\\object-touch.png");
    sf::Texture Obj_exhibition_selected_texture;
    Obj_exhibition_selected_texture.loadFromFile("assets\\object-touch-selected.png");



    sf::Font font;
    font.loadFromFile(FONT);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);


    for (int i = 0; i < 4; i++)
    {
        stringstream ss;

        // aggiungo testo allo stream
        ss << i + 1;
        // imposto coordinate testo.
        text.setPosition(64 + 256 + i * 64 + 32, 665);
        // imposto testo
        text.setString(ss.str());

        // sfondo corice
        shape.setPosition(64 + 256 + i * 64, 610);
        // disegno sfondo cornice
        window.draw(shape);
        // imposto coordinate cornice
        Obj_exhibition.setPosition(64 + 256 + i * 64, 610);

        // oggetto selezionato. (faccio bordo bello)
        if (i == selectedTool)
            Obj_exhibition.setTexture(Obj_exhibition_selected_texture);
        // altro oggetto (faccio bordo brutto)
        else
            Obj_exhibition.setTexture(Obj_exhibition_texture);

        // disegno casella.
        window.draw(Obj_exhibition);
        // disegno testo
        window.draw(text);
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(896, 800), "Elon the Plumber");

    // Player    
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets\\elon_def.png");
    player.setTexture(playerTexture);

    int playerX = 2;
    int playerY = 3;
    // direzione player. 
    int dir = 0;

    player.setPosition(playerX * 64 + 64, playerY * 64 + 64);



    MAP defaultMap = generateDefaultMap();


    //
    //  Coperture
    //

    sf::Sprite cop0;
    sf::Texture cop0_texture;
    cop0_texture.loadFromFile("assets\\copertura0.png");
    cop0.setTexture(cop0_texture);
    cop0.setPosition(0, 0);

    sf::Sprite cop1;
    sf::Texture cop1_texture;
    cop1_texture.loadFromFile("assets\\copertura1.png");
    cop1.setTexture(cop1_texture);
    cop1.setPosition(0, 700);



    //
    //  Wrench
    //
    
    sf::Sprite wrench;
    sf::Texture wrenchTexture;

    if (tools[0] == true)
		wrenchTexture.loadFromFile("assets\\wrench.png");
	else
		wrenchTexture.loadFromFile("assets\\wrench_discolored.png");

    wrench.setTexture(wrenchTexture);
	
    //
    //  Scotch
    //

    sf::Sprite scotch;
    sf::Texture scotchTexture;

    if (tools[1] == true)
        scotchTexture.loadFromFile("assets\\scotch.png");
    else
        scotchTexture.loadFromFile("assets\\scotch_discolored.png");

    scotch.setTexture(scotchTexture);
    
    //
    //  Panno
    //
    
    sf::Sprite panno;
    sf::Texture pannoTexture;

    if (tools[2] == true)
        pannoTexture.loadFromFile("assets\\panno.png");
    else
        pannoTexture.loadFromFile("assets\\panno_discolored.png");

    panno.setTexture(pannoTexture);
    
    //
    //  Spugna
    //

    sf::Sprite spongebob;
    sf::Texture spongebobTexture;

    if (tools[3] == true)
        spongebobTexture.loadFromFile("assets\\spongebob.png");
    else
        spongebobTexture.loadFromFile("assets\\spongebob_discolored.png");

    spongebob.setTexture(spongebobTexture);
	


    //
    //  Font Scritte
    //
	
    sf::Font font;
    font.loadFromFile(FONT);

    sf::Text text;
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(18);
    text.setPosition(32, 640 + 64 + 16);



    while (window.isOpen())
    {   
        sf::Event event;

        window.clear();

        // Coperture.
        window.draw(cop0);
        window.draw(cop1);

        // Mappa.
        drawMap(defaultMap, window);
        // ToolBar.
        drawToolBar(window);
		
        // Oggetti.
        wrench.setPosition(64 + 256+ 0 * 64, 610);
        scotch.setPosition(64 + 256 + 1 * 64, 610);
        panno.setPosition(64 + 256 + 2 * 64, 610);
        spongebob.setPosition(64 + 256 + 3 * 64, 610);
		window.draw(wrench);
		window.draw(scotch);
		window.draw(panno);
		window.draw(spongebob);
	
        //  Player.
        window.draw(player);
        // Testo.
        window.draw(text);

        while (window.pollEvent(event))
        {
            // Close.
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Interazioni Oggetti.
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;

                text.setString(getToolAbout(x,y,window));
            }
            
            // Comandi Giocatore.
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    //
                    //  MOVIMENTI
                    //

                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    playerTexture.loadFromFile("assets\\elon_w.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX, playerY - 1, defaultMap))
                        playerY -= 1;

                    dir = NORTH;

                    break;

                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    playerTexture.loadFromFile("assets\\elon_def.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX, playerY + 1, defaultMap))
                        playerY += 1;

                    dir = SOUTH;

                    break;

                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    playerTexture.loadFromFile("assets\\elon_a.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX - 1, playerY, defaultMap))
                        playerX -= 1;

                    dir = LEFT;

                    break;

                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    playerTexture.loadFromFile("assets\\elon_d.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX + 1, playerY, defaultMap))
                        playerX += 1;

                    dir = RIGHT;

                    break;

                    //
                    //  SELEZIONE INVENTARIO
                    //

                case sf::Keyboard::Num1:
                    selectedTool = 0;
                    break;

                case sf::Keyboard::Num2:
                    selectedTool = 1;
                    break;

                case sf::Keyboard::Num3:
                    selectedTool = 2;
                    break;

                case sf::Keyboard::Num4:
                    selectedTool = 3;
                    break;

                    //
                    //  INTERAZIONI AMBIENTALI
                    //

                case sf::Keyboard::E:
                case sf::Keyboard::Space:
                    if (hoToccatoOggetto(playerX, playerY, dir, defaultMap))
                    {
                        interagisci(playerX, playerY, dir, defaultMap);
                    }

                    break;

                default:
                    break;
                }

                player.setPosition(playerX * 64 + 64, playerY * 64 + 64);
            }
        }

        window.display();
    }

    return 0;
}
