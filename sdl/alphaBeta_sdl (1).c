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
int infinie=300;
int grille[7][7]; // initialisée par 0=vide


int machine3[4]={0,0,0,0};// les coordonee ou la machine va jouer et ou la machine va jouer le moulin
int machine4[6]={0,0,0,0,0,0};
//-----------------------------------------------------------------------------------------------
int est_une_case_valide(int i,int j)
{
    return ((i<7 && j<7)&&((i!=3 &&(j==i || j==6-i || j==3)) || (i==3 &&j!=3)));
    /*(i<7 &&j<7) :la case appartient à la grille
    (i<7 && j<7)&&((i!=3 &&(j==i || j==7-i || j==3)) || (i==3 &&j!=3):si la case est possible*/
}


char correspond(int grille[7][7],int i, int j)
{
    if (grille[i][j]==vide)
        return '.';
    else if (grille[i][j]==noir)
        return 'N';
    else
        return 'B';
}
void afficher(int grille[7][7]){
    printf("\n");
    printf("\t1  %c______________%c______________%c\n",correspond(grille,0,0),correspond(grille,0,3),correspond(grille,0,6));
    printf("\t   |              |              |\n");
    printf("\t2  |____%c_________%c_________%c____|\n",correspond(grille,1,1),correspond(grille,1,3),correspond(grille,1,5));
    printf("\t   |    |         |         |    |\n");
    printf("\t3  |____|____%c____%c____%c____|____|\n",correspond(grille,2,2),correspond(grille,2,3),correspond(grille,2,4));
    printf("\t   |    |    |         |    |    |\n");
    printf("\t4  %c____%c____%c         %c____%c____%c\n",correspond(grille,3,0),correspond(grille,3,1),correspond(grille,3,2),correspond(grille,3,4),correspond(grille,3,5),correspond(grille,3,6));
    printf("\t   |    |    |         |    |    |\n");
    printf("\t5  |____|____%c____%c____%c____|____|\n",correspond(grille,4,2),correspond(grille,4,3),correspond(grille,4,4));
    printf("\t   |    |         |         |    |\n");
    printf("\t6  |____%c_________%c_________%c____|\n",correspond(grille,5,1),correspond(grille,5,3),correspond(grille,5,5));
    printf("\t   |              |              |\n");
    printf("\t7  %c______________%c______________%c\n",correspond(grille,6,0),correspond(grille,6,3),correspond(grille,6,6));
    printf("\n\t   a    b    c    d    e    f    g \n");
}




