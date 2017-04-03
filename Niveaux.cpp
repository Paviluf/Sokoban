#include "Niveaux.h"

Niveaux::Niveaux(int niveau)
{
    m_niveauxJeu[0] = "111111111111111111111111111111111111111111111111111111111111114200000311111111111111111111111111111111111111111111111111111111111111111111111111";
    m_niveauxJeu[1] = "111111111111111111111111111111111111111400001111111111221111111111001111111111001111111111031111111111011111111111011111111111311111111111111111";
    m_niveauxJeu[2] = "111111111111111111111111111111111111111111001111114200001111111111101111111111101111111001100111111000000111111011111111111311111111111111111111";
    m_niveauxJeu[3] = "111110011111111114000001111100011001033101011011000002001211100101000011111100011211111111111001111130000001111111111111111111111111111111111111";
    m_niveauxJeu[4] = "111111111111111111111111111111111111110011111111100000011111103312011111111002011111111114011111111111111111111111111111111111111111111111111111";
    m_niveauxJeu[5] = "111111111111111111111111111111111111111100311111111021311111111000011111111101001111111120401111111100011111111111111111111111111111111111111111";
    m_niveauxJeu[6] = "111111111111111111111111111111111111111111031111111111001111111102200111111100000111111112101111111113431111111111111111111111111111111111111111";
    m_niveauxJeu[7] = "111111111111111111111111111111111111111333341111110020120111110020020111110011000111111111111111111111111111111111111111111111111111111111111111";
    m_niveauxJeu[8] = "111111111111111114001111111302031111111002011111111101111111110200111111100000111111130011111111111111111111111111111111111111111111111111111111";
    m_niveauxJeu[9] = "111111111111111111111111111111001111110003321111110241020111111233000111111001100111111111111111111111111111111111111111111111111111111111111111";
    m_niveauxJeu[10] = "111111111111111111111111111111111111110011111111110300311111110301011111110020011111111221111111111041111111111111111111111111111111111111111111";
    m_niveauxJeu[11] = "111111111111111111111111111111111111111110011111111110011111111002220111111033310111111013330111111022241111111110001111111111111111111111111111";
    m_niveauxJeu[12] = "111111111111111111111111111111111111111111111111111111031111111111033011111100200311111100010111111112220111111110411111111111111111111111111111";
    m_niveauxJeu[13] = "111111111111111111111111111100111111111102011111111032311111111023201111111032301111111114111111111100111111111100111111111100111111111111111111";
    m_niveauxJeu[14] = "111111111111111111111111111111111111111000111111103232400111100232300111111010111111111000111111111111111111111111111111111111111111111111111111";
    m_niveauxJeu[15] = "111111111111111111111111111111111111111100111111111130111111111030111111111232111111114232001111110230001111111100111111111111111111111111111111";
    m_niveauxJeu[16] = "111111111111111111111111111111111111111110001111111110521111111105450011111103500011111110001111111110011111111111111111111111111111111111111111";
    m_niveauxJeu[17] = "111111111111111111111111111111111111111104311111111022501111111001301111111000001111111021001111111100311111111111111111111111111111111111111111";
    m_niveauxJeu[18] = "111111111111111111111111111110011111110002001111110055501111110030301111111050500111111155500111111102011111111104011111111111111111111111111111";
    m_niveauxJeu[19] = "111111111111111111111111111111111111100011100111102000004111112555552111102333332011100010000011111111110011111111111111111111111111111111111111";

    m_niveaux = m_niveauxJeu[niveau];

    m_fichier = NULL;
}

Niveaux::~Niveaux()
{}

void Niveaux::changerNiveau(int niveau)
{
    m_niveaux = m_niveauxJeu[niveau];
}

std::string Niveaux::lireNiveau()
{
    return m_niveaux;
}

