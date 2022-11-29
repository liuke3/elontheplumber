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
#define PORTA       3
#define VALVOLA     3
#define CESSO       4   // Nastro
#define VASCA       5   // Nastro
#define DOCCIA      6   // Martello
#define BIDET       7   // Martello
#define LAVANDINO   8   // Chiave
#define PORTELLO    9   // Chiave
#define PORTA_INTERACT 33

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

#define PORTA1              "assets\\porta1.png"
#define PORTA2              "assets\\porta2.png"

#define CASSETTO1_TEXTURE  "assets\\cassetto1.png"
#define CASSETTO2_TEXTURE  "assets\\cassetto2.png"
#define CASSETTO3_TEXTURE  "assets\\cassetto3.png"

#define CASSETTO1 40
#define CASSETTO2 41
#define CASSETTO3 42



#define SEVOGLIO    104





struct OBJ
{
    // Stato Oggetto.
    bool rotto = false;

    // Tipo Oggetto.
    int type;

    // Coordinata X.
    short x;
    
    // Coordinata Y.
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
int currentMapIndex = 6;





MAP map1 {
    1,
    "assets\\pav1.png",
    "assets\\muro1.png",
    new unsigned[8] {
        0b00000000000000000000111111111111,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000111111000001,
        0b00000000000000000000111111000001,
        0b00000000000000000000111111000001,
        0b00000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000010101010101010101010101,
        0b00000000010101010101010101010101,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000101010101010000000000011,
        0b00000000101010101010000000000001,
        0b00000000101010101010000000000001,
    },
    2,
    new OBJ[2] {
        OBJ{ true, PORTA_INTERACT, 0, 5},
        OBJ{ true, VALVOLA, 9, 1 },
    },
    1,
    0,
    false,
    true,
};


MAP map2{
    2,
    "assets\\pav2.png",
    "assets\\muro2.png",
    new unsigned[8] {
        0b000000000000000000000111111111111,
        0b000000000000000000000111110000101,
        0b000000000000000000000111110000001,
        0b000000000000000000000100000000001,
        0b000000000000000000000100000000001,
        0b000000000000000000000100000000001,
        0b000000000000000000000100000000001,
        0b000000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000101010101001010101010101,
        0b00000000101010101001010101010101,
        0b00000000010101010100000000000001,
        0b00000000010101010100000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000011,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
    },
    3,
    new OBJ[3] {
        OBJ{ true, PORTA_INTERACT, 0, 5},
        OBJ{ true, VALVOLA, 9, 3 },
        OBJ{ true, CESSO, 2, 2 },
    },
    2,
    0,
    false,
    true,
};



MAP map3{
    3,
    "assets\\pav3.png",
    "assets\\muro3.png",
    new unsigned[8] {
        0b00000000000000000000111111111111,
        0b00000000000000000000100000000001,
        0b00000000000000000000101000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000100011110001,
        0b00000000000000000000100011110101,
        0b00000000000000000000100011110001,
        0b00000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000010101010101010101010101,
        0b00000000010101010101010101110101,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000001010101000000001,
        0b00000000010000001010101000000001,
        0b00000000010000001010101000000001,
    },
    4,
    new OBJ[4] {
        OBJ{ true, PORTA_INTERACT, 2, 1},
        OBJ{ true, VALVOLA, 11, 5 },
        OBJ{ true, CESSO, 2, 6 },
        OBJ{ true, VASCA, 9, 3 },
    },
    3,
    0,
    false,
    true,
};



MAP map4{
    4,
    "assets\\pav4.png",
    "assets\\muro4.png",
    new unsigned[8] {
        0b00000000000000000000111111111111,
        0b00000000000000000000100000000001,
        0b00000000000000000000100001000001,
        0b00000000000000000000100011110001,
        0b00000000000000000000100000000001,
        0b00000000000000000000110000000111,
        0b00000000000000000000110000000011,
        0b00000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000010101010101010101010101,
        0b00000000010101010101010101010101,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000101110100000001,
        0b00000000010000000000000000000001,
        0b00000000100100000000000000000110,
        0b00000000100100000000000000000110,
    },
    5,
    new OBJ[5] {
        OBJ{ true, PORTA_INTERACT, 5, 4},
        OBJ{ true, VALVOLA, 0, 4 },
        OBJ{ true, CESSO, 2, 6 },
        OBJ{ true, VASCA, 6, 3 },
        OBJ{ true, DOCCIA, 10, 1 },
    },
    4,
    0,
    false,
    true,
};



MAP map5{
    5,
    "assets\\pav5.png",
    "assets\\muro5.png",
    new unsigned[8] {
        0b00000000000000000000111111111111,
        0b00000000000000000000100000010001,
        0b00000000000000000000100001000001,
        0b00000000000000000000100000000101,
        0b00000000000000000000100000000001,
        0b00000000000000000000110001111111,
        0b00000000000000000000100001111111,
        0b00000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000010101010101010101010101,
        0b00000000010101010101010101011101,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000010101010101010,
        0b00000000010000000010101010101010,
    },
    6,
    new OBJ[6] {
        OBJ{ true, PORTA_INTERACT, 1, 1 },
        OBJ{ true, VALVOLA, 8, 1 },
        OBJ{ true, CESSO, 2, 4 },
        OBJ{ true, VASCA, 4, 2 },
        OBJ{ true, DOCCIA, 6, 3 },
        OBJ{ true, BIDET, 10, 6 },
    },
    5,
    0,
    false,
    true,
};



MAP map6{
    6,
    "assets\\pav6.png",
    "assets\\muro6.png",
    new unsigned[8] {
        0b00000000000000000000111111111111,
        0b00000000000000000000111111110101,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000010101011010101001010101,
        0b00000000010101010101010101010101,
        0b00000000010000000101010100000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000011,
        0b00000000010000000000000000000001,
    },
    8,
    new OBJ[8] {
        OBJ{ true, PORTA_INTERACT, 0, 6 },
        OBJ{ true, VALVOLA, 11, 6 },
        OBJ{ true, CESSO, 8, 2 },
        OBJ{ true, CESSO, 9, 2 },
        OBJ{ true, CESSO, 10, 2 },
        OBJ{ true, BIDET, 1, 2 },
        OBJ{ true, BIDET, 2, 2 },
        OBJ{ true, BIDET, 3, 2 },
    },
    7,
    0,
    false,
    true,
};


MAP map7{
    7,
    "assets\\pav7.png",
    "assets\\muro7.png",
    new unsigned[8] {
        0b00000000000000000000111111111111,
        0b00000000000000000000100000010101,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000100010000001,
        0b00000000000000000000111111111111,
        0b00000000000000000000111111111111,
        0b00000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000010101010101010101010101,
        0b00000000010101010101010101010101,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000011,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000101010101010101010101010,
        0b00000000101010101010101010101010,
    },
    5,
    new OBJ[5] {
        OBJ{ true, PORTA_INTERACT, 0, 3},
        OBJ{ true, VALVOLA, 9, 1 },
        OBJ{ true, CESSO, 7, 5 },
        OBJ{ true, BIDET, 4, 2 },
        OBJ{ true, LAVANDINO, 2, 2 },
    },
    4,
    0,
    false,
    true,
};



MAP map8{
    8,
    "assets\\pav8.png",
    "assets\\muro8.png",
    new unsigned[8] {
        0b00000000000000000000111111111111,
        0b00000000000000000000100010010101,
        0b00000000000000000000100000000001,
        0b00000000000000000000100111010001,
        0b00000000000000000000100000000011,
        0b00000000000000000000100000000001,
        0b00000000000000000000100000000001,
        0b00000000000000000000111111111111,
    },
    new unsigned[8] {
        0b00000000010101010101010101010101,
        0b00000000010101010101010101010101,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000011101000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
        0b00000000010000000000000000000001,
    },
    8,
    new OBJ[8] {
        OBJ{ true, PORTA_INTERACT, 7, 4 },
        OBJ{ true, VALVOLA, 9, 1 },
        OBJ{ true, CESSO, 7, 2 },
        OBJ{ true, BIDET, 4, 2 },
        OBJ{ true, LAVANDINO, 2, 2 },
        OBJ{ true, DOCCIA, 1, 5 },
        OBJ{ true, PORTELLO, 11, 5 },
        OBJ{ true, VASCA, 4, 4 },
    },
    7,
    0,
    false,
    true,
};



MAP maps[8] {
    map1,
    map2,
    map3,
    map4,
    map5,
    map6,
    map7,
    map8,
};



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
    t.riparazioniTot = 1;
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
        12582913,  // 00000000 11000000 00000000 00000001
        4194305,   // 00000000 01000000 00000000 00000001
        4194305,   // 00000000 01000000 00000000 00000001
    };

    // Imposto Numero Oggetti.
    t.objCounter = 1;

    // Imposto Oggetti.
    t.obj = new OBJ[t.objCounter]{
        OBJ{ true, VALVOLA, 9, 1 },
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


int indexOggetto(short x, short y, MAP map)
{
    for (int i = 0; i < map.objCounter; i++)
        if (map.obj[i].x == x && map.obj[i].y == y)
            return i;

    return -1;
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

    // Porta.
    sf::Sprite porta;
    sf::Texture portaTexture;
    portaTexture.loadFromFile(PORTA1);
    porta.setTexture(portaTexture);

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

            case PORTA:
                muro.setPosition((x + 1) * 64, (y + 1) * 64);
                window.draw(muro);

                if (map.riparazioni == map.riparazioniTot)
                {
                    portaTexture.loadFromFile(PORTA2);
                    porta.setTexture(portaTexture);
                }
                else
                {
                    portaTexture.loadFromFile(PORTA1);
                    porta.setTexture(portaTexture);
                }

                porta.setPosition((x + 1) * 64, (y + 1) * 64);
                window.draw(porta);
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

            case CASSETTO1:
                objTexture.loadFromFile(CASSETTO1_TEXTURE);
                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case CASSETTO2:
                objTexture.loadFromFile(CASSETTO2_TEXTURE);
                obj.setTexture(objTexture, true);
                window.draw(obj);
                break;

            case CASSETTO3:
                objTexture.loadFromFile(CASSETTO3_TEXTURE);
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