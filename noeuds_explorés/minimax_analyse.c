
#include <stdio.h>
#include <stdlib.h>
#define taille 7
#define profondeur 2

enum{vide,noir,blanc};//vide:0 noir:1 blanc:2

int tour =0;

int grille[7][7]; // initialisée par 0=vide

int nombre_de_noeud_genere=0;


int machine1[4]={0,0,0,0};// les coordonee ou la machine va jouer et ou la machine va jouer le moulin
int machine2[6]={0,0,0,0,0,0};
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




int* inserer_un_pion_noir()
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
                grille[choix_i][choix_j]=noir;
                choix[0]=choix_i;choix[1]=choix_j;
                return choix;
            }
            else{printf("la case est occupée\n");}
    }
        else{printf("la case n'existe pas\n");}


    }


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

void retirer_case_blanche()
{
    int choix_i,choix_j,choix_est_faux=1;
    char lettre;
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

        while(choix_est_faux)
        {
          printf("choisissez un pion adverse pour le supprimer :");
          scanf("\n%c",&lettre);


          /* On change les minuscules en majuscules */
          if ((lettre>='a')&&(lettre<'a'+taille))
          lettre=lettre+'A'-'a';

          choix_j=lettre-'A';
          scanf("%d",&choix_i);
          choix_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1
          if((grille[choix_i][choix_j]==noir))//si la case est noir ou vide ou une blanche qui appartiennet pas à un moulin
          {
              printf("\nimpossible de supprimer la case choisit la case est noire\n");
          }
          else if((grille[choix_i][choix_j]==vide))
          {
              printf("\nimpossible de supprimer la case choisit la case est vide\n");
          }
          else if(moulin_blanc(choix_i,choix_j)==1)
          {
              printf("\nimpossible de supprimer la case choisit la case appartient à un moulin\n");
          }
          else
            {
                grille[choix_i][choix_j]=vide;
                return;
            }

        }
    }
}
void retirer_case_noire()
{
    int choix_i,choix_j,choix_est_faux=1;
    char lettre;
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

        while(choix_est_faux)
        {
          printf("choisissez un pion adverse pour le supprimer :");
          scanf("\n%c",&lettre);


          /* On change les minuscules en majuscules */
          if ((lettre>='a')&&(lettre<'a'+taille))
          lettre=lettre+'A'-'a';

          choix_j=lettre-'A';
          scanf("%d",&choix_i);
          choix_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1
          if((grille[choix_i][choix_j]==blanc))//si la case est blanche ou vide ou une blanche qui appartiennet pas à un moulin
          {
              printf("\nimpossible de supprimer la case choisit la case est blanche\n");
          }
          else if((grille[choix_i][choix_j]==vide))
          {
              printf("\nimpossible de supprimer la case choisit la case est vide\n");
          }
          else if(moulin_noir(choix_i,choix_j)==1)
          {
              printf("\nimpossible de supprimer la case choisit la case appartient à un moulin\n");
          }
          else
            {
                grille[choix_i][choix_j]=vide;
                break;
            }

        }
    }
}

int *jouer_un_pion_noir()
{

    int *choix=(int*)malloc(2*sizeof(int)); //tableau qui contient la case où le joueur va poser son pion
    int choix_i,choix_cible_i,choix_cible_j,choix_j,choix_est_faux=1,nb_jouer=0;//nb_jouer:pour verifier si la case peut etre deplacee
    int k,l;//pour se deplacer vers les autres cases a verifier
    char lettre;

    //------------------------------------------------------------------ on deplace la case
    while(choix_est_faux)
    {
        printf("\nchoisissez le pion que vous voulez jouer\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_j=lettre-'A';
    scanf("%d",&choix_i);
    choix_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1





    if((!est_une_case_valide(choix_i,choix_j))||(grille[choix_i][choix_j]!=noir))
    {
        printf("vous avez choisit une case fausse");
    }
    else
      {
          k=choix_i;l=choix_j;
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
                if(grille[k][l]==vide)
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

            break;
        }
        else
        {
            printf("impossible de deplacer cette case\n");
        }
      }
   }
   //------------------------------------------------------------- on pose la case
  while(choix_est_faux)
    {
        printf("\nchoisissez la case ou vous voulez poser votre pion\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_cible_j=lettre-'A';
    scanf("%d",&choix_cible_i);
    choix_cible_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1

    if(est_une_case_valide(choix_cible_i,choix_cible_j))
    {
            if(grille[choix_cible_i][choix_cible_j]==vide) //la case n'est pas la case actuelle
          {
                k=choix_i;l=choix_j;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k<6)// on verifie si la case se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k<3)// on verifie si la case se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }
             }
                if(k==choix_cible_i && l==choix_cible_j)
                    {
                        grille[choix_cible_i][choix_cible_j]=noir;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k>0)// on verifie si la case se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k>3)// on verifie si la case se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }
              }
                if(k==choix_cible_i && l==choix_cible_j)
                    {
                        grille[choix_cible_i][choix_cible_j]=noir;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l>0)// on verifie si la case se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l>3)// on verifie si la case se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }
              }
                if(l==choix_cible_j && k==choix_cible_i)
                    {
                        grille[choix_cible_i][choix_cible_j]=noir;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }



                k=choix_i;l=choix_j;
                if(l<6)
            {
                l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l<6)// on verifie si la case se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l<3)// on verifie si la case se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }
            }
                if(l==choix_cible_j && k==choix_cible_i)
                    {
                        grille[choix_cible_i][choix_cible_j]=noir;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }

                printf("impossible de poser la case\n");



            }
            else{printf("la case est occupée\n");}
    }
        else{printf("la case n'existe pas\n");}


    }

}


