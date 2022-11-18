#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;



#define PAVIMENTO   0
#define MURO        1
#define MUROBRUTTO  2
#define VUOTO       3

#define DEFAULT_PAVIMENTO   "assets\\pav1.png"
#define DEFAULT_MURO        "assets\\muro1.png"
#define DEFAULT_MUROBRUTTO  "assets\\murobrutto1.png"
#define DEFAULT_VUOTO       "assets\\vuoto1.png"

#define FONT        "assets\\font.ttf"



#define VALVOLA 0



struct MAP
{
    // Identificatio Mappa.
    int id;
    // FileName Pavimento.
    string pavimento;
    // FileName Muro.
    string muro;
    // Collisioni Mappa.
    unsigned* col = nullptr;
    // Texture Mappa.
    unsigned* map = nullptr;
    // Oggetti Mappa.
    short** obj = nullptr;
};



MAP maps[9];



MAP generateDefaultMap()
{
    MAP t;

    // Imposto Identificatore Mappa.
    t.id = 0;
    // Imposto Pavimento.
    t.pavimento = DEFAULT_PAVIMENTO;
    // Imposto Muro.
    t.muro = DEFAULT_MURO;

    /*
        Collisioni
        ==========

        Per Risparmiare Memoria si Utilizza
        il Contenuto Binario di un Unsigned:

        Esempio:

        1 => Muro (Non si pu� Camminare)
        0 => Pavimento (Si pu� Camminare)
    */

    t.col = new unsigned[8] {
        4095,   // 00000000 00000000 00001111 11111111
        2049,   // 00000000 00000000 00001000 00000001
        2049,   // 00000000 00000000 00001000 00000001
        2049,   // 00000000 00000000 00001000 00000001
        2049,   // 00000000 00000000 00001000 00000001
        2049,   // 00000000 00000000 00001000 00000001
        2049,   // 00000000 00000000 00001000 00000001
        4095,   // 00000000 00000000 00001111 11111111
    };

    /*
        Texture
        =======

        Per Risparmiare Memoria si Utilizza
        il Contenuto Binario di un Unsigned:

        Esempio:

        3 => Muro Sottile
        2 => Vuoto
        1 => Muro (Non si pu� Camminare)
        0 => Pavimento (Si pu� Camminare)
    */

    t.map = new unsigned[8] {
        5592405,   // 00000000 01010101 01010101 01010101
        5592405,   // 00000000 01010101 01010101 01010101
        4194305,   // 00000000 01000000 00000000 00000001
        4194305,   // 00000000 01000000 00000000 00000001
        4194305,   // 00000000 01000000 00000000 00000001
        4194305,   // 00000000 01000000 00000000 00000001
        4194305,   // 00000000 01000000 00000000 00000001
        4194305,   // 00000000 01000000 00000000 00000001
    };

    // Ogetti.
    t.obj = new short*[8] {
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    };

    return t;
}



int evaluateCol(unsigned row, unsigned col)
{
    return (row >> col) & 1;
}

int evaluateMap(unsigned row, unsigned col)
{
    return (row >> (col * 2)) & 3;
}



void drawMap(MAP map, RenderWindow &window)
{
    stringstream ss;
    ss << "Livello " << map.id;

    sf::Font font;
    font.loadFromFile(FONT);

    sf::Text text;
    text.setFont(font);
    text.setString(ss.str());
    text.setCharacterSize(24);
    text.setPosition(16, 16);

    // Pavimento.
    sf::Sprite pavimento;
    sf::Texture pavimentoTexture;
    pavimentoTexture.loadFromFile(map.pavimento);
    pavimento.setTexture(pavimentoTexture);

    // Muro.
    sf::Sprite muro;
    sf::Texture muroTexture;
    muroTexture.loadFromFile(map.muro);
    muro.setTexture(muroTexture);

    // Muro Brutto.
    sf::Sprite murobrutto:
    sf::Texture murobruttoTexture;

    // Vuoto.
    sf::RectangleShape vuoto;
    vuoto.setFillColor(sf::Color::Black);

    // Disegno la Mappa.
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 12; x++)
        {
            // Mappa.
            switch (evaluateMap(map.map[y], x))
            {
            case PAVIMENTO:
                pavimento.setPosition((x + 1) * 64, (y + 1) * 64);
                window.draw(pavimento);
                break;

            case MURO:
                muro.setPosition((x + 1) * 64, (y + 1) * 64);
                window.draw(muro);
                break;

            case MUROBRUTTO:

                break;

            case VUOTO:
                muro.setPosition((x + 1) * 64, (y + 1) * 64);
                window.draw(vuoto);
                break;

            default:
                break;
            }

            // Oggetti.

            /*
            if (map.obj[y][x] != 0)
            {
                // Oggetti.
            }
            */
        }
    }

    window.draw(text);
}
