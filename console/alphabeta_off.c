
#include <stdio.h>
#include <stdlib.h>
#define taille 7
#define profondeur 2

enum{vide,noir,blanc};//vide:0 noir:1 blanc:2

int tour1 =0;
int infinie=300;
int grille[7][7]; // initialisée par 0=vide


int machine3[4]={0,0,0,0};// les coordonee ou la machine va jouer et ou la machine va jouer le moulin
int machine4[6]={0,0,0,0,0,0};
//-----------------------------------------------------------------------------------------------


//---------------------------------------------------------------



int alpha_beta1(int n[7][7], int p,int a,int b,int couleur)
{
    if((etat_final1()) || p==0)
    {

        return h(n);
    }
    else
    {
        int v=0;
        if(couleur==blanc) // c'est le joueur max qui commence  donc max est blanc
        {

        v=-infinie;
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
                                    ++tour1;
                                    if(alpha_beta1(fils_moulin,p-1,a,b,noir)>v)
                                    {
                                        v=alpha_beta1(fils_moulin,p-1,a,b,noir);
                                        machine3[0]=i;machine3[1]=j; // ou va jouer la machine
                                        machine3[2]=k;machine3[3]=l; // ou va jouer la machine le moulin

                                    }
                                    if(v>b){return v;}
                                    if(v>a){a=v;}
                                }
                              }
                           }
                         }
                      }
                    }
                else
                {
                        ++tour1;
                       if(alpha_beta1(fils_moulin,p-1,a,b,noir)>v)
                      {
                        v=alpha_beta1(fils_moulin,p-1,a,b,noir);
                        machine3[0]=i;machine3[1]=j; // ou va jouer la machine
                        machine3[2]=-1;machine3[3]=-1; // s'il n'y a pas de moulin on choisit par default -1 -1
                      }
                    if(v>b){return v;}
                    if(v>a){a=v;}
                }
            }

          }

         }
        }
      }
      else  // si tour du min:noir
      {
          v=infinie;
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
                                    ++tour1;
                                    if(alpha_beta1(fils_moulin,p-1,a,b,blanc)<v)
                                    {
                                        v=alpha_beta1(fils_moulin,p-1,a,b,blanc);

                                    }

                                    if(a>v){return v;}
                                    if(v<b){b=v;}
                                }
                              }
                           }
                         }
                      }
                    }
                    else
                    {
                        ++tour1;
                        if(alpha_beta1(fils_moulin,p-1,a,b,blanc)<v)
                            {
                                v=alpha_beta1(fils_moulin,p-1,a,b,blanc);

                            }

                        if(a>v){return v;}
                        if(v<b){b=v;}
                    }
                }

              }

          }
        }

      }
      return v;
    }
}


/*------------------------------------------------------------------------------------alphabeta2-------------------------------------*/