int *jouer_un_pion_noir3()// si la joueur n'a que 3 pions
{

    int *choix=(int*)malloc(2*sizeof(int)); //tableau qui contient la case où le joueur va poser son pion
    int choix_i,choix_cible_i,choix_cible_j,choix_j,choix_est_faux=1,nb_jouer=0;//nb_jouer:pour verifier si la case peut etre deplacee
    int k,l;//pour se deplacer vers les autres cases a verifier
    char lettre;

    //------------------------------------------------------------------ on deplace la case
    while(choix_est_faux)
    {
        printf("\nchoisissez le pion que vous voulez jouer\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_j=lettre-'A';
    scanf("%d",&choix_i);
    choix_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1





    if((!est_une_case_valide(choix_i,choix_j))||(grille[choix_i][choix_j]!=noir))
    {
        printf("vous avez choisit une case fausse");
    }
    else
      {
          k=choix_i;l=choix_j;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k<6)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                {
                    ++k;
                }
             }
                if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                        k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                {
                    --k;
                }
              }
                if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                    --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                {
                    --l;
                }
              }
                if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l<6)
             {
                    l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l<7)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                {
                    ++l;
                }
             }
             if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
         if(nb_jouer!=0)
        {

            break;
        }
        else
        {
            printf("impossible de deplacer cette case\n");
        }
      }
   }
   //------------------------------------------------------------- on pose la case
  while(choix_est_faux)
    {
        printf("\nchoisissez la case ou vous voulez poser votre pion\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_cible_j=lettre-'A';
    scanf("%d",&choix_cible_i);
    choix_cible_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1

    if(est_une_case_valide(choix_cible_i,choix_cible_j))
    {
            if(grille[choix_cible_i][choix_cible_j]==vide) //la case n'est pas la case actuelle
          {
                grille[choix_cible_i][choix_cible_j]=noir;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;



            }
            else{printf("la case est occupée\n");}
    }
        else{printf("la case n'existe pas\n");}


    }

}

