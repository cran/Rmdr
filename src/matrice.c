#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Mat.h"
 
int egal(double *v1,double *v2,int nbc)
{
  int j=0;
  for (j=0;j<nbc;j++)
    {
      if (v1[j]!=v2[j])
	{
	  return 0;
	}
    }
  
  return 1;
}

Vecteur boucle2(Matrice dmat1,Matrice dmat2)
{
  int J=dmat2->nbLignes;
  int I=dmat1->nbLignes;
  int nc1=dmat1->nbColonnes;
  Vecteur resu = vecteurAlloc(I);
  double *l1;
  double *l2;
  int i=0;
  int j=0;
 
  for (i=0;i<I;i++)
    {
      resu->donnees[i]=0;
      l1=dmat1->donnees[i];
      for (j=0;j<J;j++)
	{
	  l2=dmat2->donnees[j];
	  if (egal(l1,l2,nc1))
	    {
	      resu->donnees[i]+=1;
	    }
	}
    }
   return resu;
}

void div_col(Matrice y,Matrice y1)
{
  int i;
  int nl=y->nbLignes;
  for (i=0;i<nl;i++)
    {
      if (y->donnees[i][1]!=0.0)
	{
	  y->donnees[i][2]=y->donnees[i][0]/y->donnees[i][1];
	}
      else
	{
	  if (y->donnees[i][0]!=0.0)
	    {
	      y->donnees[i][2]=100.0;

	    }
	  else
	    {
	      y->donnees[i][1]=1.0;

	    }
	}
      y1->donnees[i][2]=y->donnees[i][2];
    }
}

Matrice sub_mdr(Matrice *tmp,Matrice *mat2,int i)
{

  int j=0,k=0,m=0;
  int nl1=(*tmp)->nbLignes;
  int nl2=(*mat2)->nbLignes;
  Matrice resu;
  Vecteur col=vecteurAlloc(nl1);
  allocMatrice(&resu,nl2,nl1+1);
 
    for (j=0;j<nl2;j++)
    {
      resu->donnees[j][0]=(*mat2)->donnees[j][0];
    }

  for (j=0;j<nl1;j++)
    {
      col->donnees[j]=((*tmp)->donnees[j][i]);
    }
  
  for (j=0;j<nl1;j++)
    {
      m=col->donnees[j];
      for (k=0;k<nl2;k++)
	{
	  resu->donnees[k][j+1]=(*mat2)->donnees[k][m];
	}      
    }
  libererVecteur(&col);
  return resu;
}

double somme1(Matrice y,double seuil)
{
  double somme=0.0;
  int i=0;
  int nl=y->nbLignes;
  for(i=0;i<nl;i++)
    {
      if (y->donnees[i][2]<seuil)
	{
	  somme+=y->donnees[i][0];
	}
      if (y->donnees[i][2]>seuil)
      	{
	  somme+=y->donnees[i][1];
	}
    }

  return somme;
}

double somme2(Matrice y, double seuil)
{
  int i;

  double somme=0.0;
  int nl=y->nbLignes;
  for(i=0;i<nl;i++)
    {
      if (y->donnees[i][2]!=seuil)
	{
	  somme+=y->donnees[i][0]+y->donnees[i][1];
	}
    }

  return somme;
}


int mdr(int *pnltmp34,int *pnc,int *pnlxx, int *pnlyy,int *pncxx,int *pnltmp, int *pnctmp, double  *ptmp, double *ptmp3, double *ptmp4, double *pxx, double *pyy ,double *z, double *zz, double *pseuil)

{
  int nltmp34=*pnltmp34;
  int nc=*pnc;
  int nlxx=*pnlxx; 
  int ncxx=*pncxx;
  int nlyy=*pnlyy;
  int nltmp=*pnltmp;
  int nctmp=*pnctmp; 
  double seuil=*pseuil;
  Matrice tmp,tmp3,tmp4,xx,yy;
  Matrice zbis;
  Matrice zzbis;
  Matrice y; 
  Matrice y1; 
  int i;
  int count=0;
  int lio=0;
  double s1;
  double s2;
  double s3;
  Vecteur y01;
  Vecteur y00;
  Vecteur y10;
  Vecteur y11;
  lectureMatrice(&tmp,ptmp,nltmp,nctmp);
  lectureMatrice(&tmp4,ptmp4, nltmp34,nc);
  lectureMatrice(&tmp3,ptmp3, nltmp34,nc);
  lectureMatrice(&xx,pxx, nlxx,ncxx);
  lectureMatrice(&yy,pyy, nlyy,ncxx);
  allocMatrice(&zbis,nctmp,1);
  allocMatrice(&zzbis,nctmp,1);
  allocMatrice(&y,nltmp34,3);
  allocMatrice(&y1,nltmp34,3);
   
  for(count=0;count<nctmp;count++)
    {
      Matrice sub = sub_mdr(&tmp,&xx,count);
      Matrice sub1 = sub_mdr(&tmp,&yy,count);
      y01=boucle2(tmp4,sub);
      y00=boucle2(tmp3,sub);
      y10=boucle2(tmp3,sub1); 
      y11=boucle2(tmp4,sub1);
    
      libererMatrice(&sub);
      libererMatrice(&sub1);
      
      for (lio=0;lio<nltmp34;lio++)
	{
	  y->donnees[lio][0]=y00->donnees[lio];
	  y->donnees[lio][1]=y01->donnees[lio];
	  y->donnees[lio][2]=0.0;
	  y1->donnees[lio][0]=y10->donnees[lio];
	  y1->donnees[lio][1]=y11->donnees[lio];
	  y1->donnees[lio][2]=0.0;
	}
      
      libererVecteur(&y01);
      libererVecteur(&y00);
      libererVecteur(&y10);
      libererVecteur(&y11);
      div_col(y,y1);
      s1=somme1(y,seuil);
      s2=somme2(y1,seuil);
      s3=somme1(y1,seuil);
      zbis->donnees[count][0] = (double)((100.0 * s1) / nlxx);
      if (s2!=0.0)
	{
	  zzbis->donnees[count][0]= (double)((100.0 * s3)/s2);
	}
      else
	{
	  zzbis->donnees[count][0]=(double)(100.0);
	}
      
      initMatrice(&y);
      initMatrice(&y1);
      }
  libererMatrice(&y);
  libererMatrice(&y1);
  libererMatrice(&tmp);
  libererMatrice(&xx);
  libererMatrice(&yy);
  libererMatrice(&tmp3);
  libererMatrice(&tmp4);
   
  for (i=0;i<zbis->nbLignes;i++)
    {
      z[i]=(double)(zbis->donnees[i][0]);
      zz[i]=(double)(zzbis->donnees[i][0]);
    }
  
  libererMatrice(&zbis);
  libererMatrice(&zzbis);
  return 1;
}