int alpha_beta2(int gr[7][7],int p,int a, int b, int couleur){
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
                        while(!est_une_case_valide(k,l) && k<6){
                            ++k;
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
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine4[0]=i;machine4[1]=j;
                                            machine4[2]=k;machine4[3]=l;
                                            machine4[4]=n;machine4[5]=m;
                                        }
                                        if(maxEval>b){return maxEval;}
                                        if(maxEval>a){a=maxEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine4[0]=i;machine4[1]=j;
                                machine4[2]=k;machine4[3]=l;
                                machine4[4]=-1;machine4[5]=-1;
                            }
                            if(maxEval>b){return maxEval;}
                            if(maxEval>a){a=maxEval;}
                        }
                    }

                    k=i;l=j;
                    if(k>0){
                        k--;
                        while(!est_une_case_valide(k,l) && k>0){
                            --k;
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
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine4[0]=i;machine4[1]=j;
                                            machine4[2]=k;machine4[3]=l;
                                            machine4[4]=n;machine4[5]=m;
                                        }
                                        if(maxEval>b){return maxEval;}
                                        if(maxEval>a){a=maxEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine4[0]=i;machine4[1]=j;
                                machine4[2]=k;machine4[3]=l;
                                machine4[4]=-1;machine4[5]=-1;
                            }
                            if(maxEval>b){return maxEval;}
                            if(maxEval>a){a=maxEval;}
                        }
                    }

                    k=i;l=j;
                    if(l>0){
                        --l;
                        while(!est_une_case_valide(k,l) && l>0){
                            --l;
                        }
                    }
                    if(est_une_case_valide(k,l) && grille[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_blanc_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==noir && moulin_noir_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine4[0]=i;machine4[1]=j;
                                            machine4[2]=k;machine4[3]=l;
                                            machine4[4]=n;machine4[5]=m;
                                        }
                                        if(maxEval>b){return maxEval;}
                                        if(maxEval>a){a=maxEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine4[0]=i;machine4[1]=j;
                                machine4[2]=k;machine4[3]=l;
                                machine4[4]=-1;machine4[5]=-1;
                            }
                            if(maxEval>b){return maxEval;}
                            if(maxEval>a){a=maxEval;}
                        }
                    }

                    k=i;l=j;
                    if(l<6){
                        l++;
                        while(!est_une_case_valide(k,l) && l<7){
                            ++l;
                        }
                    }
                    if(est_une_case_valide(k,l) && grille[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_blanc_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==noir && moulin_noir_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine4[0]=i;machine4[1]=j;
                                            machine4[2]=k;machine4[3]=l;
                                            machine4[4]=n;machine4[5]=m;
                                        }
                                        if(maxEval>b){return maxEval;}
                                        if(maxEval>a){a=maxEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine4[0]=i;machine4[1]=j;
                                machine4[2]=k;machine4[3]=l;
                                machine4[4]=-1;machine4[5]=-1;
                            }
                            if(maxEval>b){return maxEval;}
                            if(maxEval>a){a=maxEval;}
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
                        while(!est_une_case_valide(k,l) && k<6){
                            ++k;
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
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                        if(a>minEval){return minEval;}
                                        if(minEval<b){b=minEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                            if(a>minEval){return minEval;}
                            if(minEval<b){b=minEval;}
                        }
                    }

                    k=i;l=j;
                    if(k>0){
                        k--;
                        while(!est_une_case_valide(k,l) && k>0){
                            --k;
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
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                        if(a>minEval){return minEval;}
                                        if(minEval<b){b=minEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                            if(a>minEval){return minEval;}
                            if(minEval<b){b=minEval;}
                        }
                    }

                    k=i;l=j;
                    if(l>0){
                        --l;
                        while(!est_une_case_valide(k,l) && l>0){
                            --l;
                        }
                    }
                    if(est_une_case_valide(k,l) && grille[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_noir_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==blanc && moulin_blanc_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                        if(a>minEval){return minEval;}
                                        if(minEval<b){b=minEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                            if(a>minEval){return minEval;}
                            if(minEval<b){b=minEval;}
                        }
                    }

                    k=i;l=j;
                    if(l<6){
                        l++;
                        while(!est_une_case_valide(k,l) && l<7){
                            ++l;
                        }
                    }
                    if(est_une_case_valide(k,l) && grille[k][l]==vide){
                        copierGrille(gr,fils);
                        fils[k][l]=couleur;
                        fils[i][j]=vide;
                        if(moulin_noir_fils(k,l,fils)){
                            for(int n=0;i<taille;++i){
                                for(int m=0;j<taille;++j){
                                    if(est_une_case_valide(n,m)&& fils[n][m]==blanc && moulin_blanc_fils(n,m,fils)==0){
                                        copierGrille(fils,fils_moulin);
                                        fils_moulin[n][m]=vide;
                                        eval=alpha_beta2(fils_moulin,p-1,a,b,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                        if(a>minEval){return minEval;}
                                        if(minEval<b){b=minEval;}
                                    }
                                }
                            }
                        }else{
                            eval=alpha_beta2(fils,p-1,a,b,blanc);
                            if (minEval>eval){
                                minEval=eval;

                            }
                            if(a>minEval){return minEval;}
                            if(minEval<b){b=minEval;}
                        }
                    }
                }
            }
        }
        return minEval;
    }
}