int *jouer_un_pion_blanc()
{

    int *choix=(int*)malloc(2*sizeof(int)); //tableau qui contient la case où le joueur va poser son pion
    int choix_i,choix_cible_i,choix_cible_j,choix_j,choix_est_faux=1,nb_jouer=0;//nb_jouer:pour verifier si la case peut etre deplacee
    int k,l;//pour se deplacer vers les autres cases a verifier
    char lettre;

    //------------------------------------------------------------------ on deplace la case
    while(choix_est_faux)
    {
        printf("\nchoisissez le pion que vous voulez jouer\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_j=lettre-'A';
    scanf("%d",&choix_i);
    choix_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1





    if((!est_une_case_valide(choix_i,choix_j))||(grille[choix_i][choix_j]!=blanc))
    {
        printf("vous avez choisit une case fausse");
    }
    else
      {
          k=choix_i;l=choix_j;
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

                if(grille[k][l]==vide)
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
                if(grille[k][l]==vide)
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
                if(grille[k][l]==vide)
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
             if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
         if(nb_jouer!=0)
        {

            break;
        }
        else
        {
            printf("impossible de deplacer cette case\n");
        }
      }
   }
   //------------------------------------------------------------- on pose la case
  while(choix_est_faux)
    {
        printf("\nchoisissez la case ou vous voulez poser votre pion\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_cible_j=lettre-'A';
    scanf("%d",&choix_cible_i);
    choix_cible_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1

    if(est_une_case_valide(choix_cible_i,choix_cible_j))
    {
            if(grille[choix_cible_i][choix_cible_j]==vide) //la case n'est pas la case actuelle
          {
                k=choix_i;l=choix_j;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k<6)// on verifie si la case se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k<3)// on verifie si la case se trouve juste en bas de la case actuelle
                    {
                        ++k;
                    }
                }
             }
                if(k==choix_cible_i && l==choix_cible_j)
                    {
                        grille[choix_cible_i][choix_cible_j]=blanc;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (l!=3){
                    while(!est_une_case_valide(k,l) && k>0)// on verifie si la case se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && k>3)// on verifie si la case se trouve juste en haut de la case actuelle
                    {
                        --k;
                    }
                }
              }
                if(k==choix_cible_i && l==choix_cible_j)
                    {
                        grille[choix_cible_i][choix_cible_j]=blanc;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l>0)// on verifie si la case se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l>3)// on verifie si la case se trouve juste a gauche de la case actuelle
                    {
                        --l;
                    }
                }
              }
                if(l==choix_cible_j && k==choix_cible_i)
                    {
                        grille[choix_cible_i][choix_cible_j]=blanc;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }



                k=choix_i;l=choix_j;
                if(l<6)
            {
                l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                if (k!=3){
                    while(!est_une_case_valide(k,l) && l<6)// on verifie si la case se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }else{
                    while(!est_une_case_valide(k,l) && l<3)// on verifie si la case se trouve juste a droite de la case actuelle
                    {
                        ++l;
                    }
                }
            }
                if(l==choix_cible_j && k==choix_cible_i)
                    {
                        grille[choix_cible_i][choix_cible_j]=blanc;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;

                    }

                printf("impossible de poser la case\n");



            }
            else{printf("la case est occupée\n");}
    }
        else{printf("la case n'existe pas\n");}


    }

}

int *jouer_un_pion_blanc3()
{

    int *choix=(int*)malloc(2*sizeof(int)); //tableau qui contient la case où le joueur va poser son pion
    int choix_i,choix_cible_i,choix_cible_j,choix_j,choix_est_faux=1,nb_jouer=0;//nb_jouer:pour verifier si la case peut etre deplacee
    int k,l;//pour se deplacer vers les autres cases a verifier
    char lettre;

    //------------------------------------------------------------------ on deplace la case
    while(choix_est_faux)
    {
        printf("\nchoisissez le pion que vous voulez jouer\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_j=lettre-'A';
    scanf("%d",&choix_i);
    choix_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1
    if((!est_une_case_valide(choix_i,choix_j))||(grille[choix_i][choix_j]!=blanc))
    {
        printf("vous avez choisit une case fausse");
    }
    else
      {
          k=choix_i;l=choix_j;
                if(k<6)
             {
                k++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k<6)// on se deplace vers la premiere case qui se trouve juste en bas de la case actuelle
                {
                    ++k;
                }
             }
                if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(k>0)
              {
                        k--;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && k>0)// on se deplace vers la premiere case qui se trouve juste en haut de la case actuelle
                {
                    --k;
                }
              }
                if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l>0)
             {
                    --l;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l>0)// on se deplace vers la premiere case qui se trouve juste a gauche de la case actuelle
                {
                    --l;
                }
              }
                if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }



                k=choix_i;l=choix_j;
                if(l<6)
             {
                    l++;//on se deplace vers une case non valide poour qu'on puisse entrer dans la boucle
                while(!est_une_case_valide(k,l) && l<7)// on se deplace vers la premiere case qui se trouve juste a droite de la case actuelle
                {
                    ++l;
                }
             }
             if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
         if(nb_jouer!=0)
        {

            break;
        }
        else
        {
            printf("impossible de deplacer cette case\n");
        }
      }
   }
   //------------------------------------------------------------- on pose la case
  while(choix_est_faux)
    {
        printf("\nchoisissez la case ou vous voulez poser votre pion\n");
    scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+taille))
        lettre=lettre+'A'-'a';

    choix_cible_j=lettre-'A';
    scanf("%d",&choix_cible_i);
    choix_cible_i--;//on diminue 1 parce que la matrice commence par 0 pas par 1

    if(est_une_case_valide(choix_cible_i,choix_cible_j))
    {
            if(grille[choix_cible_i][choix_cible_j]==vide ) //la case n'est pas la case actuelle
          {
                grille[choix_cible_i][choix_cible_j]=blanc;
                        grille[choix_i][choix_j]=vide;// la case deplacée devient vide
                        choix[0]=choix_cible_i;choix[1]=choix_cible_j;
                        return choix;
          }
            else{printf("la case est occupee\n");}
    }
        else{printf("la case n'existe pas\n");}


    }

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
                if(grille[k][l]==vide)
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
                if(grille[k][l]==vide)
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
                if(grille[k][l]==vide)
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
             if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
            }
        }
    }

    return((nb_pion==2) || (nb_jouer==0));


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
                if(grille[k][l]==vide)
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
                if(grille[k][l]==vide)
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
                if(grille[k][l]==vide)
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
             if(grille[k][l]==vide)
                    {
                        ++nb_jouer;

                    }
            }
        }
    }

    return((nb_pion==2) || (nb_jouer==0));


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
                                    ++nombre_de_noeud_genere;
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
                        ++nombre_de_noeud_genere;
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
                                    ++nombre_de_noeud_genere;
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
                        ++nombre_de_noeud_genere;
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



















