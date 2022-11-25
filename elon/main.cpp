#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.hpp"



/*

mettere roba finestra nel while

riparazione oggetti solo se valvola chiusa

fare finestra fine coso bella

"filmato introduttivo"

"filmato deintroduttivo"


*/



using namespace std;
using namespace sf;

//
//  Direzioni Player
//

// Indentificativo Direzioni.
#define NORTH   0
#define SOUTH   1
#define RIGHT   2
#define LEFT    3



//
//  Strumenti Inventario
//

// Indetificativo Strumenti.
#define SPUGNA      0
#define NASTRO      1
#define MARTELLO    2
#define CHIAVE      3

// Stato Strumenti.
bool tools[4] = {
    true,
    false,
    false,
    false,
};

// Strumento Selezionato.
int selectedTool = 0;

// Descrizione Strumenti.
string toolsAbout[4] = {
    "Spugna Grossa",
    "Nastro Adesivo",
    "Martello Magico",
    "Chiave Inglese",
};



//
//  Giocatore
//

// Coordinata X Player.
int playerX = 2;
// Coordinata Y Player.
int playerY = 3;
// Direzione Player. 
int dir = 0;




MAP loadNextMap(RenderWindow &wd)
{
    MAP t;

    currentMapIndex++;




    switch (currentMapIndex)
    {
    case 1:
        tools[SPUGNA] = true;
        break;

    case 2:
        tools[NASTRO] = true;
        break;

    case 4:
        tools[MARTELLO] = true;
        break;
    
    case 6:
        tools[CHIAVE] = true;
        break;

    default:
        break;
    }

    cout << "LIVELLO COMPLETATO!" << endl;

    bool continue_ = true;

    while (wd.isOpen())
    {
        sf::Event event;

        wd.clear();

        sf::Font font;
        font.loadFromFile(FONT);
        sf::Text text;
        text.setFont(font);
        text.setString("Livello Completato");
        text.setCharacterSize(18);
        text.setPosition(0, 0);

        wd.draw(text);

        text.setPosition(0, 24);

        while (wd.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                continue_ = false;
            }
        }

        wd.display();

        if (!continue_)
            break;
    }

    if (currentMapIndex > 9)
        return generateDefaultMap();
    else
        return generateDefaultMap();
}



//
//  Minigiochi
//

void nastroGame(OBJ obj, Window &wd)
{
    if (!obj.rotto)
        return;

    cout << "Nastro Game" << endl;

    return;
}

void martelloGame(OBJ obj, Window& wd)
{
    if (!obj.rotto)
        return;

    cout << "Martello Game" << endl;

    return;
}

void chiaveGame(OBJ obj, Window& wd)
{
    if (!obj.rotto)
        return;

    cout << "Chiave Game" << endl;

    return;
}



bool canMove(int playerX, int playerY, MAP map)
{
    return (!evaluateCol(map.col[playerY - 1], playerX));
}



bool hoToccatoOggetto(int playerX, int playerY, int dir, MAP map)
{
    // Controllo.
    if (playerY - 1 < 0 || playerY + 1 > 7 ||
        playerX - 1 < 0 || playerX + 1 > 11)
        return false;

    // Spugna.
    if (selectedTool == SPUGNA)
        return true;

    // Nord.
    if (dir == NORTH)
        // 0 == No Oggetto.
        if (quiOggetto(playerX, playerY - 1, map).type >= 0)
            return true;

    // Sud.
    if (dir == SOUTH)
        // 0 == No Oggetto.
        if (quiOggetto(playerX, playerY + 1, map).type >= 0)
            return true;

    // Sinistra.
    if (dir == LEFT)
        // 0 == No Oggetto.
        if (quiOggetto(playerX - 1, playerY, map).type >= 0)
            return true;

    // Destra.
    if (dir == RIGHT)
        // 0 == No Oggetto.
        if (quiOggetto(playerX + 1, playerY, map).type >= 0)
            return true;

    return false;
}

