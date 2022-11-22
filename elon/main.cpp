#include <SFML/Graphics.hpp>

#include "map.hpp"

using namespace std;
using namespace sf;

//
//  Direzioni Player
//

// Indentificativo Direzioni.
#define NORTH   0
#define SOUTH   1
#define RIGHT   2
#define LEFT    3



//
//  Strumenti Inventario
//

// Indetificativo Strumenti.
#define CHIAVE      0
#define NASTRO      1
#define MARTELLO    2
#define SPUGNA      3

// Stato Strumenti.
bool tools[4] = {
    true,
    true,
    true,
    true,
};

// Strumento Selezionato.
int selectedTool = 0;

// Descrizione Strumenti.
string toolsAbout[4] = {
    "Chiave Tedesca",
    "Nastro Adesivo",
    "Martello Magico",
    "Spugna Grossa",
};






MAP loadNextMap()
{
    MAP t;

    return t;
}

bool canMove(int playerX, int playerY, MAP map)
{
    return (!evaluateCol(map.col[playerY - 1], playerX));
}

bool hoToccatoOggetto(int playerX, int playerY, int dir, MAP map)
{
    // Controllo
    if (playerY - 1 < 0 || playerY + 1 > 7 ||
        playerX - 1 < 0 || playerX + 1 > 11)
        return false;

    // Spugna.
    if (selectedTool == SPUGNA)
        return true;

    // Nord.
    if (dir == NORTH)
        // 0 == No Oggetto.
        if (map.obj[playerY - 1][playerX] != 0)
            return true;

    // Sud.
    if (dir == SOUTH)
        // 0 == No Oggetto.
        if (map.obj[playerY + 1][playerX] != 0)
            return true;

    // Sinistra.
    if (dir == LEFT)
        // 0 == No Oggetto.
        if (map.obj[playerY][playerX - 1] != 0)
            return true;

    // Destra.
    if (dir == RIGHT)
        // 0 == No Oggetto.
        if (map.obj[playerY][playerX + 1] != 0)
            return true;

    return false;
}

bool interagisci(int playerX, int playerY, int dir, MAP &map)
{
    // Controllo
    if (playerY - 1 < 0 || playerY + 1 > 7 ||
        playerX - 1 < 0 || playerX + 1 > 11)
        return false;

    //
    //  Interazione Valvola
    //

    // Nord.
    if (dir == NORTH)
    {
        if (map.obj[playerY - 1][playerX] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    // Sud.
    if (dir == SOUTH)
    {
        if (map.obj[playerY + 1][playerX] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    // Sinsitra.
    if (dir == LEFT)
    {
        if (map.obj[playerY][playerX - 1] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    // Destra.
    if (dir == RIGHT)
    {
        if (map.obj[playerY][playerX + 1] == VALVOLA)
        {
            map.valvola = !map.valvola;
            return true;
        }
    }

    //
    //  Interazione Spugna.
    //

    if (selectedTool == SPUGNA)
    {
        if (map.valvola && map.acqua)
        {
            map.acqua = false;
            map.riparazioni++;
        }
    }

    return true;
}

string getAbout(int x, int y, MAP map, sf::RenderWindow& window)
{
    int rx = x / 64;
    int ry = y / 64;

    // Descrizione Strumenti.
    if (y >= 610 && y <= 610 + 64)
        return toolsAbout[rx - 5];

    // Descrizione Ambiente.
    if (x >= 64 && x <= 832 && y >= 64 && y <= 576)
    {
 
    }

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

    //
    //menu
    sf::Sprite menu;
    sf::Texture menuTexture;
    menuTexture.loadFromFile("assets\\menu.png");
    menu.setTexture(menuTexture);
    menu.setPosition(0, 30);
	
    bool game = false;

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        window.draw(menu);
		
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Calcolo Coordinata X Relativa.
                int x = sf::Mouse::getPosition(window).x;
                // Calcolo Coordinata Y Relativa.
                int y = sf::Mouse::getPosition(window).y;

                if (x >= 291 && x <= 584 && y <= 390 && y >= 290)
                {
                    game = true;
                    break;
                }
                else if (x >= 293 && x <= 587 && y >= 466 && y <= 540)
                {
                    cout << "tasti" << endl;
                    
                }
                else if (x >= 291 && x <= 584 && y >= 615 && y <= 710)
                {
                    return 0;
                }
            }
        }
		window.display();
        if (game == true) break;
    }
	//

    //
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
    //  MARTELLO
    //
    
    sf::Sprite MARTELL;
    sf::Texture MARTELLOTexture;

    if (tools[2] == true)
        MARTELLOTexture.loadFromFile("assets\\hammer.png");
    else
        MARTELLOTexture.loadFromFile("assets\\hammer_discolored.png");

    MARTELL.setTexture(MARTELLOTexture);
    
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
    text.setPosition(32, 720);



    while (window.isOpen())
    {   
        sf::Event event;

        window.clear();

        // Carico Prossima Mappa.
        if (defaultMap.riparazioni == defaultMap.riparazioniTot)
            defaultMap = loadNextMap();

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
        MARTELL.setPosition(64 + 256 + 2 * 64, 610);
        spongebob.setPosition(64 + 256 + 3 * 64, 610);
		window.draw(wrench);
		window.draw(scotch);
		window.draw(MARTELL);
		window.draw(spongebob);
	
        //  Player.
        window.draw(player);
        // Testo.
        window.draw(text);

        // Ciclo Messaggi Finestra.
        while (window.pollEvent(event))
        {
            //
            //  Chiusura Finestra.
            //

            if (event.type == sf::Event::Closed)
                window.close();

            //
            //  Input Mouse.
            //

            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Calcolo Coordinata X Relativa.
                int x = sf::Mouse::getPosition(window).x;
                // Calcolo Coordinata Y Relativa.
                int y = sf::Mouse::getPosition(window).y;

                text.setString(getAbout(x, y, defaultMap, window));
            }
            
            //
            //  Input Tastiera.
            //

            if (event.type == sf::Event::KeyPressed)
            {
                // Analisi Input.
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
                        interagisci(playerX, playerY, dir, defaultMap);

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