int inserer_un_pion_noir(int choix_i,int choix_j)
{


    if(est_une_case_valide(choix_i,choix_j))
    {
            if(grille[choix_i][choix_j]==vide)
            {
                grille[choix_i][choix_j]=noir;
                printf("pposer pion noir\n");
                return 1;
            }
    }
    printf("la case noir n'est pas validde\n");
    return 0;





}
int* inserer_un_pion_blanc()
{
    int *choix=(int*)malloc(2*sizeof(int)); //tableau qui contient la position choisit
    int choix_i,choix_j,choix_est_faux=1;
    char lettre;
    while(choix_est_faux)
    {
        printf("\nchoisir la case ou vous voulez poser votre pion\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_j=lettre-'A';
    scanf("%d",&choix_i);
    choix_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1
    if(est_une_case_valide(choix_i,choix_j))
    {
            if(grille[choix_i][choix_j]==vide)
            {
                grille[choix_i][choix_j]=blanc;
                choix[0]=choix_i;choix[1]=choix_j;
                return choix;
            }
            else{printf("la case est occupée\n");}
    }
        else{printf("la case n'existe pas\n");}


    }


}

int moulin_noir(int i,int j)//fonction qui va nous permettre si la case  appartiennet  à un moulin
{
    int k=i,l=j,compteur=0,nb_moulin=0;
    l=0;// vrification pour les lignes
    if(i!=3)
    {
        while(l<7)
        {
            if(est_une_case_valide(k,l) && grille[k][l]==noir)
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
             if(est_une_case_valide(k,l) && grille[k][l]==noir)
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
             if(est_une_case_valide(k,l) && grille[k][l]==noir)
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
            if(est_une_case_valide(k,l) && grille[k][l]==noir)
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
             if(est_une_case_valide(k,l) && grille[k][l]==noir)
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
             if(est_une_case_valide(k,l) && grille[k][l]==noir)
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

int moulin_blanc(int i,int j)//fonction qui va nous permettre si la case  appartiennet  à un moulin
{
    int k=i,l=j,compteur=0,nb_moulin=0;
    l=0;// vrification pour les lignes
    if(i!=3)
    {
        while(l<7)
        {
            if(est_une_case_valide(k,l) && grille[k][l]==blanc)
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
             if(est_une_case_valide(k,l) && grille[k][l]==blanc)
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
             if(est_une_case_valide(k,l) && grille[k][l]==blanc)
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
            if(est_une_case_valide(k,l) && grille[k][l]==blanc)
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
             if(est_une_case_valide(k,l) && grille[k][l]==blanc)
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
             if(est_une_case_valide(k,l) && grille[k][l]==blanc)
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

int retirer_case_blanche(int choix_i,int choix_j,int *tour)
{

    int nb_case=0;//nombre de cases blanches qui n'appartiennet pas un moulin
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if(est_une_case_valide(i,j)&&(grille[i][j]==blanc)&&(moulin_blanc(i,j)==0))
            {
                ++nb_case;
            }
        }
    }
    if(nb_case!=0)
    {



          if((grille[choix_i][choix_j]==noir))//si la case est noir ou vide ou une blanche qui appartiennet pas à un moulin
          {
              printf("\nimpossible de supprimer la case choisit la case est noire\n");
              return 0;

          }
          else if((grille[choix_i][choix_j]==vide))
          {
              printf("\nimpossible de supprimer la case choisit la case est vide\n");
              return 0;
          }
          else if(moulin_blanc(choix_i,choix_j)==1)
          {
              printf("\nimpossible de supprimer la case choisit la case appartient à un moulin\n");
              return 0;
          }
          else
            {
                grille[choix_i][choix_j]=vide;
                printf("retirer blanc\n");
                return 1;
            }


    }


}



int retirer_case_noire(int choix_i,int choix_j,int *tour)
{

    int nb_case=0;//nombre de cases blanches qui n'appartiennet pas un moulin
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if(est_une_case_valide(i,j)&&(grille[i][j]==noir)&&(moulin_noir(i,j)==0))
            {
                ++nb_case;
            }
        }
    }
    if(nb_case!=0)
    {


          if((grille[choix_i][choix_j]==blanc))//si la case est blanche ou vide ou une blanche qui appartiennet pas à un moulin
          {
              printf("\nimpossible de supprimer la case choisit la case est blanche\n");
              return 0;
          }
          else if(est_une_case_valide(choix_i,choix_j) && grille[choix_i][choix_j]==vide)
          {
              printf("\nimpossible de supprimer la case choisit la case est vide\n");
              return 0;
          }
          else if(moulin_noir(choix_i,choix_j)==1)
          {
              printf("\nimpossible de supprimer la case choisit la case appartient à un moulin\n");
              return 0;
          }
          else
            {

                grille[choix_i][choix_j]=vide;
                printf("retirer noir\n");
                return 1;
            }


    }
    return 0;

}
int nb_moulin_noir()
{
    int nb_case=0;//nombre de cases noires qui n'appartiennet pas un moulin
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if(est_une_case_valide(i,j)&&(grille[i][j]==noir)&&(moulin_noir(i,j)==0))
            {
                ++nb_case;
            }
        }
    }
    return nb_case;
}

int nb_moulin_blanc()
{
    int nb_case=0;//nombre de cases blanches qui n'appartiennet pas un moulin
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if(est_une_case_valide(i,j)&&(grille[i][j]==blanc)&&(moulin_blanc(i,j)==0))
            {
                ++nb_case;
            }
        }
    }

    return nb_case;
}
int verifier_deplacement_noir(int choix_i, int choix_j)
{
    int k=choix_i,l=choix_j;
    int nb_jouer=0;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k<6)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k<3)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }
             }

                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k>3)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }
              }
                if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l>3)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }
              }
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l<6)
             {
                l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l<6)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l<3)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }
             }
             if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
         if(nb_jouer!=0)
        {

            return 1;
        }
        else
        {
            printf("impossible de deplacer cette case\n");
            return 0;
        }


}
int jouer_un_pion_noir(int choix_i, int choix_j, int choix_k, int choix_l){
    int k=choix_i,l=choix_j;
    if (est_une_case_valide(k,l) && grille[choix_k][choix_l]==vide){
        if(k<6)
             {
                k++;
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k<6)
                    {
                        ++k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k<3)
                    {
                        ++k;
                    }
                }
             }

                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=noir;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }
                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k>3)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }
              }
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=noir;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l>3)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }
              }
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=noir;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }

                    }



                k=choix_i;l=choix_j;
                if(l<6)
             {
                l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l<6)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l<3)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }
             }
             if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=noir;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }

                    }

    }
    return 0;
}

