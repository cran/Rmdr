#include <errno.h>

typedef struct{
  int nbLignes, nbColonnes; 
  double **donnees;
} *Matrice, structMatrice;


typedef struct{
  int nbElements; 
  double *donnees;
} *Vecteur, structVecteur;

Vecteur vecteurAlloc(int nbElements);
void libererVecteur(Vecteur* v);
void initVecteur(Vecteur* v);
void afficheVecteur (Vecteur* v);
int egalMDR(Vecteur *v1,Vecteur *v2);

Matrice MatriceAlloc(int l,int c);
void libererMatrice(Matrice *A);
void initMatrice(Matrice* m);
void lectureMatrice (Matrice *m,double *mat1,int nbLignes,int nbColonnes);
void lectureMatriceEntier (Matrice *m,int *mat1,int nbLignes,int nbColonnes);
void afficheMatrice (Matrice* m);
void afficheDim(Matrice *m);
void affecte (Matrice *m,int i,int j,double valeur);
void allocMatrice (Matrice *m,int nbLignes,int nbColonnes);