int alpha_beta3(int gr[7][7],int p,int a, int b, int couleur){
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
                                        eval=alpha_beta3(fils_moulin,p-1,a,b,noir);
                                        if (maxEval<eval){
                                            maxEval=eval;
                                            machine4[0]=i;machine4[1]=j;
                                            machine4[2]=k;machine4[3]=l;
                                            machine4[4]=n;machine4[5]=m;
                                        }
                                        if(maxEval>b){return maxEval;}
                                        if(maxEval>a){a=maxEval;}
                                    }
                                }
                            }
                            }else{
                            eval=alpha_beta3(fils,p-1,a,b,noir);
                            if (maxEval<eval){
                                maxEval=eval;
                                machine4[0]=i;machine4[1]=j;
                                machine4[2]=k;machine4[3]=l;
                                machine4[4]=-1;machine4[5]=-1;
                            }
                            if(maxEval>b){return maxEval;}
                            if(maxEval>a){a=maxEval;}
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
                                        eval=alpha_beta3(fils_moulin,a,b,p-1,blanc);
                                        if (minEval>eval){
                                            minEval=eval;

                                        }
                                        if(a>minEval){return minEval;}
                                        if(minEval<b){b=minEval;}
                                    }
                                }
                            }
                            }else{
                            eval=alpha_beta3(fils,a,b,p-1,blanc);
                            if (minEval>eval){
                                minEval=eval;
                            }
                            if(a>minEval){return minEval;}
                            if(minEval<b){b=minEval;}
                            }
                        }
                    }
                }
            }
        }
        return minEval;
    }
}









int joueur_vs_machine_alphaBeta()
{
    system("cls");
    int play=1;
    int* case_inseree1=NULL;//la case ou le joueur1 insere son pion
    int* case_jouee1=NULL;//la case ou le joueur1 va jouer son pion
    int alpha_beta=0;
     int etat_actuel[7][7];

    /*------------------------------------------phase1-----------------------------------------*/

    afficher(grille);
    printf("phase1\n");
    for(int i=1;i<=9;++i) //chaque joueur insere 9 pions
    {
        printf("tour du noir\n");
        case_inseree1=inserer_un_pion_noir();//on va considerer que le joueur 1 joue en noir
        system("cls");
        afficher(grille);
        printf("phase1\n");
        if(moulin_noir(case_inseree1[0],case_inseree1[1]))
        {
            retirer_case_blanche();
            system("cls");
            afficher(grille);
        }
        tour1=i;

        printf("tour du blanc\n");
        for(int k=0;k<taille;++k) // on copie l'etat actuel
          {
              for(int l=0;l<taille;++l)
                {
                    etat_actuel[k][l]=grille[k][l];
                }
          }
        alpha_beta=alpha_beta1(etat_actuel,profondeur,-infinie,infinie,blanc); //on va considerer que le joueur 2 joue en blanc
        grille[machine3[0]][machine3[1]]=blanc;//on insere le choix de la machine
        system("cls");
        afficher(grille);
        printf("phase1\n");
        if((machine3[2]!=-1) && (machine3[3]!=-1) ) // s'il y a un moulin pour la machine
        {
            grille[machine3[2]][machine3[3]]=vide;//on insere le choix de la machine
            system("cls");
            afficher(grille);
            printf("phase1\n");
        }
        tour1=i+1;


    }
    /*------------------------------------------phase2-----------------------------------------*/
    system("cls");
    afficher(grille);
    printf("phase2\n");
    while(play)
    {
        if(impossible_de_jouer_noir()==1)
        {
            printf("fin du jeu le joueur2 a gannee\n");
            break;
        }

         printf("tour du noir\n");
        if(nb_noir()==3)
        {
            case_jouee1=jouer_un_pion_noir3();
        }
        else
        {
            case_jouee1=jouer_un_pion_noir();
        }
        system("cls");
        afficher(grille);
        printf("phase2\n");
        if(moulin_noir(case_jouee1[0],case_jouee1[1]))
        {
            retirer_case_blanche();
            system("cls");
            afficher(grille);
            printf("phase2\n");
        }



        if(impossible_de_jouer_blanc()==1)
        {
            printf("fin du jeu le joueur1 a gannee\n");
            break;
        }

        printf("tour du blanc\n");
        copierGrille(grille,etat_actuel);
        if(nb_blanc()==3)
        {
            alpha_beta=alpha_beta3(etat_actuel,profondeur,-infinie,infinie,blanc); //on va considerer que le joueur 2 joue en blanc
        }else{
            alpha_beta=alpha_beta2(etat_actuel,profondeur,-infinie,infinie,blanc);
        }
        grille[machine4[0]][machine4[1]]=vide;//on insere le choix de la machine
        grille[machine4[2]][machine4[3]]=blanc;
        system("cls");
        afficher(grille);
        printf("phase2\n");
        if((machine4[4]!=-1) && (machine4[5]!=-1) ) // s'il y a un moulin pour la machine
        {
            grille[machine4[4]][machine4[5]]=vide;//on insere le choix de la machine
            system("cls");
            afficher(grille);
            printf("phase2\n");
        }
    }

    return 0;
}