int verifier_deplacement_blanc(int choix_i, int choix_j)
{
   int k=choix_i,l=choix_j;
   int nb_jouer=0;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k<6)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k<3)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }
             }

                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k>3)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }
              }
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l>3)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }
              }
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l<6)
             {
                l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l<6)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l<3)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }
             }
             if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
         if(nb_jouer!=0)
        {

            return 1;
        }
        else
        {
            printf("impossible de deplacer cette case\n");
            return 0;
        }

}


int jouer_un_pion_noir3(int choix_i, int choix_j, int choix_k, int choix_l)// si la joueur n'a que 3 pions
{

    if(est_une_case_valide(choix_k,choix_l))
    {
            if(grille[choix_k][choix_l]==vide) //la case n'est pas la case actuelle
          {
                grille[choix_k][choix_l]=noir;
                grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        return 1;

            }
            else{printf("la case est occupée\n");
            return 0;}
    }
        else{printf("la case n'existe pas\n");
        return 0;}


}


int jouer_un_pion_blanc(int choix_i, int choix_j, int choix_k, int choix_l){
    int k=choix_i,l=choix_j;
    if (est_une_case_valide(k,l) && grille[choix_k][choix_l]==vide){
        if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k<6)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k<3)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }
             }

                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=blanc;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }
                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k>3)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }
              }
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=blanc;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l>3)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }
              }
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=blanc;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }

                    }



                k=choix_i;l=choix_j;
                if(l<6)
             {
                l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l<6)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l<3)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }
             }
             if(est_une_case_valide(k,l) && grille[k][l]==vide)
                    {
                        if (choix_k==k && choix_l==l){
                            grille[choix_k][choix_l]=blanc;
                            grille[choix_i][choix_j]=vide;
                            return 1;
                        }

                    }
    }
    return 0;
}

int jouer_un_pion_blanc3(int choix_i, int choix_j, int choix_k, int choix_l)// si la joueur n'a que 3 pions
{

    if(est_une_case_valide(choix_k,choix_l))
    {
            if(grille[choix_k][choix_l]==vide) //la case n'est pas la case actuelle
          {
                grille[choix_k][choix_l]=blanc;
                grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        return 1;

            }
            else{printf("la case est occupée\n");
            return 0;}
    }
        else{printf("la case n'existe pas\n");
        return 0;}


}

int impossible_de_jouer_noir()
{
    int nb_pion=0,nb_jouer=0;//nombre de pions noirs rt nombre de cases ou on peut se deplacer
    int k,l;//pour se déplcer
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (grille[i][j]==noir))
            {
                ++nb_pion;
            }
        }
    }

    //--------------------------------------------------------- on calcule le nombre de pionsqu'on peut jouer
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (grille[i][j]==noir))
            {
                k=i;l=j;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k<6)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                {
                    ++k;
                }
             }
                if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=i;l=j;
                if(k>0)
              {
                        k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                {
                    --k;
                }
              }
                if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=i;l=j;
                if(l>0)
             {
                    --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                {
                    --l;
                }
              }
                if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=i;l=j;
                if(l<6)
             {
                    l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l<7)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                {
                    ++l;
                }
             }
             if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
            }
        }
    }

    if (nb_pion>3)
    {
        return nb_jouer==0;
    }

    return nb_pion==2;


}

