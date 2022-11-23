#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

#define PAVIMENTO   0
#define MURO        1
#define VUOTO       2
#define VALVOLA     3
#define CESSO       4   // Nastro
#define VASCA       5   // Nastro
#define DOCCIA      6   // Martello
#define BIDET       7   // Martello
#define LAVANDINO   8   // Chiave
#define PORTELLO    9   // Chiave

#define FONT                "assets\\font.ttf"

#define DEFAULT_PAVIMENTO   "assets\\pav1.png"
#define DEFAULT_MURO        "assets\\muro1.png"
#define DEFAULT_MUROBRUTTO  "assets\\murobrutto1.png"
#define DEFAULT_VUOTO       "assets\\vuoto1.png"

#define ALLAGATO            "assets\\allagato.png"
#define TEXTURE             "assets\\texture.png"

#define VALVOLA1            "assets\\valvola1.png"
#define VALVOLA2            "assets\\valvola2.png"
#define VASCA_OK            "assets\\vasca.png"
#define VASCA_ROTTO         "assets\\vasca_rotto.png"
#define CESSO_OK            "assets\\cesso.png"
#define CESSO_ROTTO         "assets\\cesso_rotto.png"
#define DOCCIA_OK           "assets\\doccia.png"
#define DOCCIA_ROTTO        "assets\\doccia_rotto.png"
#define BIDET_OK            "assets\\bidet.png"
#define BIDET_ROTTO         "assets\\bidet_rotto.png"
#define LAVANDINO_OK        "assets\\lavandino.png"
#define LAVANDINO_ROTTO     "assets\\lavandino_rotto.png"
#define PORTELLO_OK         "assets\\portello.png"
#define PORTELLO_ROTTO      "assets\\portello_rotto.png"




#define SEVOGLIO    104





struct OBJ
{
    bool rotto = false;
    int type;
    short x;
    short y;
};



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

    // Numero Oggetti.
    int objCounter = 0;

    // Oggetti Mappa.
    OBJ* obj = nullptr;

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

    // Imposto Numero Oggetti.
    t.objCounter = 7;

    // Imposto Oggetti.
    t.obj = new OBJ[t.objCounter]{
        OBJ{ true, VALVOLA, 9, 1 },
        OBJ{ true, CESSO, 1, 2 },
        OBJ{ false, VASCA, 4, 2 },
        OBJ{ true, BIDET, 5, 6 },
        OBJ{ true, DOCCIA, 6, 6 },
        OBJ{ true, LAVANDINO, 2, 2},
        OBJ{ true, PORTELLO, 0, 4},
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


OBJ quiOggetto(short x, short y, MAP map)
{
    OBJ e{ false, -1, -1, -1 };

    for (int i = 0; i < map.objCounter; i++)
        if (map.obj[i].x == x && map.obj[i].y == y)
            return map.obj[i];

    return e;
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

    // Allagato.
    sf::Sprite allagato;
    sf::Texture allagatoTexture;
    allagatoTexture.loadFromFile(ALLAGATO);
    allagato.setTexture(allagatoTexture);

    // Oggetto.
    sf::Sprite obj;
    sf::Texture objTexture;
    objTexture.loadFromFile(VALVOLA1);
    obj.setTexture(objTexture);

    // Vuoto.
    sf::RectangleShape vuoto;
    sf::Color vuotoTexture;
    vuotoTexture = sf::Color::Black;
    vuoto.setFillColor(vuotoTexture);

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

            case VUOTO:
                vuoto.setPosition((x + 1) * 64, (y + 1) * 64);
                window.draw(vuoto);
                break;

            default:
                break;
            }
        }
    }

    // Disegno Oggetti.
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 12; x++)
        {
            obj.setPosition((x + 1) * 64, (y + 1) * 64);

            OBJ tempObj = quiOggetto(x, y, map);

            // Oggetti.
            switch (tempObj.type)
            {
            case VALVOLA:
                if (map.valvola)
                    objTexture.loadFromFile(VALVOLA1);
                else
                    objTexture.loadFromFile(VALVOLA2);

                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case CESSO:
                if (tempObj.rotto)
                    objTexture.loadFromFile(CESSO_ROTTO);
                else
                    objTexture.loadFromFile(CESSO_OK);

                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case VASCA:
                if (tempObj.rotto)
                    objTexture.loadFromFile(VASCA_ROTTO);
                else
                    objTexture.loadFromFile(VASCA_OK);

                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case DOCCIA:
                if (tempObj.rotto)
                    objTexture.loadFromFile(DOCCIA_ROTTO);
                else
                    objTexture.loadFromFile(DOCCIA_OK);

                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case BIDET:
                if (tempObj.rotto)
                    objTexture.loadFromFile(BIDET_ROTTO);
                else
                    objTexture.loadFromFile(BIDET_OK);

                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case LAVANDINO:
                if (tempObj.rotto)
                    objTexture.loadFromFile(LAVANDINO_ROTTO);
                else
                    objTexture.loadFromFile(LAVANDINO_OK);

                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case PORTELLO:
                if (tempObj.rotto)
                    objTexture.loadFromFile(PORTELLO_ROTTO);
                else
                    objTexture.loadFromFile(PORTELLO_OK);

                obj.setTexture(objTexture, true);
                window.draw(obj);
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