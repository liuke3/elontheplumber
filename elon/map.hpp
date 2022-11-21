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

#define FONT                "assets\\font.ttf"

#define DEFAULT_PAVIMENTO   "assets\\pav1.png"
#define DEFAULT_MURO        "assets\\muro1.png"
#define DEFAULT_MUROBRUTTO  "assets\\murobrutto1.png"
#define DEFAULT_VUOTO       "assets\\vuoto1.png"

#define VALVOLA 1
#define WATER   2
#define VASCA   3
#define DOCCIA  4
#define BIDET   5

#define VASCA_CHIAVE    20
#define VASCA_NASTRO    21
#define VASCA_MARTELLO  22
#define WATER_CHIAVE    30
#define WATER_NASTRO    31
#define WATER_MARTELLO    31



struct MAP
{
    // Identificatio Mappa.
    int id;

    // FileName Pavimento.
    string pavimento;

    // FileName Muro.
    string muro;

    /*
        Collisioni Mappa
        ================

        Per Risparmiare Memoria si Utilizza
        il Contenuto Binario di un Unsigned:

        Esempio:

        1 => Muro (Non si pu� Camminare)
        0 => Pavimento (Si pu� Camminare)
    */
    unsigned* col = nullptr;

    /*
        Texture Mappa
        =============

        Per Risparmiare Memoria si Utilizza
        il Contenuto Binario di un Unsigned:

        Esempio:

        3 => Vuoto
        2 => Vuoto
        1 => Muro
        0 => Pavimento
    */
    unsigned* map = nullptr;

    // Oggetti Mappa.
    short** obj = nullptr;

    // Riparazioni Totali Mappa.
    int riparazioniTot = 0;

    // Riparazioni Effettuate Mappa.
    int riparazioni = 0;

    // Stato Valvola.
    // True     =>  Attivata.
    // False    =>  Non Attivata.
    bool valvola = false;

    // Stato Acqua.
    // True     =>  Attiva.
    // False    =>  Non Attiva.
    bool acqua = true;
};



//
//  Mappa.
//

// Mappa Corrente.
MAP currentMap;
// Indice Mappa Corrente.
int currentMapIndex = 0;



MAP generateDefaultMap()
{
    MAP t;

    // Imposto Identificatore Mappa.
    t.id = 0;
    // Imposto Pavimento.
    t.pavimento = DEFAULT_PAVIMENTO;
    // Imposto Muro.
    t.muro = DEFAULT_MURO;
    // Imposto Riparazioni Totali Mappa.
    t.riparazioniTot = 10;
    // Imposto Riparazioni Effettuate Mappa.
    t.riparazioni = 0;
    // Imposto Valvola.
    t.valvola = false;
    // Imposto Acqua
    t.acqua = true;

    // Imposto Collisioni.
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

    // Imposto Mappa.
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

    // Imposto Oggetti.
    t.obj = new short*[8] {
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 2, 0, 3, 0, 4, 0, 5, 0, 0, 1, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    };

    return t;
}


// Restituisco Valore Collisioni.
int evaluateCol(unsigned row, unsigned col)
{
    return (row >> col) & 1;
}


// Restituisco Valore Mappa.
int evaluateMap(unsigned row, unsigned col)
{
    return (row >> (col * 2)) & 3;
}

// Disegno Mappa.
void drawMap(MAP map, RenderWindow &window)
{
    stringstream ss;
    ss << "Livello " << map.id << " | Riparazioni: " << map.riparazioni << "/" << map.riparazioniTot;

    sf::Font font;
    font.loadFromFile(FONT);
    sf::Text text;
    text.setFont(font);
    text.setString(ss.str());
    text.setCharacterSize(18);
    text.setPosition(16, 12);

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
    sf::Sprite murobrutto;
    sf::Texture murobruttoTexture;

    // Vuoto.
    sf::RectangleShape vuoto;
    vuoto.setFillColor(sf::Color::Black);

    // Allagato.
    sf::Sprite allagato;
    sf::Texture allagatoTexture;
    allagatoTexture.loadFromFile("assets\\allagato.png");
    allagato.setTexture(allagatoTexture);

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

                if (map.acqua)
                {
                    allagato.setPosition((x + 1) * 64, (y + 1) * 64);
                    window.draw(allagato);
                }

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

            RectangleShape shape(sf::Vector2f(64.0F, 64.0F));
            shape.setPosition((x + 1) * 64, (y + 1) * 64);

            // Oggetti.
            switch (map.obj[y][x])
            {
            case VALVOLA:
                shape.setFillColor(sf::Color::Red);
                window.draw(shape);
                break;

            case WATER:
                shape.setFillColor(sf::Color::Green);
                window.draw(shape);
                break;

            case VASCA:
                shape.setFillColor(sf::Color::Magenta);
                window.draw(shape);
                break;

            case DOCCIA:
                shape.setFillColor(sf::Color::Blue);
                window.draw(shape);
                break;

            case BIDET:
                shape.setFillColor(sf::Color::Yellow);
                window.draw(shape);
                break;

            default:
                break;
            }
        }
    }

    window.draw(text);
}

/*
prossima roba:

controllare se oggetto ok per riparare
aumentare counter

fare mappe
ficcare oggetti vari nella mappe
*/