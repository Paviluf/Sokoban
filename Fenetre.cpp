#include "Fenetre.h"
#include "mur.png.h"
#include "caisse.png.h"
#include "caisse_ok.png.h"
#include "objectif.png.h"
#include "mario_haut.png.h"
#include "mario_bas.png.h"
#include "mario_gauche.png.h"
#include "mario_droite.png.h"
#include "bravo.png.h"
#include "regles.png.h"
#include "menu.png.h"
#include "gagne.png.h"
#include "regles_editeur.png.h"
#include <iostream>

Fenetre::Fenetre()
{
    sf::RenderWindow App(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32), "Sokoban", sf::Style::Close);
    App.setFramerateLimit(60);

    if(!m_mur.loadFromMemory(iMur, sizeof(iMur))||
        !m_caisse.loadFromMemory(iCaisse, sizeof(iCaisse))||
        !m_caisseOK.loadFromMemory(iCaisseOK, sizeof(iCaisseOK))||
        !m_objectif.loadFromMemory(iObjectif, sizeof(iObjectif))||
        !m_marioHaut.loadFromMemory(iMarioHaut, sizeof(iMarioHaut))||
        !m_marioBas.loadFromMemory(iMarioBas, sizeof(iMarioBas))||
        !m_marioGauche.loadFromMemory(iMarioGauche, sizeof(iMarioGauche))||
        !m_marioDroite.loadFromMemory(iMarioDroite, sizeof(iMarioDroite))||
        !m_bravo.loadFromMemory(iBravo, sizeof(iBravo))||
        !m_regles.loadFromMemory(iRegles, sizeof(iRegles))||
        !m_menu.loadFromMemory(iMenu, sizeof(iMenu))||
        !m_gagne.loadFromMemory(iGagne, sizeof(iGagne))||
        !m_reglesEditeur.loadFromMemory(iReglesEditeur, sizeof(iReglesEditeur)))
            App.close();

    m_marioHaut.setSmooth(true);
    m_marioBas.setSmooth(true);
    m_marioDroite.setSmooth(true);
    m_marioGauche.setSmooth(true);
    m_mur.setSmooth(true);
    m_caisse.setSmooth(true);
    m_caisseOK.setSmooth(true);
    m_objectif.setSmooth(true);

    App.setIcon(m_caisse.getSize().x, m_caisse.getSize().y, m_caisse.copyToImage().getPixelsPtr());

    m_sMario.setTexture(m_marioBas);
    m_sMur.setTexture(m_mur);
    m_sCaisse.setTexture(m_caisse);
    m_sCaisseOK.setTexture(m_caisseOK);
    m_sObjectif.setTexture(m_objectif);
    m_sBravo.setTexture(m_bravo);
    m_sRegles.setTexture(m_regles);
    m_sMenu.setTexture(m_menu);
    m_sGagne.setTexture(m_gagne);

