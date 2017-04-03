#ifndef NIVEAUX_H_INCLUDED
#define NIVEAUX_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <string>
#include <sstream>
#include "constantes.h"

class Niveaux
{
    public:
        Niveaux(int niveau);
        ~Niveaux();
        void changerNiveau(int niveau);
        void changerNiveauEditeur(int niveau);
        void modificationNiveau(unsigned int mouseX, unsigned int mouseY, char code);
        void sauvegardeNiveauEditeur();
        void modifierNiveauEditeur(int niveau);
        void supprimerNiveauEditeur(int niveau);
        int lireMAX();
        std::string lireNiveau();

    private:
        char m_caractereFgetc;
        int m_maxi;
        int m_test;
        std::string m_niveauxJeu[20];
        std::string m_niveaux;
        FILE* m_fichier;
};

#endif // NIVEAUX_H_INCLUDED