bool interagisci(int playerX, int playerY, int dir, MAP &map, Window &wd)
{
    // Controllo.
    if (playerY - 1 < 0 || playerY + 1 > 7 ||
        playerX - 1 < 0 || playerX + 1 > 11)
        return false;

    // Nord.
    if (dir == NORTH)
    {
        // Valvola.
        if (quiOggetto(playerX, playerY - 1, map).type == VALVOLA)
            if (!map.valvola)
            {
                map.valvola = true;
                return true;
            }

        // Nastro.
        if (selectedTool == NASTRO && (quiOggetto(playerX, playerY - 1, map).type == CESSO ||
            quiOggetto(playerX, playerY - 1, map).type == VASCA))
        {
            nastroGame(quiOggetto(playerX, playerY - 1, map), wd);
            map.obj[indexOggetto(playerX, playerY - 1, map)].rotto = false;
            map.riparazioni++;
        }

        // Martello.
        if (selectedTool == MARTELLO && (quiOggetto(playerX, playerY - 1, map).type == DOCCIA ||
            quiOggetto(playerX, playerY - 1, map).type == BIDET))
        {
            martelloGame(quiOggetto(playerX, playerY - 1, map), wd);
            map.obj[indexOggetto(playerX, playerY - 1, map)].rotto = false;
            map.riparazioni++;
        }

        // Chiave.
        if (selectedTool == CHIAVE && (quiOggetto(playerX, playerY - 1, map).type == LAVANDINO ||
            quiOggetto(playerX, playerY - 1, map).type == PORTELLO))
        {
            chiaveGame(quiOggetto(playerX, playerY - 1, map), wd);
            map.obj[indexOggetto(playerX, playerY - 1, map)].rotto = false;
            map.riparazioni++;
        }
    }

    // Sud.
    if (dir == SOUTH)
    {
        // Valvola.
        if (quiOggetto(playerX, playerY + 1, map).type == VALVOLA)
            if (!map.valvola)
            {
                map.valvola = true;
                return true;
            }

        // Nastro.
        if (selectedTool == NASTRO && (quiOggetto(playerX, playerY + 1, map).type == CESSO ||
            quiOggetto(playerX, playerY + 1, map).type == VASCA))
        {
            nastroGame(quiOggetto(playerX, playerY + 1, map), wd);
            map.obj[indexOggetto(playerX, playerY + 1, map)].rotto = false;
            map.riparazioni++;
        }

        // Martello.
        if (selectedTool == MARTELLO && (quiOggetto(playerX, playerY + 1, map).type == DOCCIA ||
            quiOggetto(playerX, playerY + 1, map).type == BIDET))
        {
            martelloGame(quiOggetto(playerX, playerY + 1, map), wd);
            map.obj[indexOggetto(playerX, playerY + 1, map)].rotto = false;
            map.riparazioni++;
        }

        // Chiave.
        if (selectedTool == CHIAVE && (quiOggetto(playerX, playerY + 1, map).type == LAVANDINO ||
            quiOggetto(playerX, playerY + 1, map).type == PORTELLO))
        {
            chiaveGame(quiOggetto(playerX, playerY + 1, map), wd);
            map.obj[indexOggetto(playerX, playerY + 1, map)].rotto = false;
            map.riparazioni++;
        }
    }

    // Sinsitra.
    if (dir == LEFT)
    {
        // Valvola.
        if (quiOggetto(playerX - 1, playerY, map).type == VALVOLA)
            if (!map.valvola)
            {
                map.valvola = true;
                return true;
            }

        // Nastro.
        if (selectedTool == NASTRO && (quiOggetto(playerX - 1, playerY, map).type == CESSO ||
            quiOggetto(playerX - 1, playerY, map).type == VASCA))
        {
            nastroGame(quiOggetto(playerX - 1, playerY , map), wd);
            map.obj[indexOggetto(playerX - 1, playerY, map)].rotto = false;
            map.riparazioni++;
        }

        // Martello.
        if (selectedTool == MARTELLO && (quiOggetto(playerX - 1, playerY, map).type == DOCCIA ||
            quiOggetto(playerX - 1, playerY, map).type == BIDET))
        {
            martelloGame(quiOggetto(playerX - 1, playerY, map), wd);
            map.obj[indexOggetto(playerX - 1, playerY, map)].rotto = false;
            map.riparazioni++;
        }

        // Chiave.
        if (selectedTool == CHIAVE && (quiOggetto(playerX - 1, playerY, map).type == LAVANDINO ||
            quiOggetto(playerX - 1, playerY, map).type == PORTELLO))
        {
            chiaveGame(quiOggetto(playerX - 1, playerY, map), wd);
            map.obj[indexOggetto(playerX - 1, playerY, map)].rotto = false;
            map.riparazioni++;
        }
    }

    // Destra.
    if (dir == RIGHT)
    {
        // Valvola.
        if (quiOggetto(playerX + 1, playerY, map).type == VALVOLA)
            if (!map.valvola)
            {
                map.valvola = true;
                return true;
            }

        // Nastro.
        if (selectedTool == NASTRO && (quiOggetto(playerX + 1, playerY, map).type == CESSO ||
            quiOggetto(playerX + 1, playerY, map).type == VASCA))
        {
            nastroGame(quiOggetto(playerX + 1, playerY, map), wd);
            map.obj[indexOggetto(playerX + 1, playerY, map)].rotto = false;
            map.riparazioni++;
        }

        // Martello.
        if (selectedTool == MARTELLO && (quiOggetto(playerX + 1, playerY, map).type == DOCCIA ||
            quiOggetto(playerX + 1, playerY, map).type == BIDET))
        {
            martelloGame(quiOggetto(playerX + 1, playerY, map), wd);
            map.obj[indexOggetto(playerX + 1, playerY, map)].rotto = false;
            map.riparazioni++;
        }

        // Chiave.
        if (selectedTool == CHIAVE && (quiOggetto(playerX + 1, playerY, map).type == LAVANDINO ||
            quiOggetto(playerX + 1, playerY, map).type == PORTELLO))
        {
            chiaveGame(quiOggetto(playerX + 1, playerY, map), wd);
            map.obj[indexOggetto(playerX + 1, playerY, map)].rotto = false;
            map.riparazioni++;
        }
    }

    // Spugna.
    if (selectedTool == SPUGNA)
    {
        if (map.valvola && map.acqua)
        {
            map.acqua = false;
            map.riparazioni++;
        }
    }

    return true;
}