//    m_sMario.setScale(1.5, 1.5);
//    m_sMur.setScale(1.5, 1.5);
//    m_sCaisse.setScale(1.5, 1.5);
//    m_sCaisseOK.setScale(1.5, 1.5);
//    m_sObjectif.setScale(1.5, 1.5);
//    m_sBravo.setScale(1.5, 1.5);
//    m_sRegles.setScale(1.5, 1.5);
//    m_sMenu.setScale(1.5, 1.5);
//    m_sGagne.setScale(1.5, 1.5);

    //const sf::Input& Input = App.GetInput();

    // Declare a new font
    sf::Font font;
    // Load it from a file
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "font failed";
    }

    m_text.setFont(font);
    m_text.setCharacterSize(18.f);
    m_text.setStyle(sf::Text::Bold | sf::Text::Italic);
    m_text.setColor(sf::Color(0,0,0));
    m_text.setPosition(10.f, 5.f);

    m_ok = false;
    m_objectifRestant = false;
    m_niveauActuel = 0;
    m_bravoAfficher = false;
    m_reglesAfficher = false;
    m_menuAfficher = true;
    m_gagneAfficher = false;
    m_niveauJeu = false;
    m_niveauEditeur = false;
    m_editeur = false;
    m_mouseX = 0;
    m_mouseY = 0;
    m_code = '1';
    m_reglesEditeurB = false;
    m_poserDroite = false;
    m_poserGauche = false;
	m_emploiEditeur = false;

    Niveaux Level(m_niveauActuel);

    while(App.isOpen())
    {
        sf::Event Event;
        while(App.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
                App.close();

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape) && m_menuAfficher)
                App.close();

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape) && !m_menuAfficher)
            {
                m_editeur = false;
                m_niveauEditeur = false;
                m_niveauJeu = false;
                m_menuAfficher = true;
                m_niveauActuel = 0;

                if(m_niveauJeu)
                    Level.changerNiveau(m_niveauActuel);

                if(m_niveauEditeur)
                    Level.changerNiveauEditeur(m_niveauActuel);
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R) && (m_niveauJeu || m_niveauEditeur))
            {
                m_sMario.setTexture(m_marioBas);

                if(m_niveauJeu)
                    Level.changerNiveau(m_niveauActuel);

                if(m_niveauEditeur)
                    Level.changerNiveauEditeur(m_niveauActuel);

                chargerNiveau(Level);
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageUp) && ((m_niveauJeu && m_niveauActuel <= 18) || (m_niveauEditeur && m_niveauActuel <= Level.lireMAX() - 1) || (m_editeur && m_niveauActuel <= Level.lireMAX() - 1)))
            {
                m_sMario.setTexture(m_marioBas);
                m_niveauActuel++;

                if(m_niveauJeu)
                    Level.changerNiveau(m_niveauActuel);

                if(m_niveauEditeur || m_editeur)
                    Level.changerNiveauEditeur(m_niveauActuel);

                chargerNiveau(Level);
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageDown) && (m_niveauActuel > 0))
            {
                m_sMario.setTexture(m_marioBas);
                m_niveauActuel--;

                if(m_niveauJeu)
                    Level.changerNiveau(m_niveauActuel);

                if(m_niveauEditeur || m_editeur)
                    Level.changerNiveauEditeur(m_niveauActuel);

                chargerNiveau(Level);
            }

			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right) && !m_bravoAfficher && !m_emploiEditeur && !m_reglesAfficher && !m_menuAfficher && !m_gagneAfficher && !m_editeur)
            {
                if(m_sMarioPosition.x + 1 >= NB_BLOCS_LARGEUR)
                    break;

                if(m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] == MUR)
                    break;

                if((m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] == CAISSE || m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] == CAISSE_OK) &&
                  (m_sMarioPosition.x + 2 >= NB_BLOCS_LARGEUR || m_niveau[m_sMarioPosition.x + 2][m_sMarioPosition.y] == MUR ||
                   m_niveau[m_sMarioPosition.x + 2][m_sMarioPosition.y] == CAISSE || m_niveau[m_sMarioPosition.x + 2][m_sMarioPosition.y] == CAISSE_OK))
                    break;

                if(m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] == CAISSE || m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] == CAISSE_OK)
                {
                    if(m_niveau[m_sMarioPosition.x + 2][m_sMarioPosition.y] == OBJECTIF)
                        m_niveau[m_sMarioPosition.x + 2][m_sMarioPosition.y] = CAISSE_OK;
                    else
                        m_niveau[m_sMarioPosition.x + 2][m_sMarioPosition.y] = CAISSE;

                    if(m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] == CAISSE_OK)
                        m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] = OBJECTIF;
                    else
                        m_niveau[m_sMarioPosition.x + 1][m_sMarioPosition.y] = VIDE;
                }

                m_sMario.setTexture(m_marioDroite);
                m_sMarioPosition.x = m_sMarioPosition.x + 1;
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left) && !m_bravoAfficher && !m_emploiEditeur && !m_reglesAfficher && !m_menuAfficher && !m_gagneAfficher && !m_editeur)
            {
                if(m_sMarioPosition.x - 1 < 0)
                    break;

                if(m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] == MUR)
                    break;

                if((m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] == CAISSE || m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] == CAISSE_OK) &&
                  (m_sMarioPosition.x - 2 < 0 || m_niveau[m_sMarioPosition.x - 2][m_sMarioPosition.y] == MUR ||
                   m_niveau[m_sMarioPosition.x - 2][m_sMarioPosition.y] == CAISSE || m_niveau[m_sMarioPosition.x - 2][m_sMarioPosition.y] == CAISSE_OK))
                    break;

                if(m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] == CAISSE || m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] == CAISSE_OK)
                {
                    if(m_niveau[m_sMarioPosition.x - 2][m_sMarioPosition.y] == OBJECTIF)
                        m_niveau[m_sMarioPosition.x - 2][m_sMarioPosition.y] = CAISSE_OK;
                    else
                        m_niveau[m_sMarioPosition.x - 2][m_sMarioPosition.y] = CAISSE;

                    if(m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] == CAISSE_OK)
                        m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] = OBJECTIF;
                    else
                        m_niveau[m_sMarioPosition.x - 1][m_sMarioPosition.y] = VIDE;
                }

                m_sMario.setTexture(m_marioGauche);
                m_sMarioPosition.x = m_sMarioPosition.x - 1;
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up) && !m_bravoAfficher && !m_emploiEditeur && !m_reglesAfficher && !m_menuAfficher && !m_gagneAfficher && !m_editeur)
            {
                if(m_sMarioPosition.y - 1 < 0)
                    break;

                if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] == MUR)
                    break;

                if((m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] == CAISSE || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] == CAISSE_OK) &&
                  (m_sMarioPosition.y - 2 < 0 || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 2] == MUR ||
                   m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 2] == CAISSE || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 2] == CAISSE_OK))
                    break;

                if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] == CAISSE || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] == CAISSE_OK)
                {
                    if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 2] == OBJECTIF)
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 2] = CAISSE_OK;
                    else
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 2] = CAISSE;

                    if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] == CAISSE_OK)
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] = OBJECTIF;
                    else
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y - 1] = VIDE;
                }

                m_sMario.setTexture(m_marioHaut);
                m_sMarioPosition.y = m_sMarioPosition.y - 1;
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down) && !m_bravoAfficher && !m_emploiEditeur && !m_reglesAfficher && !m_menuAfficher && !m_gagneAfficher && !m_editeur)
            {
                if(m_sMarioPosition.y + 1 >= NB_BLOCS_LARGEUR)
                    break;

                if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] == MUR)
                    break;

                if((m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] == CAISSE || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] == CAISSE_OK) &&
                  (m_sMarioPosition.y + 2 >= NB_BLOCS_HAUTEUR || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 2] == MUR ||
                   m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 2] == CAISSE || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 2] == CAISSE_OK))
                    break;

                if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] == CAISSE || m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] == CAISSE_OK)
                {
                    if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 2] == OBJECTIF)
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 2] = CAISSE_OK;
                    else
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 2] = CAISSE;

                    if(m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] == CAISSE_OK)
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] = OBJECTIF;
                    else
                        m_niveau[m_sMarioPosition.x][m_sMarioPosition.y + 1] = VIDE;
                }

                m_sMario.setTexture(m_marioBas);
                m_sMarioPosition.y = m_sMarioPosition.y + 1;
            }


            if((Event.type == sf::Event::KeyPressed) && m_bravoAfficher)
            {
                m_bravoAfficher = false;
                m_ok = true;
            }

            if((Event.type == sf::Event::KeyPressed) && m_editeur)
            {
                switch(Event.key.code)
                {
                    case sf::Keyboard::Numpad1 :
                        m_code = '1';
                        m_sCurseur.setTexture(m_mur);
                        break;
                    case sf::Keyboard::Num1 :
                        m_code = '1';
                        m_sCurseur.setTexture(m_mur);
                        break;
                    case sf::Keyboard::Numpad2 :
                        m_code = '2';
                        m_sCurseur.setTexture(m_caisse);
                        break;
                    case sf::Keyboard::Num2 :
                        m_code = '2';
                        m_sCurseur.setTexture(m_caisse);
                        break;
                    case sf::Keyboard::Numpad3 :
                        m_code = '3';
                        m_sCurseur.setTexture(m_objectif);
                        break;
                    case sf::Keyboard::Num3 :
                        m_code = '3';
                        m_sCurseur.setTexture(m_objectif);
                        break;
                    case sf::Keyboard::Numpad4 :
                        m_code = '4';
                        m_sCurseur.setTexture(m_marioBas);
                        break;
                    case sf::Keyboard::Num4 :
                        m_code = '4';
                        m_sCurseur.setTexture(m_marioBas);
                        break;
                    case sf::Keyboard::Numpad5 :
                        m_code = '5';
                        m_sCurseur.setTexture(m_caisseOK);
                        break;
                    case sf::Keyboard::Num5 :
                        m_code = '5';
                        m_sCurseur.setTexture(m_caisseOK);
                        break;
                    default :
                        m_code = '1';
                        m_sCurseur.setTexture(m_mur);
                        break;
                }
            }


            if((Event.type == sf::Event::KeyPressed) && m_reglesAfficher)
            {
                m_sRegles.setTexture(m_reglesEditeur);

                if(m_reglesEditeurB)
                {
                    m_reglesEditeurB = false;
                    m_menuAfficher = true;
                }

                m_reglesEditeurB = true;
            }

			if((Event.type == sf::Event::KeyPressed) && m_emploiEditeur)
            {
				m_emploiEditeur = false;
				m_editeur = true;
                m_menuAfficher = false;
                m_sCurseur.setTexture(m_mur);
                Level.changerNiveauEditeur(m_niveauActuel);
                chargerNiveau(Level);
			}

            if((Event.type == sf::Event::KeyPressed) && m_menuAfficher && !m_reglesAfficher && !m_emploiEditeur)
            {
                if((Event.key.code == sf::Keyboard::Numpad1) || (Event.key.code == sf::Keyboard::Num1))
                {
                    m_menuAfficher = false;
                    m_niveauJeu = true;
                    Level.changerNiveau(m_niveauActuel);
                    chargerNiveau(Level);
                }

                if((Event.key.code == sf::Keyboard::Numpad2) || (Event.key.code == sf::Keyboard::Num2))
                {
                    m_menuAfficher = false;
                    m_niveauEditeur = true;
                    Level.changerNiveauEditeur(m_niveauActuel);
                    chargerNiveau(Level);
                }

                if((Event.key.code == sf::Keyboard::Numpad3) || (Event.key.code == sf::Keyboard::Num3))
                {
					m_emploiEditeur = true;
					m_menuAfficher = false;
					m_sRegles.setTexture(m_reglesEditeur);
                }

                if((Event.key.code == sf::Keyboard::Numpad4) || (Event.key.code == sf::Keyboard::Num4))
                {
                    m_menuAfficher = false;
                    m_reglesAfficher = true;
                }

            }

            if((Event.type == sf::Event::KeyPressed) && m_gagneAfficher)
            {
                m_niveauActuel = 0;
                m_gagneAfficher = false;
                m_menuAfficher = true;
            }

            if((Event.type == sf::Event::MouseButtonPressed) && m_editeur)
            {
                if(Event.mouseButton.button  == sf::Mouse::Left)
                    m_poserGauche = true;
                if(Event.mouseButton.button == sf::Mouse::Right)
                    m_poserDroite = true;
            }

            if((Event.type == sf::Event::MouseButtonReleased) && m_editeur)
            {
                m_poserGauche = false;
                m_poserDroite = false;
            }


            if(m_poserGauche)
            {
                m_mouseX = Event.mouseMove.x;
                m_mouseY = Event.mouseMove.y;

                Level.modificationNiveau(m_mouseX, m_mouseY, m_code);

                chargerNiveau(Level);
            }

            if(m_poserDroite)
            {
                m_mouseX = Event.mouseMove.x;
                m_mouseY = Event.mouseMove.y;

                Level.modificationNiveau(m_mouseX, m_mouseY, '0');

                chargerNiveau(Level);
            }


            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A) && m_editeur)
            {
                Level.sauvegardeNiveauEditeur();
                m_niveauActuel = Level.lireMAX();
                Level.changerNiveauEditeur(m_niveauActuel);
                chargerNiveau(Level);
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::M) && m_editeur)
            {
                Level.modifierNiveauEditeur(m_niveauActuel);
                Level.changerNiveauEditeur(m_niveauActuel);
                chargerNiveau(Level);
            }

            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S) && m_editeur)
            {
                Level.supprimerNiveauEditeur(m_niveauActuel);

                if(m_niveauActuel > 0)
                    m_niveauActuel--;

                Level.changerNiveauEditeur(m_niveauActuel);
                chargerNiveau(Level);
            }

            if((Event.type == sf::Event::MouseMoved) && m_editeur)
            {
                m_mouseX = Event.mouseMove.x;
                m_mouseY = Event.mouseMove.y;
                m_position.x = m_mouseX + 10;
                m_position.y = m_mouseY + 15;
                m_sCurseur.setPosition(m_position);
            }
        }

        m_objectifRestant = false;

        if(!m_reglesAfficher && !m_menuAfficher && !m_gagneAfficher && !m_emploiEditeur)
        {
            for (int i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
            {
                for (int j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                {
                    m_position.x = i * TAILLE_BLOC;
                    m_position.y = j * TAILLE_BLOC;

                    switch(m_niveau[i][j])
                    {
                        case VIDE:
                            break;
                        case MUR:
                            m_sMur.setPosition(m_position);
                            App.draw(m_sMur);
                            break;
                        case CAISSE:
                            m_sCaisse.setPosition(m_position);
                            App.draw(m_sCaisse);
                            break;
                        case OBJECTIF:
                            m_objectifRestant = true;
                            m_sObjectif.setPosition(m_position);
                            App.draw(m_sObjectif);
                            break;
                        case CAISSE_OK:
                            m_sCaisseOK.setPosition(m_position);
                            App.draw(m_sCaisseOK);
                            break;
                    }
                }
            }

            m_position.x = m_sMarioPosition.x * TAILLE_BLOC;
            m_position.y = m_sMarioPosition.y * TAILLE_BLOC;
            m_sMario.setPosition(m_position);

                App.draw(m_sMario);

            if(!m_objectifRestant && !m_ok && !m_editeur)
                m_bravoAfficher = true;

            if(m_bravoAfficher)
            {
                m_sBravo.setPosition(64.0f, 150.0f);
                App.draw(m_sBravo);
            }

            if(!m_objectifRestant && !m_bravoAfficher && !m_editeur)
            {
                m_niveauActuel++;

                if((m_niveauJeu && m_niveauActuel == 20) || (m_niveauEditeur && m_niveauActuel > Level.lireMAX()))
                {
                    m_gagneAfficher = true;
                    m_niveauEditeur = false;
                    m_niveauJeu = false;
                    m_ok = false;
                }

                if((m_niveauJeu && m_niveauActuel <= 19) || (m_niveauEditeur && m_niveauActuel <= Level.lireMAX()))
                {
                    m_ok = false;

                    if(m_niveauJeu)
                        Level.changerNiveau(m_niveauActuel);

                    if(m_niveauEditeur)
                        Level.changerNiveauEditeur(m_niveauActuel);

                    chargerNiveau(Level);
                }
            }
        }

        if(m_gagneAfficher)
            App.draw(m_sGagne);

        if(m_reglesAfficher)
            App.draw(m_sRegles);

		if(m_emploiEditeur)
			App.draw(m_sRegles);

        if(m_menuAfficher)
        {
            m_reglesEditeurB = false;
            m_reglesAfficher = false;
            m_sRegles.setTexture(m_regles);
            App.draw(m_sMenu);
        }

        m_oss << m_niveauActuel + 1;
        m_result = "Niveau " + m_oss.str();
        m_text.setString(m_result);

        if(!m_menuAfficher && !m_gagneAfficher && !m_reglesAfficher && !m_emploiEditeur)
            App.draw(m_text);

        m_oss.str("");

        if(m_editeur)
            App.draw(m_sCurseur);

        App.display();

        App.clear(sf::Color(255, 255, 255));
    }
}

Fenetre::~Fenetre()
{}


void Fenetre::chargerNiveau(Niveaux Level)
{
    for (int i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (int j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (Level.lireNiveau()[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    m_niveau[j][i] = 0;
                    break;
                case '1':
                    m_niveau[j][i] = 1;
                    break;
                case '2':
                    m_niveau[j][i] = 2;
                    break;
                case '3':
                    m_niveau[j][i] = 3;
                    break;
                case '4':
                    m_niveau[j][i] = 4;
                    break;
                 case '5':
                    m_niveau[j][i] = 5;
                    break;
            }
        }
    }

    for (int i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (int j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (m_niveau[i][j] == MARIO)
            {
                m_sMarioPosition.x = i;
                m_sMarioPosition.y = j;
                m_niveau[i][j] = VIDE;
            }
        }
    }

    m_sMario.setTexture(m_marioBas);
}


