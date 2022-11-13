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

bool tools[12] = { true };

string toolsAbout[12] = {
    "Chiaveee",
    "Doggooo",
    "Panooo",
    "Se vogliooo",
    "?",
    "Mar-Anza",
    "1+1=2",
    "C++++",
    "WINBGIM.H",
    "ATOM",
    "UwU",
    ":))",
};



bool canMove(int playerX, int playerY, MAP map)
{
    return (!evaluateColOrMap(map.col[playerY - 1], playerX));
}



void clickOnWindow(int x, int y, sf::RenderWindow& window)
{
    // Toolbar.
    if (y >= 640 && y <= 640 + 64)
    {
        sf::Font font;
        font.loadFromFile(FONT);

        sf::Text text;
        text.setFont(font);
        text.setString(toolsAbout[(x / 64) - 1]);
        text.setCharacterSize(18);
        text.setPosition(16, 640 + 64 + 16);

        window.draw(text);
    }
}



void drawToolBar(sf::RenderWindow &window)
{
    sf::RectangleShape shape(sf::Vector2f(64.0F, 64.0F));

    for (int i = 0; i < 12; i++)
    {
        shape.setPosition(64 + i * 64, 640);

        if (i%2== 0)
            shape.setFillColor(sf::Color::Green);
        else
            shape.setFillColor(sf::Color::Magenta);

        window.draw(shape);
    }
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(896, 768), "Elon the Plumber");

    // Player    
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets\\elon.png");
    player.setTexture(playerTexture);

    int playerX = 2;
    int playerY = 3;

    player.setPosition(playerX * 64 + 64, playerY * 64 + 64);

    MAP defaultMap = generateDefaultMap();

    while (window.isOpen())
    {
        sf::Event event;

        drawMap(defaultMap, window);

        drawToolBar(window);

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
                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;

                clickOnWindow(x, y, window);
            }
            
            // Comandi Giocatore.
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    if (canMove(playerX, playerY - 1, defaultMap))
                        playerY -= 1;

                    break;

                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    if (canMove(playerX, playerY + 1, defaultMap))
                        playerY += 1;

                    break;

                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    if (canMove(playerX - 1, playerY, defaultMap))
                        playerX -= 1;

                    break;

                case sf::Keyboard::D:
                case sf::Keyboard::Right:
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