string* objAbout1 = new string[7] {
    "Valvola Aperta\n Richiede Mani",
    "Cesso Rotto\n Richiede Nastro Adesivo",
    "Vasca Incrinata\n Richiede Nastro Adesivo",
    "Doccia Sfasciata\n Richiede Martello",
    "Bidet Bombardato\n Richiede Martello",
    "Lavandino Innondato\n Richiede Chiave",
    "Portello Devastato\n Richiede Chiave",
};

string* objAbout2 = new string[7]{
    "Valvola Chiusa",
    "Cesso Slendente",
    "Vasca Immacolata",
    "Doccia Incredibile",
    "Bidet Fantasioso",
    "Lavandino Asburgico",
    "Portello Perfetto",
};



string getAbout(int x, int y, MAP map, sf::RenderWindow& window)
{
    int rx = x / 64;
    int ry = y / 64;

    // Descrizione Strumenti.
    if (y >= 610 && y <= 610 + 64)
        return toolsAbout[rx - 5];

    // Descrizione Ambiente.
    if (x >= 64 && x <= 832 && y >= 64 && y <= 576)
    {
        OBJ tempObj = quiOggetto(rx - 1, ry - 1, map);

        // Elon Musk.
        if (rx - 1 == playerX && ry - 1 == playerY)
            return "Elon Musk";

        // No Oggetto.
        if (tempObj.type < 0)
        {
            switch (evaluateMap(map.map[ry - 1], rx))
            {
            case PAVIMENTO:
                if (map.acqua)
                    return "Pavimento Allagato";
                else
                    return "Pavimento";

                break;

            case MURO:
                return "Muro";
                break;

            case VUOTO:
                return "Vuoto Cosmico";
                break;

            default:
                break;
            }
        }
        // Sì Oggetto.
        else
        {
            if (tempObj.rotto)
                return objAbout1[tempObj.type - 3];
            else
                return objAbout2[tempObj.type - 3];
        }
    }

    return "";
}



