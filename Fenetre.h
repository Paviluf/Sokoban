#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include "Niveaux.h"

class Fenetre
{
    public:
        Fenetre();
        ~Fenetre();
        void chargerNiveau(Niveaux Level);

    private:
        sf::Vector2i m_sMarioPosition;
        sf::Vector2f m_position;
        sf::Texture m_mur;
        sf::Texture m_caisse;
        sf::Texture m_caisseOK;
        sf::Texture m_objectif;
        sf::Texture m_marioHaut;
        sf::Texture m_marioBas;
        sf::Texture m_marioGauche;
        sf::Texture m_marioDroite;
        sf::Texture m_bravo;
        sf::Texture m_regles;
        sf::Texture m_menu;
        sf::Texture m_gagne;
        sf::Texture m_reglesEditeur;
        sf::Sprite m_sMur;
        sf::Sprite m_sCaisse;
        sf::Sprite m_sCaisseOK;
        sf::Sprite m_sObjectif;
        sf::Sprite m_sMario;
        sf::Sprite m_sBravo;
        sf::Sprite m_sRegles;
        sf::Sprite m_sMenu;
        sf::Sprite m_sGagne;
        sf::Sprite m_sCurseur;
        bool m_ok;
        bool m_objectifRestant;
        bool m_bravoAfficher;
        bool m_reglesAfficher;
        bool m_menuAfficher;
        bool m_gagneAfficher;
        bool m_niveauJeu;
        bool m_niveauEditeur;
        bool m_editeur;
        bool m_reglesEditeurB;
        bool m_poserGauche;
        bool m_poserDroite;
		bool m_emploiEditeur;
        char m_code;
        int m_niveau[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR];
        int m_niveauActuel;
        unsigned int m_mouseX;
        unsigned int m_mouseY;
        sf::Text m_text;
        std::ostringstream m_oss;
        std::string m_result;
};

#endif // FENETRE_H_INCLUDED
