#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define dimension_pion 27
#define cadre 16
#define marge 10
#define pas 37
#define grand_pas 48
#define taille 7
#define profondeur 2

enum{vide,noir,blanc};//vide:0 noir:1 blanc:2

int tour =0;

int grille[7][7]; // initialisée par 0=vide


int machine1[4]={0,0,0,0};// les coordonee ou la machine va jouer et ou la machine va jouer le moulin
int machine2[6]={0,0,0,0,0,0};
//-----------------------------------------------------------------------------------------------


int moulin_noir_fils(int i,int j,int fils[7][7])//fonction qui va nous permettre si la case  appartiennet  à un moulin
{
    int k=i,l=j,compteur=0,nb_moulin=0;
    l=0;// vrification pour les lignes
    if(i!=3)
    {
        while(l<7)
        {
            if(est_une_case_valide(k,l) && fils[k][l]==noir)
            {
                ++compteur;
            }
            ++l;
        }
        if(compteur==3)//s'il y a 3 cases noirs(moulin)
        {
            ++nb_moulin;
        }
        compteur=0;
    }
    else
    {
        if(j<3)
        {
            while(l<3) // si la case est dans la ligne4 on verifie les 3 premiers cases
           {
             if(est_une_case_valide(k,l) && fils[k][l]==noir)
             {
                 ++compteur;
             }
             ++l;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }
          compteur=0;
        }
        else// sinon on verifie les 3 derniers cases
        {
            l=4;
            while(l<7)
           {
             if(est_une_case_valide(k,l) && fils[k][l]==noir)
             {
                 ++compteur;
             }
             ++l;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }

        }

    }
    l=j;k=0;//verification pour les colonnes
    compteur=0;
    if(j!=3)
    {
        while(k<7)
        {
            if(est_une_case_valide(k,l) && fils[k][l]==noir)
            {
                ++compteur;
            }
            ++k;
        }
        if(compteur==3)//s'il y a 3 cases noirs(moulin)
        {
            ++nb_moulin;
        }
        compteur=0;
    }
    else
    {
        if(i<3)
        {
            while(k<3) // si la case est dans la colonne 4 on verifie les 3 premiers cases
           {
             if(est_une_case_valide(k,l) && fils[k][l]==noir)
             {
                 ++compteur;
             }
             ++k;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }
          compteur=0;
        }
          else// sinon on verifie les 3 derniers cases
        {
            k=4;
            while(k<7)
           {
             if(est_une_case_valide(k,l) && fils[k][l]==noir)
             {
                 ++compteur;
             }
             ++k;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }
          compteur=0;

        }

    }
    return (nb_moulin>=1);

}


int moulin_blanc_fils(int i,int j,int fils[7][7])//fonction qui va nous permettre si la case  appartiennet  à un moulin
{
    int k=i,l=j,compteur=0,nb_moulin=0;
    l=0;// vrification pour les lignes
    if(i!=3)
    {
        while(l<7)
        {
            if(est_une_case_valide(k,l) && fils[k][l]==blanc)
            {
                ++compteur;
            }
            ++l;
        }
        if(compteur==3)//s'il y a 3 cases noirs(moulin)
        {
            ++nb_moulin;
        }
        compteur=0;
    }
    else
    {
        if(j<3)
        {
            while(l<3) // si la case est dans la ligne4 on verifie les 3 premiers cases
           {
             if(est_une_case_valide(k,l) && fils[k][l]==blanc)
             {
                 ++compteur;
             }
             ++l;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }
          compteur=0;
        }
        else// sinon on verifie les 3 derniers cases
        {
            l=4;
            while(l<7)
           {
             if(est_une_case_valide(k,l) && fils[k][l]==blanc)
             {
                 ++compteur;
             }
             ++l;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }

        }

    }
    l=j;k=0;//verification pour les colonnes
    compteur=0;
    if(j!=3)
    {
        while(k<7)
        {
            if(est_une_case_valide(k,l) && fils[k][l]==blanc)
            {
                ++compteur;
            }
            ++k;
        }
        if(compteur==3)//s'il y a 3 cases noirs(moulin)
        {
            ++nb_moulin;
        }
        compteur=0;
    }
    else
    {
        if(i<3)
        {
            while(k<3) // si la case est dans la colonne 4 on verifie les 3 premiers cases
           {
             if(est_une_case_valide(k,l) && fils[k][l]==blanc)
             {
                 ++compteur;
             }
             ++k;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }
          compteur=0;
        }
          else// sinon on verifie les 3 derniers cases
        {
            k=4;
            while(k<7)
           {
             if(est_une_case_valide(k,l) && fils[k][l]==blanc)
             {
                 ++compteur;
             }
             ++k;
           }
            if(compteur==3)//s'il y a 3 cases noirs(moulin)
          {
             ++nb_moulin;
          }
          compteur=0;

        }

    }
    return (nb_moulin>=1);

}