int main()
{
    int play=1;
    int* case_inseree1=NULL;//la case ou le joueur1 insere son pion
    int* case_jouee1=NULL;//la case ou le joueur1 va jouer son pion
    int minmax=0;
     int etat_actuel[7][7];

    /*------------------------------------------phase1-----------------------------------------*/

    afficher(grille);
    printf("phase1\n");
    for(int i=1;i<=9;++i) //chaque joueur insere 9 pions
    {
        printf("tour du noir\n");
        case_inseree1=inserer_un_pion_noir();//on va considerer que le joueur 1 joue en noir
        afficher(grille);
        printf("phase1\n");
        if(moulin_noir(case_inseree1[0],case_inseree1[1]))
        {
            retirer_case_blanche();
            afficher(grille);
        }
        tour=i;

        printf("tour du blanc\n");
        for(int k=0;k<taille;++k) // on copie l'etat actuel
          {
              for(int l=0;l<taille;++l)
                {
                    etat_actuel[k][l]=grille[k][l];
                }
          }
          nombre_de_noeud_genere=0;
        minmax=minmax1(etat_actuel,profondeur,blanc); //on va considerer que le joueur 2 joue en blanc
        grille[machine1[0]][machine1[1]]=blanc;//on insere le choix de la machine
        afficher(grille);
        printf("phase1\n");
        if((machine1[2]!=-1) && (machine1[3]!=-1) ) // s'il y a un moulin pour la machine
        {
            grille[machine1[2]][machine1[3]]=vide;//on insere le choix de la machine
            afficher(grille);
            printf("phase1\n");
        }
        tour=i+1;
        printf("nombre de noeuds generes:%d\n",nombre_de_noeud_genere);


    }
    /*------------------------------------------phase2-----------------------------------------*/
    printf("phase2\n");
    while(play)
    {
        if(impossible_de_jouer_noir()==1)
        {
            printf("fin du jeu le joueur2 a gannee\n");
            break;
        }

         printf("tour du noir\n");
        case_jouee1=jouer_un_pion_noir();
        //system("cls");
        afficher(grille);
        printf("phase2\n");
        if(moulin_noir(case_jouee1[0],case_jouee1[1]))
        {
            retirer_case_blanche();
            //system("cls");
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
        minmax=minimax2(etat_actuel,profondeur,blanc); //on va considerer que le joueur 2 joue en blanc
        grille[machine2[0]][machine2[1]]=vide;//on insere le choix de la machine
        grille[machine2[2]][machine2[3]]=blanc;
        //system("cls");
        afficher(grille);
        printf("phase2\n");
        if((machine2[4]!=-1) && (machine2[5]!=-1) ) // s'il y a un moulin pour la machine
        {
            grille[machine2[4]][machine2[5]]=vide;//on insere le choix de la machine
            //system("cls");
            afficher(grille);
            printf("phase2\n");
        }
    }

    return 0;
}