int impossible_de_jouer_blanc()
{
    int nb_pion=0,nb_jouer=0;//nombre de pions noirs rt nombre de cases ou on peut se deplacer
    int k,l;//pour se déplcer
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (grille[i][j]==blanc))
            {
                ++nb_pion;
            }
        }
    }

    //--------------------------------------------------------- on calcule le nombre de pionsqu'on peut jouer
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (grille[i][j]==blanc))
            {
                k=i;l=j;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k<6)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                {
                    ++k;
                }
             }
                if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=i;l=j;
                if(k>0)
              {
                        k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                {
                    --k;
                }
              }
                if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=i;l=j;
                if(l>0)
             {
                    --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                {
                    --l;
                }
              }
                if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=i;l=j;
                if(l<6)
             {
                    l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l<7)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                {
                    ++l;
                }
             }
             if(est_une_case_valide(k,l) &&grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
            }
        }
    }
    if (nb_pion>3)
    {
        return nb_jouer==0;
    }

    return nb_pion==2;


}

int nb_noir()
{
    int nb=0;
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (grille[i][j]==noir))
            {
                ++nb;
            }
        }
    }
    return nb;
}


int nb_blanc()
{
    int nb=0;
    for(int i=0;i<taille;++i)
    {
        for(int j=0;j<taille;++j)
        {
            if((est_une_case_valide(i,j)) && (grille[i][j]==blanc))
            {
                ++nb;
            }
        }
    }
    return nb;
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



int alpha_beta1(int n[7][7], int p,int a,int b,int couleur)
{
    if((etat_final1()) || p==0)
    {

        return h(n);
    }
    else
    {
        if(couleur==blanc) // c'est le joueur max qui commence  donc max est blanc
        {
        int max=-infinie;
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
                                    a=alpha_beta1(fils_moulin,p-1,a,b,noir);
                                    if(a>=max)
                                    {
                                        max=a;
                                        machine3[0]=i;machine3[1]=j; // ou va jouer la machine
                                        machine3[2]=k;machine3[3]=l; // ou va jouer la machine le moulin

                                    }
                                    if(a>=b){return max;}
                                }
                              }
                           }
                         }
                      }
                    }
                else
                {
                        ++tour;
                        a=alpha_beta1(fils_moulin,p-1,a,b,noir);
                       if(a>=max)
                      {
                        max=a;
                        machine3[0]=i;machine3[1]=j; // ou va jouer la machine
                        machine3[2]=-1;machine3[3]=-1; // s'il n'y a pas de moulin on choisit par default -1 -1
                      }
                    if(a>b){return max;}
                }
            }

          }

         }
        }
        return max;
      }
      else  // si tour du min:noir
      {
          int min=infinie;
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
                                    b=alpha_beta1(fils_moulin,p-1,a,b,blanc);
                                    if(b<=min)
                                    {
                                        min=b;


                                    }

                                    if(a>b){return min;}
                                }
                              }
                           }
                         }
                      }
                    }
                    else
                    {
                        ++tour;
                        b=alpha_beta1(fils_moulin,p-1,a,b,blanc);
                        if(b<=min)
                            {
                                min=b;


                            }

                        if(a>b){return min;}
                    }
                }

              }

          }
        }
        return min;
      }
    }
}


/*------------------------------------------------------------------------------------alphabeta2-------------------------------------*/





void copierGrille(int de[7][7], int a[7][7]){
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            a[i][j]=de[i][j];

        }
    }
}





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







int cliquer_sur_rect(int x,int y,int h,int w,SDL_Event event)
{
    return((event.button.x<w+x)&&(event.button.x>x)&&(event.button.y<h+y)&&(event.button.y>y));
}

void poser_dans(int i,int j,SDL_Rect *rectangle,SDL_Rect *depart)
{
    //pour x
    if(j<=2)
    {
        rectangle->x=depart->x+cadre+marge+j*pas;
    }
    else if(j==3)
    {
        rectangle->x=depart->x+cadre+marge+grand_pas+2*pas;
    }
    else
    {
        rectangle->x=depart->x+cadre+marge+2*grand_pas+(j-2)*pas;//i-2=3+(i-5)
    }
    //pour y
    if(i<=2)
    {
        rectangle->y=depart->y+cadre+marge+i*pas;
    }
    else if(i==3)
    {
        rectangle->y=depart->y+cadre+marge+grand_pas+(i-1)*pas;
    }
    else
    {
        rectangle->y=depart->y+cadre+marge+2*grand_pas+(i-2)*pas;//i-2=3+(i-5)
    }


}