//---------------------------------------------------------------
//minmax
int h(int n[7][7])
{
        int nb_pionn=0,nb_pionb=0;//nombre de pions noirs et nombre de pions blanches
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (n[i][j]==noir))
            {
                ++nb_pionn;
            }
        }
    }
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (n[i][j]==blanc))
            {
                ++nb_pionb;
            }
        }
    }
    return(nb_pionb-nb_pionn);
}

int etat_final1() // on atteint l'etat finale si les deux joueurs ont posé leurs 9 pions
{

    return(tour==18);
}



int minmax1(int n[7][7], int p,int couleur)
{
    if((etat_final1()) || p==0)
    {

        return h(n);
    }
    else
    {
        if(couleur==blanc) // c'est le joueur max qui commence  donc max est blanc
        {

        int max=-30;
        int fils[7][7];
        int fils_moulin[7][7];

//on genere les fils
        for(int i=0;i<taille;++i) // a chaque fois on pose un pion s'il est possible
        {
            for(int j=0;j<taille;++j)
          {
              if(est_une_case_valide(i,j) )
              {
                if(n[i][j]==vide)
                {
                      for(int k=0;k<taille;++k) // on copie l'etat actuel
                      {
                          for(int l=0;l<taille;++l)
                         {
                         fils[k][l]=n[k][l];
                         }
                      }
                    fils[i][j]=blanc;// s'il n'y a pas un moulin : alors voila le fils genere
                    if(moulin_blanc_fils(i,j,fils))
                    {
                       for(int k=0;k<taille;++k) // on applique la regle du moulin pour toute case possible
                      {
                          for(int l=0;l<taille;++l)
                         {
                             if(est_une_case_valide(k,l))
                             {

                               if(fils[k][l]==noir)
                              {
                                if(!moulin_noir_fils(k,l,fils))
                                {
                                      for(int k=0;k<taille;++k) // on copie le fils actuel
                                  {
                                         for(int l=0;l<taille;++l)
                                        {
                                             fils_moulin[k][l]=fils[k][l];
                                        }
                                  }

                                    fils_moulin[k][l]=vide; // voila un fils genere
                                    ++tour;
                                    if(minmax1(fils_moulin,p-1,noir)>max)
                                    {
                                        max=minmax1(fils_moulin,p-1,noir);
                                        machine1[0]=i;machine1[1]=j; // ou va jouer la machine
                                        machine1[2]=k;machine1[3]=l; // ou va jouer la machine le moulin

                                    }
                                }
                              }
                           }
                         }
                      }
                    }
                    else
                    {
                        ++tour;
                        if(minmax1(fils,p-1,noir)>max)
                          {
                             max=minmax1(fils,p-1,noir);
                             machine1[0]=i;machine1[1]=j; // ou va jouer la machine
                             machine1[2]=-1;machine1[3]=-1; // s'il n'y a pas de moulin on choisit par default -1 -1
                          }
                    }
                }

              }

          }
        }
        return max;
      }
      else  // si tour du min:noir
      {
          int min=30;
          int fils[7][7];
          int fils_moulin[7][7];

//on genere les fils
        for(int i=0;i<taille;++i) // a chaque fois on pose un pion s'il est possible
        {
            for(int j=0;j<taille;++j)
          {
              if(est_une_case_valide(i,j) )
              {
                if(n[i][j]==vide)
                {
                      for(int k=0;k<taille;++k) // on copie l'etat actuel
                      {
                          for(int l=0;l<taille;++l)
                         {
                         fils[k][l]=n[k][l];

                         }
                      }
                    fils[i][j]=noir;// s'il n'y a pas un moulin : alors voila le fils genere
                    if(moulin_noir_fils(i,j,fils))
                    {
                       for(int k=0;k<taille;++k) // on applique la regle du moulin pour toute case possible
                      {
                          for(int l=0;l<taille;++l)
                         {
                             if(est_une_case_valide(k,l))
                             {

                               if(fils[k][l]==blanc)
                              {
                                if(!moulin_blanc_fils(k,l,fils))
                                {
                                    for(int k=0;k<taille;++k) // on copie le fils actuel
                                  {
                                         for(int l=0;l<taille;++l)
                                        {
                                             fils_moulin[k][l]=fils[k][l];
                                        }
                                  }
                                    fils_moulin[k][l]=vide; // voila un fils genere
                                    ++tour;
                                    if(minmax1(fils_moulin,p-1,blanc)<min)
                                    {
                                        min=minmax1(fils_moulin,p-1,blanc);

                                    }
                                }
                              }
                           }
                         }
                      }
                    }
                    else
                    {
                        ++tour;
                        if(minmax1(fils,p-1,blanc)<min)
                            {
                                min=minmax1(fils,p-1,blanc);
                            }
                    }
                }

              }

          }
        }

        return min;
      }

    }
}






