#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define TAILLE_BLOC       32
#define NB_BLOCS_LARGEUR  12
#define NB_BLOCS_HAUTEUR  12
#define LARGEUR_FENETRE   TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE   TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif // CONSTANTES_H_INCLUDED