void Niveaux::changerNiveauEditeur(int niveau)
{
    int h = 0;
    int j = 0;
    m_maxi = 0;
    m_test = 0;
    m_caractereFgetc = 0;

    m_fichier = fopen("niveaux.lvl", "r");

    if(m_fichier == NULL)
    {
        m_fichier = fopen("niveaux.lvl", "w+");
        fclose(m_fichier);
        m_fichier = fopen("niveaux.lvl", "r");
    }

    while (m_caractereFgetc != EOF)
    {
        m_caractereFgetc = fgetc(m_fichier);

        if(m_caractereFgetc != EOF)
            m_test++;

        if (m_caractereFgetc == '\n')
            m_maxi++;
    }

    if(m_test > 0)
    {
        rewind(m_fichier);

        while (h != niveau)
        {
            m_caractereFgetc = fgetc(m_fichier);

            if (m_caractereFgetc == '\n' || m_caractereFgetc == EOF)
                h++;
        }

        do
        {
            m_caractereFgetc = fgetc(m_fichier);

            if(m_caractereFgetc != '\n')
                m_niveaux[j] = m_caractereFgetc;

            j++;
        }while (j <= NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR);
    }


    if((m_fichier == NULL) || (m_test == 0))
        m_niveaux = m_niveauxJeu[0];

    fclose(m_fichier);
}

int Niveaux::lireMAX()
{
    return m_maxi;
}

void Niveaux::modificationNiveau(unsigned int mouseX, unsigned int mouseY, char code)
{
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int z = 0;

    x = mouseX / 34;
    y = mouseY / 34;
    z = (y * 12) + x;

    if(code == '4')
    {
        for(int i = 0; i < 144; i++)
        {
            if(m_niveaux[i] == '4')
                m_niveaux[i] = '0';

        }
    }

    m_niveaux[z] = code;
}

void Niveaux::sauvegardeNiveauEditeur()
{
    m_test = 0;
    m_maxi = 0;
    m_caractereFgetc = 0;

    m_fichier = fopen("niveaux.lvl", "r");

    if(m_fichier == NULL)
    {
        m_fichier = fopen("niveaux.lvl", "w+");
        fclose(m_fichier);
        m_fichier = fopen("niveaux.lvl", "r");
    }

    while (m_caractereFgetc != EOF)
    {
        m_caractereFgetc = fgetc(m_fichier);

        if(m_caractereFgetc != EOF)
            m_test++;
    }

    fclose(m_fichier);

    m_fichier = fopen("niveaux.lvl", "a");

    if(m_test > 0)
        fputc('\n', m_fichier);

    for(int i = 0; i < 144; i++)
    {
        fputc(m_niveaux[i], m_fichier);
    }

    fclose(m_fichier);

    m_caractereFgetc = 0;

    m_fichier = fopen("niveaux.lvl", "r");

    while (m_caractereFgetc != EOF)
    {
        m_caractereFgetc = fgetc(m_fichier);

        if (m_caractereFgetc == '\n')
            m_maxi++;
    }

    fclose(m_fichier);
}