void copierGrille(int de[7][7], int a[7][7]){
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            a[i][j]=de[i][j];

        }
    }
}




int minimax2(int gr[7][7],int p, int couleur){
    if (p==0 || impossible_de_jouer_blanc()==1 || impossible_de_jouer_noir()==1){
        return h(gr);
    }
    int eval=0;
    if(couleur==blanc){
        int maxEval=-9999;
        int fils[7][7];
        int fils_moulin[7][7];

        for (int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if (est_une_case_valide(i,j) && gr[i][j]==couleur ){
                    int k=i,l=j;
                    if(k<6){
                        k++;
                        if (l!=3){
                            while(!est_une_case_valide(k,l) && k<6){
                                ++k;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && k<3){
                                ++k;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_blanc_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==noir && moulin_noir_fils(n,m,fils)==0 ){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine2[0]=i;machine2[1]=j;
                                            machine2[2]=k;machine2[3]=l;
                                            machine2[4]=n;machine2[5]=m;
                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine2[0]=i;machine2[1]=j;
                                machine2[2]=k;machine2[3]=l;
                                machine2[4]=-1;machine2[5]=-1;
                            }
                        }
                    }

                    k=i;l=j;
                    if(k>0){
                        k--;
                        if (l!=3){
                            while(!est_une_case_valide(k,l) && k>0){
                                --k;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && k>3){
                                --k;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_blanc_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==noir && moulin_noir_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine2[0]=i;machine2[1]=j;
                                            machine2[2]=k;machine2[3]=l;
                                            machine2[4]=n;machine2[5]=m;
                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine2[0]=i;machine2[1]=j;
                                machine2[2]=k;machine2[3]=l;
                                machine2[4]=-1;machine2[5]=-1;
                            }
                        }
                    }

                    k=i;l=j;
                    if(l>0){
                        --l;
                        if (k!=3){
                            while(!est_une_case_valide(k,l) && l>0){
                                --l;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && l>3){
                                --l;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_blanc_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==noir && moulin_noir_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine2[0]=i;machine2[1]=j;
                                            machine2[2]=k;machine2[3]=l;
                                            machine2[4]=n;machine2[5]=m;
                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine2[0]=i;machine2[1]=j;
                                machine2[2]=k;machine2[3]=l;
                                machine2[4]=-1;machine2[5]=-1;
                            }
                        }
                    }

                    k=i;l=j;
                    if(l<6){
                        ++l;
                        if (k!=3){
                            while(!est_une_case_valide(k,l) && l<6){
                                ++l;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && l<3){
                                ++l;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_blanc_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==noir && moulin_noir_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine2[0]=i;machine2[1]=j;
                                            machine2[2]=k;machine2[3]=l;
                                            machine2[4]=n;machine2[5]=m;
                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine2[0]=i;machine2[1]=j;
                                machine2[2]=k;machine2[3]=l;
                                machine2[4]=-1;machine2[5]=-1;
                            }
                        }
                    }
                }
            }
        }
        return maxEval;
    }
    else{
        int minEval=9999;
        int fils[7][7];
        int fils_moulin[7][7];

        for (int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if (est_une_case_valide(i,j) && gr[i][j]==couleur ){
                    int k=i,l=j;
                    if(k<6){
                        k++;
                        if (l!=3){
                            while(!est_une_case_valide(k,l) && k<6){
                                ++k;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && k<3){
                                ++k;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_noir_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==blanc && moulin_blanc_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                        }
                    }

                    k=i;l=j;
                    if(k>0){
                        k--;
                        if (l!=3){
                            while(!est_une_case_valide(k,l) && k>0){
                                --k;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && k>3){
                                --k;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_noir_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==blanc && moulin_blanc_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                        }
                    }

                    k=i;l=j;
                    if(l>0){
                        --l;
                        if (k!=3){
                            while(!est_une_case_valide(k,l) && l>0){
                                --l;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && l>3){
                                --l;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_noir_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==blanc && moulin_blanc_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                        }
                    }

                    k=i;l=j;
                    if(l<6){
                        ++l;
                        if (k!=3){
                            while(!est_une_case_valide(k,l) && l<6){
                                ++l;
                            }
                        }else{
                            while(!est_une_case_valide(k,l) && l<3){
                                ++l;
                            }
                        }
                    }
                    if(est_une_case_valide(k,l) && gr[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_noir_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==blanc && moulin_blanc_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax2(fils_moulin,p-1,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                    }
                                }
                            }
                        }else{
                            eval=minimax2(fils,p-1,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                        }
                    }
                }
            }
        }
        return minEval;
    }
}

