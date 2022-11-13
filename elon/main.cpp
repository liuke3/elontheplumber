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

bool tools[10] = { true };



bool canMove(int playerX, int playerY, MAP map)
{
    return (evaluateColOrMap(map.col[playerY + 1], playerX) == PAVIMENTO);
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(896, 768), "Elon the Plumber");

    // Player    
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets\\elon.png");
    player.setTexture(playerTexture);

    int playerX = 128;
    int playerY = 192;

    player.setPosition(playerX, playerY);

    MAP defaultMap = generateDefaultMap();

    while (window.isOpen())
    {
        sf::Event event;

        drawMap(defaultMap, window);

        window.draw(player);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Interazioni Oggetti.
            if (event.type == sf::Event::MouseButtonPressed)
            {
                /*
                int x = sf::Mouse::getPosition(window).x / 64;
                int y = sf::Mouse::getPosition(window).y / 64;

                if (obj[y][x] == 1)
                {
                    sf::Font textFont;
                    sf::Text text;
                    textFont.loadFromFile("assets\\font.ttf");
                    text.setFont(textFont);
                    text.setString("Obj");
                    text.setCharacterSize(16);
                    text.setFillColor(sf::Color::White);
                    text.setStyle(sf::Text::Bold);
                    text.setPosition(0, 0);
                    window.draw(text);
                }
                */
            }
            
            // Comandi Giocatore.
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    if (playerY - 64 >= 192)
                        playerY -= 64;

                    /*
                        Nuovo sistema movimento giocatore basato su collisioni mappa
                        e non su limiti preimpostati. va fixata playerX e player Y relativamente
                        alla startx draw della mappa e alla starty draw della mappa e poi siuuuuuum
                    
                    */

                    /*
                    if (canMove((playerX / 64), (playerY / 64) - 1, defaultMap))
                        playerY -= 64;
                    */
                    break;

                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    if (playerY < (int)window.getSize().y - 256 && evaluateColOrMap(playerY + 1, playerX))
                        playerY += 64;

                    /*
                    if (canMove((playerX / 64), (playerY / 64) + 1, defaultMap))
                        playerY += 64;
                    */
                    break;

                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    if (playerX - 64 >= 128 && evaluateColOrMap(playerY - 1, playerX))
                        playerX -= 64;

                    break;

                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    if (playerX < (int)window.getSize().x - 192 && evaluateColOrMap(playerY - 1, playerX))
                        playerX += 64;

                    break;

                default:
                    break;
                }

                player.setPosition(playerX, playerY);
            }
        }

        window.display();
    }

    return 0;
}
