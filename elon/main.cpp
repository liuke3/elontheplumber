#include <SFML/Graphics.hpp>

#include "map.hpp"

using namespace std;



/*
    Sotto barra dell'inventario

    col maouse si selezione l'oggetto attivo e quando ci si avvicina
    a una roba interagente se l'oggetto giusto è selezionato fai qualcosa
    struemnto colorate = true;
    strumento scolorato = false;

    selezionabile solo se true o colorato

    dietro ognis strumento una cornce

    angolo alto sinistra descrizione
    angolo alto destra livello
*/

bool tools[4] = { false, false, false, false };

string toolsAbout[4] = {
    "Chiave Tedesca",
    "Nastro Adesivo",
    "Panno Magico",
    "Spugna Grossa alias spongebob",
};



bool canMove(int playerX, int playerY, MAP map)
{
    return (!evaluateCol(map.col[playerY - 1], playerX));
}



void clickOnWindow(int x, int y, sf::RenderWindow& window)
{
    // Toolbar.
}


string getToolAbout(int x, int y, sf::RenderWindow& window)
{
    if (y >= 640 && y <= 640 + 64)
        return toolsAbout[(x / 64) - 5];

    return "";
}



void drawToolBar(sf::RenderWindow &window)
{
    sf::RectangleShape shape(sf::Vector2f(64.0F, 64.0F));
    sf::Sprite Obj_exhibition;
    sf::Texture Obj_exhibition_texture;
    Obj_exhibition_texture.loadFromFile("assets\\object-touch.png");
    Obj_exhibition.setTexture(Obj_exhibition_texture);

    for (int i = 0; i < 4; i++)
    {
        shape.setPosition(64 + 256 + i * 64, 640);
        Obj_exhibition.setPosition(64 + 256 + i * 64, 640);
        sf::Color redondi(100, 100, 100, 100);
        shape.setFillColor(redondi);
        window.draw(shape);
        window.draw(Obj_exhibition);
    }
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(896, 768), "Elon the Plumber");

    // Player    
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets\\elon_d_def.png");
    player.setTexture(playerTexture);

    int playerX = 2;
    int playerY = 3;

    player.setPosition(playerX * 64 + 64, playerY * 64 + 64);



    MAP defaultMap = generateDefaultMap();



    //
    //Tool bar
    //
    
    sf::Sprite wrench;
    sf::Texture wrenchTexture;
    if (tools[0] == true)
    {
		wrenchTexture.loadFromFile("assets\\wrench.png");
	}
	else
	{
		wrenchTexture.loadFromFile("assets\\wrench_discolored.png");
    }
    wrench.setTexture(wrenchTexture);
	
    sf::Sprite scotch;
    sf::Texture scotchTexture;
    if (tools[1] == true)
    {
        scotchTexture.loadFromFile("assets\\scotch.png");
    }
    else
    {
        scotchTexture.loadFromFile("assets\\scotch_discolored.png");
    }
    scotch.setTexture(scotchTexture);
    
    sf::Sprite panno;
    sf::Texture pannoTexture;
    if (tools[2] == true)
    {
        pannoTexture.loadFromFile("assets\\panno.png");
    }
    else
    {
        pannoTexture.loadFromFile("assets\\panno_discolored.png");
    }
    panno.setTexture(pannoTexture);
    
    sf::Sprite spongebob;
    sf::Texture spongebobTexture;
    if (tools[3] == true)
    {
        spongebobTexture.loadFromFile("assets\\spongebob.png");
    }
    else
    {
        spongebobTexture.loadFromFile("assets\\spongebob_discolored.png");
    }
    spongebob.setTexture(spongebobTexture);
	
    //
    //
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

        drawMap(defaultMap, window);
        drawToolBar(window);
		
        wrench.setPosition(64 + 256+ 0 * 64, 640);
        scotch.setPosition(64 + 256 + 1 * 64, 640);
        panno.setPosition(64 + 256 + 2 * 64, 640);
        spongebob.setPosition(64 + 256 + 3 * 64, 640);
		
		window.draw(wrench);
		window.draw(scotch);
		window.draw(panno);
		window.draw(spongebob);
		

        window.draw(player);
        window.draw(text);

        while (window.pollEvent(event))
        {
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
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    playerTexture.loadFromFile("assets\\elon_w.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX, playerY - 1, defaultMap))
                        playerY -= 1;

                    break;

                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    playerTexture.loadFromFile("assets\\elon_d_def.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX, playerY + 1, defaultMap))
                        playerY += 1;

                    break;

                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    playerTexture.loadFromFile("assets\\elon_a.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX - 1, playerY, defaultMap))
                        playerX -= 1;

                    break;

                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    playerTexture.loadFromFile("assets\\elon_d_def.png");
                    player.setTexture(playerTexture);

                    if (canMove(playerX + 1, playerY, defaultMap))
                        playerX += 1;

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
