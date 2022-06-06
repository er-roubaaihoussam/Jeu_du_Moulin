#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



int regle(int argc, char** argv)
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
                        joueur_vs_joueur();
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