int *la_case_cliquee(int x,int y,SDL_Event event,SDL_Rect depart)// on return les i et j a partir des x et y cliquee
{
    int *case_choisie=(int*)malloc(2*sizeof(int));
    case_choisie[0]=7;case_choisie[1]=7; //par default
    for(int i=0;i<=taille;++i)
    {
        if(i<=2)
       {
           for(int j=0;j<=taille;++j)
           {
               if(j<=2)
             {
                if(cliquer_sur_rect(depart.x+cadre+marge+j*pas,depart.y+cadre+marge+i*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
               else if(j==3)
             {
                  if(cliquer_sur_rect(depart.x+cadre+marge+grand_pas+2*pas,depart.y+cadre+marge+i*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
               else
             {
                 if(cliquer_sur_rect(depart.x+cadre+marge+2*grand_pas+(j-2)*pas,depart.y+cadre+marge+i*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
           }
        }
        else if(i==3)
       {
           for(int j=0;j<=taille;++j)
           {
               if(j<=2)
             {
                if(cliquer_sur_rect(depart.x+cadre+marge+j*pas,depart.y+cadre+marge+grand_pas+2*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
               else if(j==3)
             {
                  if(cliquer_sur_rect(depart.x+cadre+marge+grand_pas+2*pas,depart.y+cadre+marge+grand_pas+2*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
               else
             {
                 if(cliquer_sur_rect(depart.x+cadre+marge+2*grand_pas+(j-2)*pas,depart.y+cadre+marge+grand_pas+2*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
           }
       }
         else
       {
            for(int j=0;j<=taille;++j)
           {
               if(j<=2)
             {
                if(cliquer_sur_rect(depart.x+cadre+marge+j*pas,depart.y+cadre+marge+2*grand_pas+(i-2)*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
               else if(j==3)
             {
                  if(cliquer_sur_rect(depart.x+cadre+marge+grand_pas+2*pas,depart.y+cadre+marge+2*grand_pas+(i-2)*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
               else
             {
                 if(cliquer_sur_rect(depart.x+cadre+marge+2*grand_pas+(j-2)*pas,depart.y+cadre+marge+2*grand_pas+(i-2)*pas,dimension_pion,dimension_pion,event))
                {
                    case_choisie[0]=i;case_choisie[1]=j;
                }
             }
           }
       }
    }
    return case_choisie;
}


int indice_de_la_case(int i,int j,SDL_Rect rectangle[9],SDL_Rect depart)
{
    if(i<=2)
       {

               if(j<=2)
             {
                 for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+j*pas)&&(rectangle[k].y==depart.y+cadre+marge+i*pas,dimension_pion))
                     {return k;}
                 }

             }
               else if(j==3)
             {
                  for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+grand_pas+2*pas )&&(rectangle[k].y==depart.y+cadre+marge+i*pas))
                        {return k;}
                 }
             }
               else
             {
                 for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+2*grand_pas+(j-2)*pas )&&(rectangle[k].y==depart.y+cadre+marge+i*pas))
                     {return  k;}
                 }
             }

        }
        else if(i==3)
       {

               if(j<=2)
             {
                for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+j*pas)&&(rectangle[k].y==depart.y+cadre+marge+grand_pas+2*pas))
                     {return  k;}
                 }
             }
               else if(j==3)
             {
                 for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+grand_pas+2*pas)&&(rectangle[k].y==depart.y+cadre+marge+grand_pas+2*pas))
                     {return  k;}
                 }
             }
               else
             {
                 for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+2*grand_pas+(j-2)*pas)&&(rectangle[k].y==depart.y+cadre+marge+grand_pas+2*pas))
                     {return  k;}
                 }
             }

       }
         else
       {

               if(j<=2)
             {
               for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+j*pas)&&(rectangle[k].y==depart.y+cadre+marge+2*grand_pas+(i-2)*pas))
                     {return  k;}
                 }
             }
               else if(j==3)
             {
                 for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+grand_pas+2*pas)&&(rectangle[k].y==depart.y+cadre+marge+2*grand_pas+(i-2)*pas))
                     {return  k;}
                 }
             }
               else
             {
                 for(int k=0;k<9;++k)
                 {
                     if((rectangle[k].x==depart.x+cadre+marge+2*grand_pas+(j-2)*pas)&&(rectangle[k].y==depart.y+cadre+marge+2*grand_pas+(i-2)*pas))
                     {return  k;}
                 }
             }

       }
       return 9;
}









