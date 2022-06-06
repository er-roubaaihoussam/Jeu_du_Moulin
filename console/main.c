#include <stdio.h>
#include <stdlib.h>


//cette fonction permet d'afficher le contenu d'un fichier texte
void afficher_fichier(char *nom){
    char *nom_du_fichier = nom;
    char lire_chaine[50];
    FILE *fichier = NULL;
    if((fichier = fopen(nom_du_fichier,"r")) == NULL)                       //au cas où un erreur d'ouverture du fichier
    {
        fprintf(stderr,"erreur d'ouvrir le fichier %s\n",nom_du_fichier);
        return -1;
    }
    while(fgets(lire_chaine,sizeof(lire_chaine),fichier) != NULL)            //lecture du contenu du fichier
        printf("%s",lire_chaine);
    fclose(fichier);
}

//cette fonction permet d'afficher les regles du jeu à partir d'un fichier texte 'regles.txt'
void regles()
{
    int choix;
    system("cls");
    afficher_fichier("regles.txt");
    printf("\n\n\t\t\t Tapez sur 0 pour retourner a l'accueil : ");
    scanf("%d",&choix);
    system("cls");
}







int main()
{
    int choix;
    do{
    afficher_fichier("accueil.txt");
    printf("\n\n\t\t\tVeuillez choisir un nombre pour continuer : ");
    scanf("%d",&choix);
    switch(choix){
    case 1:joueur_vs_joueur();
        break;
    case 2:joueur_vs_machine_minimax();
        break;
    case 3:joueur_vs_machine_alphaBeta();
        break;
    case 4:regles();
        break;
    }
    }
    while (choix!=5);
    system("cls");
    return 0;
}