void drawToolBar(sf::RenderWindow &window)
{
    sf::RectangleShape shape(sf::Vector2f(64.0F, 64.0F));   
    sf::Color redondi;
    redondi = sf::Color(100, 100, 100, 100);
    shape.setFillColor(redondi);

    sf::Sprite Obj_exhibition;

    sf::Texture Obj_exhibition_texture;
    Obj_exhibition_texture.loadFromFile("assets\\object-touch.png");
    sf::Texture Obj_exhibition_selected_texture;
    Obj_exhibition_selected_texture.loadFromFile("assets\\object-touch-selected.png");

    sf::Font font;
    font.loadFromFile(FONT);
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);

    for (int i = 0; i < 4; i++)
    {
        stringstream ss;

        // aggiungo testo allo stream
        ss << i + 1;
        // imposto coordinate testo.
        text.setPosition(64 + 256 + i * 64 + 32, 665);
        // imposto testo
        text.setString(ss.str());

        // sfondo corice
        shape.setPosition(64 + 256 + i * 64, 610);
        // disegno sfondo cornice
        window.draw(shape);
        // imposto coordinate cornice
        Obj_exhibition.setPosition(64 + 256 + i * 64, 610);

        // oggetto selezionato. (faccio bordo bello)
        if (i == selectedTool)
            Obj_exhibition.setTexture(Obj_exhibition_selected_texture);
        // altro oggetto (faccio bordo brutto)
        else
            Obj_exhibition.setTexture(Obj_exhibition_texture);

        // disegno casella.
        window.draw(Obj_exhibition);
        // disegno testo
        window.draw(text);
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(896, 800), "Elon the Plumber");

    //menu
    sf::Sprite menu;
    sf::Texture menuTexture;
    menuTexture.loadFromFile("assets\\menu.png");
    menu.setTexture(menuTexture);
    menu.setPosition(0, 0);

    //tasto gioca
    bool tastogioca = false;
    sf::Sprite tasto_gioca;
    sf::Texture tasto_giocaTexture;
    tasto_giocaTexture.loadFromFile("assets\\tasto_gioca.png");
    tasto_gioca.setTexture(tasto_giocaTexture);
    tasto_gioca.setPosition(340, 338);

    //tasto tasti
    bool tastotasti = false;
    sf::Sprite tasto_tasti;
    sf::Texture tasto_tastiTexture;
    tasto_tastiTexture.loadFromFile("assets\\tasto_tasti.png");
    tasto_tasti.setTexture(tasto_tastiTexture);
    tasto_tasti.setPosition(338, 466);

    //tasto esci
    bool tastoesci = false;
    sf::Sprite tasto_esci;
    sf::Texture tasto_esciTexture;
    tasto_esciTexture.loadFromFile("assets\\tasto_esci.png");
    tasto_esci.setTexture(tasto_esciTexture);
    tasto_esci.setPosition(338, 610);

    bool game = false;

    int mx, my;
    //musica menu
    sf::Music musica;
    musica.openFromFile("assets\\menu_music.wav");
    musica.play();

    while (window.isOpen())
    {
        sf::Event event;

        window.clear();

        window.draw(menu);

        if (tastogioca)
        {
            window.draw(tasto_gioca);
        }
        if (tastotasti)
        {
            window.draw(tasto_tasti);
        }
        if (tastoesci)
        {
            window.draw(tasto_esci);
        }



        while (window.pollEvent(event))
        {
            mx = sf::Mouse::getPosition(window).x;
            my = sf::Mouse::getPosition(window).y;

            if (event.type == sf::Event::Closed) {
                window.close();

            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mx >= 342 && mx <= 574 && my <= 469 && my >= 372)
                {
                    game = true;
                    break;
                }
                else if (mx >= 342 && mx <= 574 && my >= 500 && my <= 596)
                {
                    cout << "tasti" << endl;
                }
                else if (mx >= 342 && mx <= 574 && my >= 644 && my <= 742)
                {
                    return 0;
                }

            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (mx >= 342 && mx <= 574 && my <= 469 && my >= 372)
                {
                    tastogioca = true;
                    tastotasti = false;
                    tastoesci = false;
                }
                else if (mx >= 342 && mx <= 574 && my >= 500 && my <= 596)
                {
                    tastotasti = true;
                    tastogioca = false;
                    tastoesci = false;
                }
                else if (mx >= 342 && mx <= 574 && my >= 644 && my <= 742)
                {
                    tastoesci = true;
                    tastotasti = false;
                    tastogioca = false;
                }
                else
                {
                    tastogioca = false;
                    tastotasti = false;
                    tastoesci = false;
                }
            }
        }

        window.display();

        if (game == true)
            break;
    }

    musica.stop();
    //
    // Player
    //

    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets\\elon_def.png");
    player.setTexture(playerTexture);


    player.setPosition(playerX * 64 + 64, playerY * 64 + 64);



    MAP defaultMap = generateDefaultMap();


    //
    //  Coperture
    //

    sf::Sprite cop0;
    sf::Texture cop0_texture;
    cop0_texture.loadFromFile("assets\\copertura0.png");
    cop0.setTexture(cop0_texture);
    cop0.setPosition(0, 0);

    sf::Sprite cop1;
    sf::Texture cop1_texture;
    cop1_texture.loadFromFile("assets\\copertura1.png");
    cop1.setTexture(cop1_texture);
    cop1.setPosition(0, 700);

    //
    //  Wrench
    //
    
    sf::Sprite wrench;
    sf::Texture wrenchTexture;

    if (tools[0] == true)
        wrenchTexture.loadFromFile("assets\\wrench.png");
    else
        wrenchTexture.loadFromFile("assets\\wrench_discolored.png");

    wrench.setTexture(wrenchTexture);

    //
    //  Scotch
    //

    sf::Sprite scotch;
    sf::Texture scotchTexture;

    if (tools[1] == true)
        scotchTexture.loadFromFile("assets\\scotch.png");
    else
        scotchTexture.loadFromFile("assets\\scotch_discolored.png");

    scotch.setTexture(scotchTexture);
    
    //
    //  Martello
    //
    
    sf::Sprite martello;
    sf::Texture MARTELLOTexture;

    if (tools[2] == true)
        MARTELLOTexture.loadFromFile("assets\\hammer.png");
    else
        MARTELLOTexture.loadFromFile("assets\\hammer_discolored.png");

    martello.setTexture(MARTELLOTexture);
    
    //
    //  Spugna
    //

    sf::Sprite spongebob;
    sf::Texture spongebobTexture;

    if (tools[3] == true)
        spongebobTexture.loadFromFile("assets\\spongebob.png");
    else
        spongebobTexture.loadFromFile("assets\\spongebob_discolored.png");

    spongebob.setTexture(spongebobTexture);
	
    //
    //  Font Scritte
    //
	
    sf::Font font;
    font.loadFromFile(FONT);
    sf::Text text;
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(18);
    text.setPosition(32, 720);
    //passi
    bool footstep = true;

    sf::SoundBuffer buffer;
    buffer.loadFromFile("assets\\footstep1.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(25.f);
    //musica gioco
    sf::Music musica_gioco;
    musica_gioco.openFromFile("assets\\game_music.wav");
    musica_gioco.play();
    musica_gioco.setLoop(true);

    while (window.isOpen())
    {   
        sf::Event event;

        window.clear(sf::Color(48, 48, 48));

        // Carico Prossima Mappa.
        if (defaultMap.riparazioni == defaultMap.riparazioniTot)
        {
            defaultMap = loadNextMap(window);

            if (currentMapIndex > 9)
            {
                while (true);
            }
        }

        // Copertura Superiore.
        window.draw(cop0);
        // Copertura Inferiore.
        window.draw(cop1);
        // Mappa.
        drawMap(defaultMap, window);
        // ToolBar.
        drawToolBar(window);
		
        // Oggetti.
        spongebob.setPosition(320 + 0 * 64, 610);
        scotch.setPosition(320 + 1 * 64, 610);
        martello.setPosition(320 + 2 * 64, 610);
        wrench.setPosition(320 + 3 * 64, 610);
        window.draw(spongebob);
		window.draw(scotch);
		window.draw(martello);
        window.draw(wrench);

        //  Player.
        window.draw(player);
        // Testo.
        window.draw(text);

        // Ciclo Messaggi Finestra.
        while (window.pollEvent(event))
        {
            //
            //  Chiusura Finestra.
            //

            if (event.type == sf::Event::Closed)
                window.close();
            //
            //  Input Mouse.
            //

			

            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Calcolo Coordinata X Relativa.
                int x = sf::Mouse::getPosition(window).x;
                // Calcolo Coordinata Y Relativa.
                int y = sf::Mouse::getPosition(window).y;

                text.setString(getAbout(x, y, defaultMap, window));
            }
            
            //
            //  Input Tastiera.
            //

            if (event.type == sf::Event::KeyPressed)
            {
                // Analisi Input.
                switch (event.key.code)
                {
                    //
                    //  MOVIMENTI
                    //

                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    playerTexture.loadFromFile("assets\\elon_w.png");
                    player.setTexture(playerTexture);

                    if (dir != NORTH)
                        dir = NORTH;
                    else
                    {
                        if (canMove(playerX, playerY - 1, defaultMap))
                            playerY -= 1;
                    }
                    sound.stop();
                    if (footstep) {
                        buffer.loadFromFile("assets\\footstep1.wav");
                        footstep = false;
                    }
                    else {
						buffer.loadFromFile("assets\\footstep2.wav");
						footstep = true;
                    }
                    sound.play();
					
                    break;

                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    playerTexture.loadFromFile("assets\\elon_def.png");
                    player.setTexture(playerTexture);

                    if (dir != SOUTH)
                        dir = SOUTH;
                    else
                    {
                        if (canMove(playerX, playerY + 1, defaultMap))
                            playerY += 1;
                    }
                    sound.stop();
                    if (footstep) {
                        buffer.loadFromFile("assets\\footstep1.wav");
                        footstep = false;
                    }
                    else {
                        buffer.loadFromFile("assets\\footstep2.wav");
                        footstep = true;
                    }
                    sound.play();

                    break;

                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    playerTexture.loadFromFile("assets\\elon_a.png");
                    player.setTexture(playerTexture);

                    if (dir != LEFT)
                        dir = LEFT;
                    else
                    {
                        if (canMove(playerX - 1, playerY, defaultMap))
                            playerX -= 1;
                    }
                    sound.stop();
                    if (footstep) {
                        buffer.loadFromFile("assets\\footstep1.wav");
                        footstep = false;
                    }
                    else {
                        buffer.loadFromFile("assets\\footstep2.wav");
                        footstep = true;
                    }
                    sound.play();

                    break;

                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    playerTexture.loadFromFile("assets\\elon_d.png");
                    player.setTexture(playerTexture);

                    if (dir != RIGHT)
                        dir = RIGHT;
                    else
                    {
                        if (canMove(playerX + 1, playerY, defaultMap))
                            playerX += 1;
                    }
                    sound.stop();
                    if (footstep) {
                        buffer.loadFromFile("assets\\footstep1.wav");
                        footstep = false;
                    }
                    else {
                        buffer.loadFromFile("assets\\footstep2.wav");
                        footstep = true;
                    }
                    sound.play();
					
                    break;

                    //
                    //  SELEZIONE INVENTARIO
                    //

                case sf::Keyboard::Num1:
                    // Controllo se Oggetto è Attivo.
                    if (tools[0])
                    {
                        // Imposto Selezione.
                        selectedTool = 0;
                        // Imposto Testo,
                        text.setString(toolsAbout[0]);
                    }

                    break;

                case sf::Keyboard::Num2:
                    // Controllo se Oggetto è Attivo.
                    if (tools[1])
                    {
                        // Imposto Selezione.
                        selectedTool = 1;
                        // Imposto Testo,
                        text.setString(toolsAbout[1]);
                    }

                    break;

                case sf::Keyboard::Num3:
                    // Controllo se Oggetto è Attivo.
                    if (tools[2])
                    {
                        // Imposto Selezione.
                        selectedTool = 2;
                        // Imposto Testo,
                        text.setString(toolsAbout[2]);
                    }

                    break;

                case sf::Keyboard::Num4:
                    // Controllo se Oggetto è Attivo.
                    if (tools[3])
                    {
                        // Imposto Selezione.
                        selectedTool = 3;
                        // Imposto Testo,
                        text.setString(toolsAbout[3]);
                    }

                    break;

                    //
                    //  INTERAZIONI AMBIENTALI
                    //

                case sf::Keyboard::E:
                case sf::Keyboard::Space:
                    if (hoToccatoOggetto(playerX, playerY, dir, defaultMap))
                    {
                        interagisci(playerX, playerY, dir, defaultMap, window);
                    }

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