int main(int argc, char** argv)
{
    int *case_choisie=(int*)malloc(2*sizeof(int));
   int alpha_beta=0;
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

    image_pion_noir=IMG_Load("pion_noir.jpg");
    image_pion_blanc=IMG_Load("pion_blanc.jpg");
    image_boutton=IMG_Load("boutton.png");


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
                                  alpha_beta=alpha_beta1(etat_actuel,profondeur,-infinie,infinie,blanc); //on va considerer que le joueur 2 joue en blanc
                                  grille[machine3[0]][machine3[1]]=blanc;//on insere le choix de la machine

                                  poser_dans(machine3[0],machine3[1],&pion_blanc[indice_blanc],&emplacement);
                                  ++indice_blanc;
                                  if((machine3[2]!=-1) && (machine3[3]!=-1) ) // s'il y a un moulin pour la machine
                                 {
                                    grille[machine3[2]][machine3[3]]=vide;//on insere le choix de la machine
                                    int indice=indice_de_la_case(machine3[2],machine3[3],pion_noir,emplacement);
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
                                 alpha_beta=alpha_beta1(etat_actuel,profondeur,-infinie,infinie,blanc); //on va considerer que le joueur 2 joue en blanc
                                  grille[machine3[0]][machine3[1]]=blanc;//on insere le choix de la machine

                                  poser_dans(machine3[0],machine3[1],&pion_blanc[indice_blanc],&emplacement);
                                  ++indice_blanc;
                                  if((machine3[2]!=-1) && (machine3[3]!=-1) ) // s'il y a un moulin pour la machine
                                 {
                                    grille[machine3[2]][machine3[3]]=vide;//on insere le choix de la machine

                                    int indice2=indice_de_la_case(machine3[2],machine3[3],pion_noir,emplacement);
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
                                 alpha_beta=alpha_beta3(etat_actuel,profondeur,-infinie,infinie,blanc); //on va considerer que le joueur 2 joue en blanc
                                }else{
                                 alpha_beta=alpha_beta2(etat_actuel,profondeur,-infinie,infinie,blanc);
                                }
                                  grille[machine4[0]][machine4[1]]=vide;
                                  grille[machine4[2]][machine4[3]]=blanc;
                                  indice_blanc=indice_de_la_case(machine4[0],machine4[1],pion_blanc,emplacement);
                                    if(indice_blanc!=9)
                                   {
                                    poser_dans(machine4[2],machine4[3],&pion_blanc[indice_blanc],&emplacement);
                                    if((machine4[4]!=-1) && (machine4[5]!=-1) )
                                    {
                                        grille[machine4[4]][machine4[5]]=vide;
                                        int indice=indice_de_la_case(machine4[4],machine4[5],pion_noir,emplacement);
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
                                 alpha_beta=alpha_beta3(etat_actuel,profondeur,-infinie,infinie,blanc); //on va considerer que le joueur 2 joue en blanc
                                }else{
                                 alpha_beta=alpha_beta2(etat_actuel,profondeur,-infinie,infinie,blanc);
                                }
                                  grille[machine4[0]][machine4[1]]=vide;
                                  grille[machine4[2]][machine4[3]]=blanc;
                                  indice_blanc=indice_de_la_case(machine4[0],machine4[1],pion_blanc,emplacement);
                                    if(indice_blanc!=9)
                                   {
                                    poser_dans(machine4[2],machine4[3],&pion_blanc[indice_blanc],&emplacement);
                                    if((machine4[4]!=-1) && (machine4[5]!=-1) )
                                    {
                                        grille[machine4[4]][machine4[5]]=vide;
                                        int indice=indice_de_la_case(machine4[4],machine4[5],pion_noir,emplacement);
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

