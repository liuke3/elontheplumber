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

#define ALLAGATO            "assets\\allagato.png"

#define VALVOLA1            "assets\\valvola1.png"
#define VALVOLA2            "assets\\valvola2.png"
#define VASCA_OK            "assets\\vasca.png"
#define VASCA_ROTTO         "assets\\vasca_rotto.png"
#define CESSO_OK             "assets\\cesso.png"
#define CESSO_ROTTO         "assets\\cesso_rotto.png"
#define DOCCIA_OK           "assets\\doccia.png"
#define DOCCIA_ROTTO        "assets\\doccia_rotto.png"
#define BIDET_OK            "assets\\bidet.png"
#define BIDET_ROTTO         "assets\\bidet_rotto.png"
#define LAVANDINO_OK        "assets\\lavandino.png"
#define LAVANDINO_ROTTO     "assets\\lavandino_rotto.png"
#define PORTELLO_OK         "assets\\portello.png"
#define PORTELLO_ROTTO      "assets\\portello_rotto.png"

#define TEXTURE             "assets\\texture.png"

#define VALVOLA     1

#define CESSO       2
#define VASCA       3
#define DOCCIA      4
#define BIDET       5
#define LAVANDINO   6

#define PORTELLO    7

// Vasca Varianti Minigiochi.
#define VASCA_CHIAVE    20
#define VASCA_NASTRO    21
#define VASCA_MARTELLO  22

// Water Varianti Minigiochi.
#define CESSO_CHIAVE    30
#define CESSO_NASTRO    31
#define CESSO_MARTELLO  32

// Doccia Varianti Minigiochi.
#define DOCCIA_CHIAVE   40
#define DOCCIA_NASTRO   41
#define DOCCIA_MARTELLO 42

// Bidet Varianti Minigiochi.
#define BIDET_CHIAVE    50
#define BIDET_NASTRO    51
#define BIDET_MARTELLO  52

// Lavandino Varianti Minigiochi.
#define LAVANDINO_CHIAVE    60
#define LAVANDINO_NASTRO    61
#define LAVANDINO_MARTELLO  62

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



struct POINT
{
    int x;
    int y;

    POINT(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};



struct OBJ
{
    bool rotto = false;
    int type;
    int x;
    int y;

    OBJ(bool rotto, int type, int x, int y)
    {
        this->rotto = rotto;
        this->type = type;
        this->x = x;
        this->y = y;
    }
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
        new short[12] { 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        new short[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    };

    // nuova roba oggetti

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
    allagatoTexture.loadFromFile(ALLAGATO);
    allagato.setTexture(allagatoTexture);

    // Oggetto.
    sf::Sprite obj;
    sf::Texture objTexture;
    objTexture.loadFromFile(VALVOLA1);
    obj.setTexture(objTexture);

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

            obj.setPosition((x + 1) * 64, (y + 1) * 64);

            // Oggetti.
            switch (map.obj[y][x])
            {
            case VALVOLA:
                if (map.valvola)
                    objTexture.loadFromFile(VALVOLA1);
                else
                    objTexture.loadFromFile(VALVOLA2);

                obj.setTexture(objTexture);
                window.draw(obj);
                break;

            case CESSO:
                objTexture.loadFromFile(CESSO_OK);
                obj.setTexture(objTexture);
                window.draw(obj);
                break;

            case VASCA:
                //objTexture.loadFromFile(VASCA_OK);
                objTexture.loadFromFile(TEXTURE);
                obj.setTexture(objTexture);
                window.draw(obj);
                break;

            case DOCCIA:
                //objTexture.loadFromFile(DOCCIA_OK);
                objTexture.loadFromFile(TEXTURE);
                obj.setTexture(objTexture);
                window.draw(obj);
                break;

            case BIDET:
                //objTexture.loadFromFile(BIDET_OK);
                objTexture.loadFromFile(TEXTURE);
                obj.setTexture(objTexture);
                window.draw(obj);
                break;

            case LAVANDINO:
                objTexture.loadFromFile(BIDET_OK);
                obj.setTexture(objTexture);
                window.draw(obj);
                break;

            case PORTELLO:
                objTexture.loadFromFile(PORTELLO_ROTTO);
                obj.setTexture(objTexture);
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