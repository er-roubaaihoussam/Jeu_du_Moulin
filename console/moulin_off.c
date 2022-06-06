
#include <stdio.h>
#include <stdlib.h>
#define taille 7

enum{vide,noir,blanc};//vide:0 noir:1 blanc:2

int grille[7][7]; // initialisée par 0=vide

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
          else if(est_une_case_valide(choix_i,choix_j) && grille[choix_i][choix_j]==vide)
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
          else if(est_une_case_valide(choix_i,choix_j) && grille[choix_i][choix_j]==vide)
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
          break;
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
            break;
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
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
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
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
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
                if(est_une_case_valide(k,l) && grille[k][l]==vide)
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
             if(est_une_case_valide(k,l) && grille[k][l]==vide)
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



int joueur_vs_joueur()
{
    system("cls");
    int play=1;
    int* case_inseree1=NULL;//la case ou le joueur1 insere son pion
    int* case_inseree2=NULL;

    int* case_jouee1=NULL;//la case ou le joueur1 va jouer son pion
    int* case_jouee2=NULL;

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


        printf("tour du blanc\n");
        case_inseree2=inserer_un_pion_blanc(); //on va considerer que le joueur 2 joue en blanc
        system("cls");
        afficher(grille);
        printf("phase1\n");
        if(moulin_blanc(case_inseree2[0],case_inseree2[1]))
        {
            retirer_case_noire();
            system("cls");
            afficher(grille);
            printf("phase1\n");
        }


    }
    /*----------------------------------------phase2-----------------------------------------------*/
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
        if(nb_blanc()==3)
        {
            case_jouee2=jouer_un_pion_blanc3();
        }
        else
        {
            case_jouee2=jouer_un_pion_blanc();
        }
        system("cls");
        afficher(grille);
        printf("phase2\n");
        if(moulin_blanc(case_jouee2[0],case_jouee2[1]))
        {
            retirer_case_noire();
            system("cls");
            afficher(grille);
            printf("phase2\n");
        }




    }



    return 0;
}

