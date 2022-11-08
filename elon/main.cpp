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

#define DEFAULT_PAVIMENTO   "assets\\pav1.png"
#define DEFAULT_MURO        "assets\\muro1.png"

bool tools[104] = { true };

int main()
{
    sf::RenderWindow window(sf::VideoMode(896, 768), "Elon the Plumber");
    
    //
    //  Texture
    //

    // Pavimento.
    sf::Sprite pavimento;
    sf::Texture pavimentoTexture;
    pavimentoTexture.loadFromFile(DEFAULT_PAVIMENTO);
    pavimento.setTexture(pavimentoTexture);
    // Muro.
    sf::Sprite muro;
    sf::Texture muroTexture;
    muroTexture.loadFromFile(DEFAULT_MURO);
    muro.setTexture(muroTexture);

    //
    //  Player
    //
    
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets\\elon.png");
    player.setTexture(playerTexture);

    int playerX = 128;
    int playerY = 192;

    player.setPosition(playerX, playerY);

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

        sf::RectangleShape mario(sf::Vector2f(64, 64));

        // Disegno la Mappa.
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 12; x++)
            {
                pavimento.setPosition((x + 1) * 64, (y + 1) * 64);
                muro.setPosition((x + 1) * 64, (y + 1) * 64);

                switch (map[y][x])
                {
                case PAVIMENTO:
                    window.draw(pavimento);
                    break;

                case MURO:
                    window.draw(muro);
                    break;

                default:
                    break;
                }

                if (obj[y][x] != 0)
                {
                    mario.setFillColor(sf::Color::Red);
                    mario.setPosition((x + 1) * 64, (y + 1) * 64);
                    window.draw(mario);
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