void Niveaux::modifierNiveauEditeur(int niveau)
{
    int h = 0;
    int i = 0;
    int r = 0;
    int k = 0;
    m_caractereFgetc = 0;
	std::string *niveauCopier = NULL;
    niveauCopier = new std::string[m_maxi + 2]; // std::string niveauCopier[m_maxi + 2];
    std::string niveauAcopier = "";

    for(int y = 0; y < m_maxi; y++)
    {
        niveauCopier[y].erase();
    }

    m_fichier = fopen("niveaux.lvl", "r");

    if(m_fichier == NULL)
    {
        m_fichier = fopen("niveaux.lvl", "w+");
        fclose(m_fichier);
        m_fichier = fopen("niveaux.lvl", "r");
    }

    while (m_caractereFgetc != EOF)
    {
        m_caractereFgetc = fgetc(m_fichier);

        if(m_caractereFgetc != '\n' && m_caractereFgetc != EOF)
        {
            niveauAcopier = niveauAcopier + m_caractereFgetc;
            i++;
            k++;
        }

        if (m_caractereFgetc == '\n' || m_caractereFgetc == EOF)
        {
            niveauCopier[h] = niveauAcopier;
            niveauAcopier.erase();
            h++;
            i = 0;
        }
    }

    fclose(m_fichier);

    niveauCopier[niveau] = m_niveaux;

    i = 0;

    niveauAcopier.erase();

    m_fichier = fopen("niveaux.lvl", "w+");

    niveauAcopier = niveauCopier[r];


    for(int j = 0; j < ((m_maxi + 1) * 144); j++)
    {
        m_caractereFgetc = niveauAcopier[i];

        fputc(m_caractereFgetc, m_fichier);
        i++;

        if(i == 144)
        {
            i = 0;
            r++;
            niveauAcopier = niveauCopier[r];

            if(r <= m_maxi)
                fputc('\n', m_fichier);
        }
    }

    fclose(m_fichier);

    m_caractereFgetc = 0;

    m_fichier = fopen("niveaux.lvl", "r");

    while (m_caractereFgetc != EOF)
    {
        m_caractereFgetc = fgetc(m_fichier);

        if (m_caractereFgetc == '\n')
            m_maxi++;
    }

    fclose(m_fichier);

	delete[] niveauCopier;
}

void Niveaux::supprimerNiveauEditeur(int niveau)
{
    int h = 0;
    int i = 0;
    int r = 0;
    int k = 0;
    m_test = 0;
    m_caractereFgetc = 0;
    bool niveauZero = false;
    std::string *niveauCopier = NULL;
    niveauCopier = new std::string[m_maxi + 2]; // std::string niveauCopier[m_maxi + 2];
    std::string niveauAcopier = "";

    m_fichier = fopen("niveaux.lvl", "r");

    if(m_fichier == NULL)
    {
        m_fichier = fopen("niveaux.lvl", "w+");
        fclose(m_fichier);
        m_fichier = fopen("niveaux.lvl", "r");
    }

    while (m_caractereFgetc != EOF)
    {
        m_caractereFgetc = fgetc(m_fichier);

        if(m_caractereFgetc != EOF)
            m_test++;
    }

    fclose(m_fichier);

    m_caractereFgetc = 0;

    if(m_test > 0)
    {
        if(niveau == 0)
            niveauZero = true;

        for(int y = 0; y < m_maxi + 2; y++)
        {
            niveauCopier[y].erase();
        }

        m_fichier = fopen("niveaux.lvl", "r");

        m_caractereFgetc = 0;

        while (m_caractereFgetc != EOF)
        {
            m_caractereFgetc = fgetc(m_fichier);

            if(m_caractereFgetc != '\n' && m_caractereFgetc != EOF)
            {
                niveauAcopier = niveauAcopier + m_caractereFgetc;
                i++;
                k++;
            }

            if (m_caractereFgetc == '\n' || m_caractereFgetc == EOF)
            {
                niveauCopier[h] = niveauAcopier;
                niveauAcopier.erase();
                h++;
                i = 0;
            }
        }

        fclose(m_fichier);

        i = 0;

        niveauAcopier.erase();

        m_fichier = fopen("niveaux.lvl", "w+");

        niveauAcopier = niveauCopier[r];

        for(int j = 0; j < ((m_maxi + 1) * 144); j++)
        {
            m_caractereFgetc = niveauAcopier[i];

            if(r != niveau)
                fputc(m_caractereFgetc, m_fichier);

            i++;

            if(i == 144)
            {
                i = 0;

                r++;
                niveauAcopier = niveauCopier[r];

                if((r != niveau && r <= m_maxi) && !niveauZero)
                    fputc('\n', m_fichier);

                niveauZero = false;
            }
        }

        fclose(m_fichier);

        m_caractereFgetc = 0;

    }

        m_fichier = fopen("niveaux.lvl", "r");

        while (m_caractereFgetc != EOF)
        {
            m_caractereFgetc = fgetc(m_fichier);

            if (m_caractereFgetc == '\n')
                m_maxi++;
        }

        fclose(m_fichier);

		delete[] niveauCopier;
}