int minimax3(int gr[7][7],int p, int couleur){
    if (p==0 || impossible_de_jouer_blanc()==1 || impossible_de_jouer_noir()==1){
        return h(gr);
    }
    int eval=0;
    if(couleur==blanc){
        int maxEval=-9999;
        int fils[7][7];
        int fils_moulin[7][7];

        for (int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if (est_une_case_valide(i,j) && gr[i][j]==couleur ){
                    for (int k=0;k<7;k++){
                        for(int l=0;l<7;l++){
                            if(est_une_case_valide(k,l) && gr[k][l]==vide){
                                copierGrille(gr,fils);
                                fils[k][l]=couleur;
                                fils[i][j]=vide;
                            }
                            if(moulin_blanc_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==noir && moulin_noir_fils(n,m,fils)==0 ){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax3(fils_moulin,p-1,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine2[0]=i;machine2[1]=j;
                                            machine2[2]=k;machine2[3]=l;
                                            machine2[4]=n;machine2[5]=m;
                                        }
                                    }
                                }
                            }
                            }else{
                            eval=minimax3(fils,p-1,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine2[0]=i;machine2[1]=j;
                                machine2[2]=k;machine2[3]=l;
                                machine2[4]=-1;machine2[5]=-1;
                            }
                            }
                        }
                    }
                }
            }
        }
        return maxEval;
    }
    else{
        int minEval=9999;
        int fils[7][7];
        int fils_moulin[7][7];

        for (int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if (est_une_case_valide(i,j) && gr[i][j]==couleur ){
                    for (int k=0;k<7;k++){
                        for(int l=0;l<7;l++){
                            if(est_une_case_valide(k,l) && gr[k][l]==vide){
                                copierGrille(gr,fils);
                                fils[k][l]=couleur;
                                fils[i][j]=vide;
                            }
                            if(moulin_noir_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==blanc && moulin_blanc_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=minimax3(fils_moulin,p-1,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                    }
                                }
                            }
                            }else{
                            eval=minimax3(fils,p-1,blanc);
                            if (minEval>eval){
                                minEval=eval;
                            }
                            }
                        }
                    }
                }
            }
        }
        return minEval;
    }
}











