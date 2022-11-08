#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;

#define PAVIMENTO   0
#define MURO        1

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

bool tools[104] = { true };

int main()
{
    sf::RenderWindow window(sf::VideoMode(896, 768), "Elon the Plumber");
    
    //
    //  Texture
    //

    sf::Sprite pavimento;
    sf::Texture pavimentoTexture;
    pavimentoTexture.loadFromFile("assets\\pav1.png");
    pavimento.setTexture(pavimentoTexture);

    //
    //  Player
    //
    
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets\\elon.png");
    player.setTexture(playerTexture);
    player.setPosition(128, 192);

    int playerX = 128;
    int playerY = 128;

    while (window.isOpen())
    {
        sf::Event event;

        // Collisioni Mappa.
        int col[8][12] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        };

        // Texture Mappa.
        int map[8][12] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        };

        // Oggetti Mappa.
        int obj[8][12] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        };

        sf::RectangleShape shape(sf::Vector2f(64, 64));

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 12; x++)
            {
                shape.setPosition((x + 1) * 64, (y + 1) * 64);
                pavimento.setPosition((x + 1) * 64, (y + 1) * 64);

                if (map[y][x] == 1)
                {
                    shape.setFillColor(sf::Color::Red);
                    window.draw(shape);
                }
                else
                {
                    window.draw(pavimento);
                }
            }
        }

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
                int x = sf::Mouse::getPosition(window).x / 64;
                int y = sf::Mouse::getPosition(window).y / 64;

                if (obj[y][x] == 1)
                {
                    sf::Font font;

                    font.loadFromFile("assets\\font.ttf");

                    sf::Text text;

                    // select the font
                    text.setFont(font); // font is a sf::Font

                    // set the string to display
                    text.setString("Hello world");

                    // set the character size
                    text.setCharacterSize(24); // in pixels, not points!

                    // set the color
                    text.setFillColor(sf::Color::Red);

                    // set the text style
                    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                    text.setPosition(0, 0);
                    window.draw(text);


                    cout << "Obj" << endl;
                }
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

                    break;

                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    if (playerY < (int)window.getSize().y - 256)
                        playerY += 64;

                    break;

                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    if (playerX - 64 >= 128)
                        playerX -= 64;

                    break;

                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    if (playerX < (int)window.getSize().x - 192)
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
