#include "Mat.h"
#include <stdlib.h>
#include <stdio.h>

Vecteur vecteurAlloc(int nbElements)
{
  Vecteur A;
  int i;
  A=(Vecteur)malloc(sizeof(structVecteur));
  A->nbElements=nbElements;
  A->donnees=(double*)malloc(nbElements*sizeof(double));
  for(i=0;i<nbElements;i++)
    {
      A->donnees[i]=-10.0;
    }
  return A;
}

void libererVecteur(Vecteur * A){
  free((*A)->donnees);
  free((*A));
  *A=NULL;
}

void initVecteur(Vecteur* v)
{
  int nbe=(*v)->nbElements;
  int i;
  for(i=0;i<nbe;i++)
    {
      (*v)->donnees[i]=0;
    }
}

int egalMDR(Vecteur *v1,Vecteur *v2) 
{
  int nbe=(*v1)->nbElements;
  int nbe2=(*v2)->nbElements;
  int i=0;
  if (nbe != nbe2)
    {
      fprintf(stderr," egalMDR vecteur de dim diff\n");
      exit(0);
    }

  for (i=0;i<nbe;i++)
    {
      if ((*v1)->donnees[i]!=(*v2)->donnees[i])
	{
	  return 0;
	}
    }
  return 1;
}

void afficheVecteur (Vecteur* v)
{
  int nbElements=(*v)->nbElements;
  int i;
  for(i=0;i<nbElements;i++)
    {
      printf("%f\t",(*v)->donnees[i]);
    }
  printf("\n");
}


Matrice MatriceAlloc(int l,int c){
    Matrice A;
    int i,j;
    A=(Matrice)malloc(sizeof(structMatrice));
    A->nbLignes=l;A->nbColonnes=c;
    A->donnees=(double**)malloc(l*sizeof(double*));
    for(i=0;i<l;i++) {
        A->donnees[i]=(double *)malloc(c*sizeof(double ));
    }

    for(i=0;i<l;i++) 
      {
	for(j=0;j<c;j++)
	  {
	    A->donnees[i][j]=-10.0;
	  }
      }
    return A;
}
void libererMatrice(Matrice *A){
    int i;
    for(i=0;i<(*A)->nbLignes;i++)
      {
	free((*A)->donnees[i]);
      }
    free((*A)->donnees);
    free((*A));
    *A=NULL;
}


void initMatrice(Matrice* m)
{
  int nbLignes=(*m)->nbLignes;
  int nbColonnes=(*m)->nbColonnes;
  int i, j;
  for(i=0;i<nbLignes;i++)
    {
      for(j=0;j<nbColonnes;j++)
	{
	  (*m)->donnees[i][j]=-10.0;
	}
    }
}


void lectureMatrice (Matrice *m,double *mat1,int nbLignes,int nbColonnes)
{
  int I=nbLignes;
  int J=nbColonnes;
  
  int i,j;
  int k=0;
  *m=MatriceAlloc(nbLignes,nbColonnes);
  for(j=0;j<J;j++)
    {
      for(i=0;i<I;i++)
	{ 
	  (*m)->donnees[i][j]=(double)(mat1[k]);
	  k++;
	}
      }
  }

void allocMatrice (Matrice *m,int nbLignes,int nbColonnes)
{
   *m=MatriceAlloc(nbLignes,nbColonnes);
}

void  lectureMatriceEntier (Matrice *m,int *mat1,int nbLignes,int nbColonnes)
{
  int I=nbLignes;
  int J=nbColonnes;
  int i,j;
  int k=0;
  *m=MatriceAlloc(I,J);
  initMatrice(m);
  for(i=0;i<I;i++)
    { 
      for(j=0;j<J;j++)
	{
	  (*m)->donnees[i][j]=(double)(mat1[k]);
	  k++;
	}
      }
  }

void  affecte (Matrice *m,int i,int j,double valeur)
{
  (*m)->donnees[i][j]=valeur;
}

void afficheMatrice (Matrice* m)
{
 int nl=(*m)->nbLignes;
  int nc=(*m)->nbColonnes;
  int i, j;
  for(i=0;i<nl;i++)
    {
      for(j=0;j<nc;j++)
	{
	  fprintf(stderr,"%f\t",(*m)->donnees[i][j]);
	}
      fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}

void afficheDim(Matrice *m)
{
  int nl=(*m)->nbLignes;
  int nc=(*m)->nbColonnes;
  fprintf(stderr,"%d lignes %d colonnnes\n",nl,nc);
}