int joueur_vs_machine()
{
    int *case_choisie=(int*)malloc(2*sizeof(int));
   int minmax=0;
     int etat_actuel[7][7];


   if(SDL_Init(SDL_INIT_VIDEO)!=0)
   {
       SDL_Log("Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
   }

    TTF_Init();
     SDL_Window *window=NULL;

    SDL_Renderer *renderer=NULL;

   window=SDL_CreateWindow("fenetre",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);

   if(window==NULL)
   {
       SDL_Log("Échec de creation window(%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
   }
   renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

   if(renderer==NULL)
   {
       SDL_Log("Échec de creation du rendu(%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
   }



   int hauteur,largeur;

   SDL_Surface *image=NULL;
   SDL_Surface *image1=NULL;
   SDL_Surface *image_pion_noir=NULL;
   SDL_Surface *image_pion_blanc=NULL;
   SDL_Surface *support1=NULL;
   SDL_Surface *support2=NULL;
   SDL_Surface *image_joueur1=NULL;
   SDL_Surface *image_joueur2=NULL;
   SDL_Surface *image_boutton=NULL;

   image=IMG_Load("grille.jpg");
   image1=IMG_Load("background.jpg");
   image_boutton=IMG_Load("boutton.png");

    image_pion_noir=IMG_Load("pion_noir.jpg");
    image_pion_blanc=IMG_Load("pion_blanc.jpg");
    support1=IMG_Load("emplacement.png");
    support2=IMG_Load("emplacement.png");
    image_joueur1=IMG_Load("icone_joueur1.png");
    image_joueur2=IMG_Load("icone_robot.png");
   SDL_SetColorKey(image_pion_noir,SDL_TRUE,SDL_MapRGB(image_pion_noir->format,255,255,255));
   SDL_SetColorKey(image_pion_blanc,SDL_TRUE,SDL_MapRGB(image_pion_blanc->format,0,0,0));



   SDL_Texture* texture=NULL;
   SDL_Texture* arriere=NULL;
   SDL_Texture* texture1=NULL;
   SDL_Texture* texture2=NULL;
   SDL_Texture  *texture_noir[9]={NULL};
   SDL_Texture  *texture_blanc[9]={NULL};
   SDL_Texture* texture_j1=NULL;
   SDL_Texture* texture_j2=NULL;
   SDL_Texture* texture_jouer_en_noir=NULL;
   SDL_Texture* texture_jouer_en_blanc=NULL;
   SDL_Texture* texture_boutton=NULL;
   for(int i=0;i<9;++i)
   {
        texture_noir[i]=SDL_CreateTextureFromSurface(renderer,image_pion_noir);
   }
   for(int i=0;i<9;++i)
   {
        texture_blanc[i]=SDL_CreateTextureFromSurface(renderer,image_pion_blanc);
   }
   for(int i=0;i<9;++i)
   {
        if(texture_noir[i]==NULL)
        {
        SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Log("Échec de creation de texture(%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
        }
   }
   for(int i=0;i<9;++i)
   {
        if(texture_blanc[i]==NULL)
        {
        SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Log("Échec de creation de texture(%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
        }
   }

   texture=SDL_CreateTextureFromSurface(renderer,image);
   arriere=SDL_CreateTextureFromSurface(renderer,image1);
   texture1=SDL_CreateTextureFromSurface(renderer,support1);
   texture2=SDL_CreateTextureFromSurface(renderer,support2);
   texture_j1=SDL_CreateTextureFromSurface(renderer,image_joueur1);
   texture_j2=SDL_CreateTextureFromSurface(renderer,image_joueur2);
   texture_jouer_en_noir=SDL_CreateTextureFromSurface(renderer,image_pion_noir);
   texture_jouer_en_blanc=SDL_CreateTextureFromSurface(renderer,image_pion_blanc);
   texture_boutton=SDL_CreateTextureFromSurface(renderer,image_boutton);
   SDL_QueryTexture(texture,NULL,NULL,&largeur,&hauteur);


   SDL_Rect pion_noir[9];
   SDL_Rect pion_blanc[9];
   for(int i=0;i<9;++i)
   {
        pion_noir[i].h=dimension_pion;pion_noir[i].w=dimension_pion;
        pion_blanc[i].h=dimension_pion;pion_blanc[i].w=dimension_pion;
   }

   SDL_Rect emplacement;
   emplacement.h=hauteur+100;emplacement.w=largeur+100;
   emplacement.x=(800-emplacement.w)/2;
   emplacement.y=(600-emplacement.h)/2;

   SDL_Rect boutton_menu;

   boutton_menu.h=25;boutton_menu.w=77;
   boutton_menu.x=(800-boutton_menu.w)/2;boutton_menu.y=0;


   SDL_Rect background;
   background.h=600;background.w=800;
   background.x=0;
   background.y=0;


   SDL_Rect rec_noir;SDL_Rect rec_blanc;
   rec_blanc.w=rec_noir.w=5*dimension_pion;
   rec_blanc.h=rec_noir.h=2*dimension_pion;
   rec_noir.x=emplacement.x+emplacement.w+(800-(emplacement.x+emplacement.w)-rec_noir.w)/2;
   rec_noir.y=emplacement.y+(emplacement.h)/2 ;
   rec_blanc.y=rec_noir.y;
   rec_blanc.x=(800-(emplacement.x+emplacement.w)-rec_noir.w)/2;


   for(int i=0;i<4;++i)
   {
        pion_noir[i].x=rec_noir.x+i*dimension_pion;
        pion_noir[i].y=rec_noir.y;
   }
   for(int i=4;i<8;++i)
   {
        pion_noir[i].x=rec_noir.x+(i-4)*dimension_pion;
        pion_noir[i].y=rec_noir.y+dimension_pion;
   }
   pion_noir[8].x=rec_noir.x+4*dimension_pion;
   pion_noir[8].y=rec_noir.y+dimension_pion/2;




   for(int i=0;i<4;++i)
   {
        pion_blanc[i].x=rec_blanc.x+i*dimension_pion;
        pion_blanc[i].y=rec_blanc.y;
   }
   for(int i=4;i<8;++i)
   {
        pion_blanc[i].x=rec_blanc.x+(i-4)*dimension_pion;
        pion_blanc[i].y=rec_blanc.y+dimension_pion;
   }
   pion_blanc[8].x=rec_blanc.x+4*dimension_pion;
   pion_blanc[8].y=rec_blanc.y+dimension_pion/2;


   SDL_Rect icone1;SDL_Rect icone2;

   icone2.h=icone2.w=icone1.w=icone1.h=3*dimension_pion;
   icone1.x=rec_noir.x+dimension_pion;
   icone1.y=rec_noir.y-icone1.h;
   icone2.x=rec_blanc.x+dimension_pion;
   icone2.y=rec_blanc.y-icone2.h;





   SDL_Rect jouer_en_noir;SDL_Rect jouer_en_blanc;
   jouer_en_noir.h=jouer_en_noir.w=jouer_en_blanc.h=jouer_en_blanc.w=dimension_pion;
   jouer_en_noir.x=rec_noir.x+rec_noir.w;
   jouer_en_blanc.x=rec_blanc.x-dimension_pion;
   jouer_en_blanc.y=jouer_en_noir.y=rec_noir.y+dimension_pion/2;



   SDL_Event event;
   int jouer_noir=1;int jouer_blanc=1;
   int moulin_n=2;int moulin_b=2;
   int positionner_n=3,positionner_b=3;
   int action_noir=jouer_noir;

   int indice_noir=0; // indice du tableau des pions noires
   int indice_blanc=0; // indice du tableau des pions blanches
   int detruire_case_noire[9]={0};
   int detruire_case_blanche[9]={0};
   int compte_tour=0;
   int vraie=SDL_TRUE;
   int choix_i,choix_j;


   while(vraie)
   {
       SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,arriere,NULL,&background);
   SDL_RenderCopy(renderer,texture,NULL,&emplacement);
   SDL_RenderCopy(renderer,texture_boutton,NULL,&boutton_menu);

   SDL_RenderCopy(renderer,texture_jouer_en_noir,NULL,&jouer_en_noir);
   SDL_RenderCopy(renderer,texture_jouer_en_blanc,NULL,&jouer_en_blanc);
   SDL_RenderCopy(renderer,texture1,NULL,&rec_noir);
   SDL_RenderCopy(renderer,texture2,NULL,&rec_blanc);
   SDL_RenderCopy(renderer,texture_j1,NULL,&icone1);
   SDL_RenderCopy(renderer,texture_j2,NULL,&icone2);
   for(int i=0;i<9;++i)
   {
        if(!detruire_case_noire[i])
        SDL_RenderCopy(renderer,texture_noir[i],NULL,&pion_noir[i]);
        else
        {
           pion_noir[i].x=pion_noir[i].y=10;
        }

   }

   for(int i=0;i<9;++i)
   {

        for(int i=0;i<9;++i)
     {
        if(!detruire_case_blanche[i])
        SDL_RenderCopy(renderer,texture_blanc[i],NULL,&pion_blanc[i]);
        else
        {
           pion_blanc[i].x=pion_blanc[i].y=10;
        }

     }
   }



   SDL_RenderPresent(renderer);
       while(SDL_PollEvent(&event))
       {
           switch(event.type)
           {
          case SDL_QUIT:
              vraie=SDL_FALSE;
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
               {
                   if(cliquer_sur_rect(boutton_menu.x,boutton_menu.y,boutton_menu.h,boutton_menu.w,event))
                   {
                       printf("menu\n");
                       main(0,"");
                   }
                else
              {
                  case_choisie=la_case_cliquee(event.button.x,event.button.y,event,emplacement);


                 if(compte_tour<9) //phase1
                {

                         if(action_noir==jouer_noir)
                         {

                           if(inserer_un_pion_noir(case_choisie[0],case_choisie[1]))
                          {
                            poser_dans(case_choisie[0],case_choisie[1],&pion_noir[indice_noir],&emplacement);
                            ++indice_noir;
                              if((moulin_noir(case_choisie[0],case_choisie[1]))&&(nb_blanc()!=0))
                             {
                                 printf("choisit le pion blanc a retirer\n");
                                action_noir=moulin_n;
                             }
                             else
                             {
                                 ++compte_tour;
                                 tour=compte_tour;
                                 for(int k=0;k<taille;++k) // on copie l'etat actuel
                               {
                                    for(int l=0;l<taille;++l)
                                 {
                                        etat_actuel[k][l]=grille[k][l];
                                 }
                               }
                                  minmax=minmax1(etat_actuel,profondeur,blanc); //on va considerer que le joueur 2 joue en blanc
                                  grille[machine1[0]][machine1[1]]=blanc;//on insere le choix de la machine

                                  poser_dans(machine1[0],machine1[1],&pion_blanc[indice_blanc],&emplacement);
                                  ++indice_blanc;
                                  if((machine1[2]!=-1) && (machine1[3]!=-1) ) // s'il y a un moulin pour la machine
                                 {
                                    grille[machine1[2]][machine1[3]]=vide;//on insere le choix de la machine
                                    int indice=indice_de_la_case(machine1[2],machine1[3],pion_noir,emplacement);
                                   if(indice!=9)
                                   {detruire_case_noire[indice]=1;}

                                 }
                                 tour=compte_tour+1;
                             }



                          }
                         }
                         else if(action_noir==moulin_n)
                         {


                               if(retirer_case_blanche(case_choisie[0],case_choisie[1],&tour)) //si on peut retirer la case cible
                               {
                                   int indice=indice_de_la_case(case_choisie[0],case_choisie[1],pion_blanc,emplacement);
                                   if(indice!=9)
                                   {detruire_case_blanche[indice]=1;}
                                   compte_tour++;
                                   tour=compte_tour;


                                   for(int k=0;k<taille;++k) // on copie l'etat actuel
                               {
                                    for(int l=0;l<taille;++l)
                                 {
                                        etat_actuel[k][l]=grille[k][l];
                                 }
                               }
                                  minmax=minmax1(etat_actuel,profondeur,blanc); //on va considerer que le joueur 2 joue en blanc
                                  grille[machine1[0]][machine1[1]]=blanc;//on insere le choix de la machine

                                  poser_dans(machine1[0],machine1[1],&pion_blanc[indice_blanc],&emplacement);
                                  ++indice_blanc;
                                  if((machine1[2]!=-1) && (machine1[3]!=-1) ) // s'il y a un moulin pour la machine
                                 {
                                    grille[machine1[2]][machine1[3]]=vide;//on insere le choix de la machine
                                    int indice2=indice_de_la_case(machine1[2],machine1[3],pion_noir,emplacement);
                                   if(indice2!=9)
                                   {detruire_case_noire[indice2]=1;}

                                 }
                                   tour=compte_tour+1;
                                   action_noir=jouer_noir;

                               }



                         }


                   }
                   else //phase2
                   {
                        if (impossible_de_jouer_noir()==1)
                        {
                            printf("fin du jeu le joueur2 a gannee\n");
                            return 0;
                        }
                        else if (impossible_de_jouer_noir()==1)
                        {
                            printf("fin du jeu le joueur1 a gannee\n");
                            return 0;
                        }
                            else{
                        if(action_noir==jouer_noir)
                         {
                           case_choisie=la_case_cliquee(event.button.x,event.button.y,event,emplacement);
                           if (est_une_case_valide(case_choisie[0],case_choisie[1]) ){
                                if (grille[case_choisie[0]][case_choisie[1]]==noir){
                                if(nb_noir()>3 && verifier_deplacement_noir(case_choisie[0],case_choisie[1])){
                                    choix_i=case_choisie[0];
                                    choix_j=case_choisie[1];
                                    action_noir=positionner_n;
                                    printf("Choisir le positionnement\n");
                                }else if(nb_noir()==3){
                                    choix_i=case_choisie[0];
                                    choix_j=case_choisie[1];
                                    action_noir=positionner_n;
                                    printf("Choisir le positionnement\n");
                                }
                           }else{
                               printf("Veuillez choisir une case valide\n");
                           }
                           }
                         }

                           else if(action_noir==positionner_n)
                           {
                               case_choisie=la_case_cliquee(event.button.x,event.button.y,event,emplacement);
                               if(jouer_un_pion_noir(choix_i,choix_j,case_choisie[0],case_choisie[1]))
                                {
                                    indice_noir=indice_de_la_case(choix_i,choix_j,pion_noir,emplacement);
                                    if(indice_noir!=9)
                                   {
                                    poser_dans(case_choisie[0],case_choisie[1],&pion_noir[indice_noir],&emplacement);
                                    if((moulin_noir(case_choisie[0],case_choisie[1]))&&(nb_blanc()!=0))
                                    {
                                        printf("choisit le pion blanc a retirer\n");
                                        action_noir=moulin_n;
                                    }
                                    else{
                                 for(int k=0;k<taille;++k) // on copie l'etat actuel
                               {
                                    for(int l=0;l<taille;++l)
                                 {
                                        etat_actuel[k][l]=grille[k][l];
                                 }
                               }
                                  if(nb_blanc()==3)
                                {
                                 minmax=minimax3(etat_actuel,profondeur,blanc); //on va considerer que le joueur 2 joue en blanc
                                }else{
                                 minmax=minimax2(etat_actuel,profondeur,blanc);
                                }
                                  grille[machine2[0]][machine2[1]]=vide;
                                  grille[machine2[2]][machine2[3]]=blanc;
                                  indice_blanc=indice_de_la_case(machine2[0],machine2[1],pion_blanc,emplacement);
                                    if(indice_blanc!=9)
                                   {
                                    poser_dans(machine2[2],machine2[3],&pion_blanc[indice_blanc],&emplacement);
                                    if((machine1[2]!=-1) && (machine1[3]!=-1) )
                                    {
                                        grille[machine2[4]][machine2[5]]=vide;
                                        int indice=indice_de_la_case(machine2[4],machine2[5],pion_noir,emplacement);
                                    if(indice!=9)
                                    {detruire_case_noire[indice]=1;}

                                    }
                                    }
                                    action_noir=jouer_noir;
                           }
                                   }
                                }else{
                                    printf("Veuillez choisir une case valide \n");
                                }
                           }
                            else if(action_noir==moulin_n)
                            {
                                case_choisie=la_case_cliquee(event.button.x,event.button.y,event,emplacement);


                               if(retirer_case_blanche(case_choisie[0],case_choisie[1],&tour)) //si on peut retirer la case cible
                               {
                                   int indice=indice_de_la_case(case_choisie[0],case_choisie[1],pion_blanc,emplacement);
                                   if(indice!=9)
                                   {detruire_case_blanche[indice]=1;
                                action_noir=jouer_noir;}


                                 for(int k=0;k<taille;++k) // on copie l'etat actuel
                               {
                                    for(int l=0;l<taille;++l)
                                 {
                                        etat_actuel[k][l]=grille[k][l];
                                 }
                               }
                                  if(nb_blanc()==3)
                                {
                                 minmax=minimax3(etat_actuel,profondeur,blanc); //on va considerer que le joueur 2 joue en blanc
                                }else{
                                 minmax=minimax2(etat_actuel,profondeur,blanc);
                                }
                                  grille[machine2[0]][machine2[1]]=vide;
                                  grille[machine2[2]][machine2[3]]=blanc;
                                  indice_blanc=indice_de_la_case(machine2[0],machine2[1],pion_blanc,emplacement);
                                    if(indice_blanc!=9)
                                   {
                                    poser_dans(machine2[2],machine2[3],&pion_blanc[indice_blanc],&emplacement);
                                    if((machine1[2]!=-1) && (machine1[3]!=-1) )
                                    {
                                        grille[machine2[4]][machine2[5]]=vide;
                                        int indice=indice_de_la_case(machine2[4],machine2[5],pion_noir,emplacement);
                                    if(indice!=9)
                                    {detruire_case_noire[indice]=1;}

                                    }
                                    }
                                    action_noir=jouer_noir;
                           }
                            }


                    }

                    }

                   }
                  }

            break;



          default:
            break;
           }
       }


   }











   SDL_DestroyTexture(arriere);
   SDL_DestroyTexture(texture);
   SDL_DestroyTexture(texture_jouer_en_noir);
    SDL_DestroyTexture(texture_jouer_en_blanc);
   SDL_DestroyTexture(texture1);
   SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture_j1);
    SDL_DestroyTexture(texture_j2);
    SDL_DestroyTexture(texture_boutton);
   for(int i=0;i<9;++i)
   {
        SDL_DestroyTexture(texture_noir[i]);
   }


   SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Quit();
   free(case_choisie);
   return 0;






}

