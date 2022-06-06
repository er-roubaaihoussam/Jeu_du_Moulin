#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



int regle()
{



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




   SDL_Surface *image_regles=NULL;
   SDL_Surface *image_boutton=NULL;


    image_regles=IMG_Load("regles.png");
    image_boutton=IMG_Load("boutton.png");


   SDL_Texture* texture=NULL;
   SDL_Texture* texture_boutton=NULL;


   texture=SDL_CreateTextureFromSurface(renderer,image_regles);
   texture_boutton=SDL_CreateTextureFromSurface(renderer,image_boutton);


   SDL_Rect les_regles;

   les_regles.h=600;les_regles.w=800;
   les_regles.x=0;
   les_regles.y=0;

   SDL_Rect boutton_menu;

   boutton_menu.h=25;boutton_menu.w=77;
   boutton_menu.x=(800-boutton_menu.w)/2;boutton_menu.y=0;






   SDL_Event event;
   int vraie=SDL_TRUE;



   while(vraie)
   {
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,texture,NULL,&les_regles);
   SDL_RenderCopy(renderer,texture_boutton,NULL,&boutton_menu);

   SDL_RenderPresent(renderer);
       while(SDL_PollEvent(&event))
       {
           switch(event.type)
           {
          case SDL_QUIT:
              vraie=SDL_FALSE;
            break;
          /*case SDL_MOUSEMOTION:


                        printf("(%d,%d)\n",event.motion.x,event.motion.y);



            break;*/
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
               {
                   if(cliquer_sur_rect(boutton_menu.x,boutton_menu.y,boutton_menu.h,boutton_menu.w,event))
                   {
                        main(0,"");
                   }

               }
            break;


          default:
            break;
           }
       }


   }










   SDL_DestroyTexture(texture);
   SDL_DestroyTexture(texture_boutton);


   SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Quit();

   return 0;
}



int main(int argc, char** argv)
{



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




   SDL_Surface *image_menu=NULL;


    image_menu=IMG_Load("menu3.png");

   SDL_Texture* texture=NULL;


   texture=SDL_CreateTextureFromSurface(renderer,image_menu);



   SDL_Rect menu;

   menu.h=600;menu.w=800;
   menu.x=0;
   menu.y=0;

   SDL_Rect jouer_vs_joueur;
   SDL_Rect jouer_vs_machine;
   SDL_Rect regles;
   SDL_Rect quitter;
   quitter.x=250;quitter.y=482;
   quitter.h=33;quitter.w=267;

   jouer_vs_joueur.x=251;jouer_vs_joueur.y=336;
   jouer_vs_joueur.h=33;jouer_vs_joueur.w=267;


   jouer_vs_machine.x=251;jouer_vs_machine.y=385;
   jouer_vs_machine.h=33;jouer_vs_machine.w=267;

   regles.x=251;regles.y=433;
   regles.h=33;regles.w=267;




   SDL_Event event;
   int vraie=SDL_TRUE;



   while(vraie)
   {
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,texture,NULL,&menu);

   SDL_RenderPresent(renderer);
       while(SDL_PollEvent(&event))
       {
           switch(event.type)
           {
          case SDL_QUIT:
              vraie=SDL_FALSE;
            break;
          /*case SDL_MOUSEMOTION:


                        printf("(%d,%d)\n",event.motion.x,event.motion.y);



            break;*/
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
               {
                   if(cliquer_sur_rect(jouer_vs_joueur.x,jouer_vs_joueur.y,jouer_vs_joueur.h,jouer_vs_joueur.w,event))
                   {
                       joueur_vs_joueur();

                   }
                   else if(cliquer_sur_rect(jouer_vs_machine.x,jouer_vs_machine.y,jouer_vs_machine.h,jouer_vs_machine.w,event))
                   {
                       joueur_vs_machine();

                   }
                   else if(cliquer_sur_rect(regles.x,regles.y,regles.h,regles.w,event))
                   {
                        regle();
                   }
                   else if(cliquer_sur_rect(quitter.x,quitter.y,quitter.h,quitter.w,event))
                   {
                       vraie=SDL_FALSE;

                   }
               }
            break;


          default:
            break;
           }
       }


   }










   SDL_DestroyTexture(texture);


   SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Quit();

   return 0;
}

