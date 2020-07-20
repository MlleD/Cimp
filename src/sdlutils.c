#include "sdlutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "transformations/trans_couleurs.h"
#include "cli/cmdprocessing.h"
#include "cli/cmdargs.h"
#include "load_save/save.h"
#include "transformations/modification.h"
#define NB_SURFACES 3
#define UNUSED(x) (void)(x)

SDL_Surface** init_image_data() {
    SDL_Surface** imagedata = calloc(NB_SURFACES, sizeof(*imagedata));
    return imagedata;
}





/** Methode pour le traitement par lot **/


void traitement_lot(SDL_Surface *imagedata[])
{

    /****** creation du thread  *********/
    int threadReturnValue;
    SDL_Thread *thread = SDL_CreateThread(edit_command_lot, "test", NULL);

    SDL_Window *window[MAX_WINDOWS];
    SDL_Renderer *renderer[MAX_WINDOWS];
    SDL_Texture *texture[MAX_WINDOWS];

    char window_name[15];
    int size_window_name = sizeof window_name;
    memset(window_name, 0, size_window_name);

    for (int i = 0; i < MAX_WINDOWS; i++)
    {
        SDL_snprintf(window_name, size_window_name, "cimp - image%d", i + 1);

        if (imagedata[i] == NULL)
        {
            window[i] = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
        }
        else
        {
            window[i] = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, imagedata[i]->w, imagedata[i]->h, 0);
            renderer[i] = SDL_CreateRenderer(window[i], -1, 0);
            texture[i] = SDL_CreateTextureFromSurface(renderer[i], imagedata[i]);
        }
    }

    int quit = 0;
    SDL_Event event;

    while (!quit)
    {

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                SDL_DestroyWindow(SDL_GetWindowFromID(event.window.windowID));
                break;
            }
            break;
        }

        if (commande == 12)
        {
            for (int i = 0; i < MAX_WINDOWS; i++)
            {
               if (imagedata[i] != NULL)
               {
                   gris(imagedata[i], texture[i]);
               }
            }
            commande = 0;
        }

        if (commande == 5)
        {
            for (int i = 0; i < MAX_WINDOWS; i++)
            {
                if (imagedata[i] != NULL)
                {
                    negatif(imagedata[i], texture[i]);
                }
            }
            commande = 0;
        }

        if (commande == 6)
        {

            R1 = (Uint8)R;
            G1 = (Uint8)G;
            B1 = (Uint8)B;
            for (int i = 0; i < MAX_WINDOWS; i++)
            {
                if (imagedata[i] != NULL)
                {
                    remplissage_all(imagedata[i], texture[i], R1, G1, B1);
                }
            }
            commande = 0;
        }

        if (commande == 7)
        {

            R1 = (Uint8)R;
            G1 = (Uint8)G;
            B1 = (Uint8)B;
            for (int i = 0; i < MAX_WINDOWS; i++)
            {
                if (imagedata[i] != NULL)
                {
                    black_white(imagedata[i], texture[i], 0, 0, 0, 0);
                }
            }
            commande = 0;
        }

        if (commande == 8)
        {
            for (int i = 0; i < MAX_WINDOWS; i++)
            {
                if (imagedata[i] != NULL)
                {
                    symetrie(imagedata[i], "verticale", texture[i]);
                }
            }
            commande = 0;
        }

        if (commande == 9)
        {
            for (int i = 0; i < MAX_WINDOWS; i++)
            {
                if (imagedata[i] != NULL)
                {
                    symetrie(imagedata[i], "horizontale", texture[i]);
                }
            }
            commande = 0;
        }
        for (int i = 0; i < MAX_WINDOWS; i++)
        {
            if (imagedata[i] != NULL)
            {
                SDL_RenderPresent(renderer[i]);
                SDL_RenderCopy(renderer[i], texture[i], NULL, NULL);
            }
        }
    }

    SDL_WaitThread(thread, &threadReturnValue);
}



/** fonction pour editer une image **/

SDL_Surface *edit_image(SDL_Surface *imagedata, SDL_Surface *originalPic,SDL_Texture * texture) {

/****** creation du thread  *********/
    int   threadReturnValue;
    SDL_Thread *thread=SDL_CreateThread(edit_command,"test",NULL );


    //S'il n'y a pas d'image
    if (imagedata == NULL) {

        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 fenetre",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  imagedata->w, imagedata->h, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    texture = SDL_CreateTextureFromSurface(renderer, imagedata);

    int quit=0;
    int res=1;
    int res2=1;
    int res3=1;

    /** rectangles pour la selection **/
	SDL_Rect rectangle;
    SDL_Rect rectangle2;
    SDL_Rect rectangle3;
    /** coordonnees des selections rectangulaire **/
    int x=0;
    int y=0;
    int h=0;
    int w=0;

    int x2=0;
    int y2=0;
    int h2=0;
    int w2=0;

    int x3=0;
    int y3=0;

    UNUSED(h2);
    UNUSED(w2);

    int posx, posy;
    bool leftMouseButtonDown;


    /*** Parametres pour une deuxieme fenetre (recadrage)****/

    SDL_Renderer   *second_renderer=NULL;
    SDL_Texture    *second_texture=NULL;

    /** Parametres pour une deuxieme image ou on va copier une region de la premiere image **/
    SDL_Window  *window_copier=NULL;
    SDL_Renderer   *renderer_copier=NULL;
    SDL_Texture   * texture_copier=NULL;

    SDL_Surface *surfaceBefore;
    SDL_Surface *surfaceSelect;
    surfaceSelect = SDL_CreateRGBSurface(imagedata->flags, imagedata->w, imagedata->h, imagedata->format->BitsPerPixel, imagedata->format->Rmask, imagedata->format->Gmask, imagedata->format->Bmask, imagedata->format->Amask);


    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


	SDL_Event event;

    while (!quit) {

		SDL_WaitEvent(&event);

	if(commande!=27){
        SDL_BlitSurface(imagedata, NULL,surfaceSelect,NULL);
	}
    switch (event.type) {

    case SDL_QUIT:
    quit=1;
    printf("taper 'exit edit' pour quitter le mode edit\n");
    break;

    case SDL_WINDOWEVENT:

        switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:

            SDL_DestroyWindow(SDL_GetWindowFromID(event.window.windowID));

            break;
        }

        break;

    case SDL_MOUSEMOTION:

            if (leftMouseButtonDown && (commandeSelection==11 || commande==19)) {

                rectangle.w = event.motion.x - rectangle.x;
                rectangle.h = event.motion.y - rectangle.y;
                res=SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer, &rectangle);
                x=rectangle.x;
                y=rectangle.y;
                h=rectangle.h;
                w=rectangle.w;

            }
              /** deuxieme selection **/
              if (leftMouseButtonDown) {


                if(commande==20){
                rectangle2.w = event.motion.x - rectangle2.x;
                rectangle2.h = event.motion.y - rectangle2.y;
                res2=SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer, &rectangle2);
                }
                /** selectionner dans une autre image **/
                if(commande==31){
                rectangle3.w = event.motion.x - rectangle3.x;
                rectangle3.h = event.motion.y - rectangle3.y;
                res3=SDL_SetRenderDrawColor(renderer_copier, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer_copier, &rectangle3);
                }
                x3=rectangle3.x;
                y3=rectangle3.y;


            }


            break;
    case SDL_MOUSEBUTTONUP:
                leftMouseButtonDown = false;
			break;

    case SDL_MOUSEBUTTONDOWN:
                leftMouseButtonDown = true;
                switch(event.button.button ){

                    case SDL_BUTTON_RIGHT:

                    /** UNDO selection pixel **/
                    SDL_BlitSurface(surfaceSelect, NULL,imagedata,NULL);
                    SDL_UpdateTexture(texture, NULL, surfaceSelect->pixels, surfaceSelect->w * sizeof(Uint32));

                    break;
                    case SDL_BUTTON_LEFT:

                    /** selection pixel **/
                    if(commande==27){

                        SDL_GetMouseState(&posx, &posy);
                        SDL_Color color = {R1,G1,B1,0};
                        surfaceBefore=selection_color(&color, threshold, imagedata,posx, posy);
                        SDL_BlitSurface(surfaceBefore, NULL,imagedata,NULL);
                        SDL_UpdateTexture(texture, NULL, surfaceBefore->pixels, surfaceBefore->w * sizeof(Uint32));

               }
                    break;


                    }




 /** recuperer x et y de la selection **/

 if(commandeSelection==11 || commande==19){

 SDL_GetMouseState(&rectangle.x, &rectangle.y);


  }

  if(commande==20){

 SDL_GetMouseState(&rectangle2.x, &rectangle2.y);

}

  if(commande==31){

 SDL_GetMouseState(&rectangle3.x, &rectangle3.y);

}

			    break;



}

/** dessin du rectangle de la selection **/
if(res==0){

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &rectangle);



}

if(res2==0){

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &rectangle2);
}


 if(commande==31 && res3==0){

            SDL_SetRenderDrawColor(renderer_copier, 255, 0, 0, 0);
            SDL_RenderDrawRect(renderer_copier, &rectangle3);

        }


/** supprimer la selection **/

if(commande==18){

    rectangle.x=0;
    rectangle.y=0;
    rectangle.w=0;
    rectangle.h=0;

    rectangle2.x=0;
    rectangle2.y=0;
    rectangle2.w=0;
    rectangle2.h=0;


    commande=0;
    commandeSelection=0;

}


/** copier une partie de l'image dans la meme fenetre **/

if(commande==21){

copier(imagedata, imagedata, texture,x, y, w, h, x2, y2);

commande=0;
res2=1;

}


/** couper une partie de l'image dans la meme fenetre **/

if(commande==28){

couper(imagedata, imagedata, texture,NULL, x,y,w,h, x2, y2);
commande=0;
res2=1;

}


/** copier une partie de l'image dans une autre fenetre (image2) **/
if(commande==32){

copier(imagedata, structure.imagedata[1],texture_copier,x, y, w, h, x3, y3);
commande=0;
}

/** copier une partie de l'image dans une autre fenetre (image1) **/
if(commande==48){

copier(imagedata, structure.imagedata[0],texture_copier,x, y, w, h, x3, y3);
commande=0;
}

/** copier une partie de l'image dans une autre fenetre (image3) **/
if(commande==49){

copier(imagedata, structure.imagedata[2],texture_copier,x, y, w, h, x3, y3);
commande=0;
}

/** couper une partie de l'image dans une autre fenetre (image2)**/
if(commande==33){

couper(imagedata, structure.imagedata[1],texture,texture_copier,x, y, w, h, x3, y3);
commande=0;
}

/** couper une partie de l'image dans une autre fenetre (image3) **/
if(commande==50){

couper(imagedata, structure.imagedata[2],texture,texture_copier,x, y, w, h, x3, y3);
commande=0;
}

/** couper une partie de l'image dans une autre fenetre (image1) **/
if(commande==51){

couper(imagedata, structure.imagedata[0],texture,texture_copier,x, y, w, h, x3, y3);
commande=0;
}



/*** Recadrage rectangulaire ***/

if(res==0 && commande==13){

        structure.secondSurface = coupe_surf(imagedata,x,y,w, h);
        imagedata=modif_taille(imagedata, w, h);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_BlitSurface(structure.secondSurface,NULL,imagedata,NULL);
        SDL_SetWindowSize(window,w,h);
        renderer = SDL_CreateRenderer(window, -1, 0);
        texture= SDL_CreateTextureFromSurface(renderer, structure.secondSurface);
        SDL_UpdateTexture(texture, NULL, structure.secondSurface->pixels, structure.secondSurface->w * sizeof(Uint32));

        commande=18;

}


/** view image2 pour copier/couper **/
    if(commande==29){


        window_copier = SDL_CreateWindow("image2",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  structure.imagedata[1]->w,  structure.imagedata[1]->h, 0);
        renderer_copier = SDL_CreateRenderer(window_copier, -1, SDL_RENDERER_ACCELERATED);
        texture_copier = SDL_CreateTextureFromSurface(renderer_copier, structure.imagedata[1] );
        commande=0;

               }

 /** view image1 pour copier/couper **/
    if(commande==45){


        window_copier = SDL_CreateWindow("image1",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  structure.imagedata[0]->w,  structure.imagedata[0]->h, 0);
        renderer_copier = SDL_CreateRenderer(window_copier, -1, SDL_RENDERER_ACCELERATED);
        texture_copier = SDL_CreateTextureFromSurface(renderer_copier, structure.imagedata[0] );
        commande=0;

               }

/** view image3 pour copier/couper **/
  if(commande==46){


        window_copier = SDL_CreateWindow("image3",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  structure.imagedata[2]->w,  structure.imagedata[2]->h, 0);
        renderer_copier = SDL_CreateRenderer(window_copier, -1, SDL_RENDERER_ACCELERATED);
        texture_copier = SDL_CreateTextureFromSurface(renderer_copier, structure.imagedata[2] );
        commande=0;

               }

/** remplissage d'une selection **/

if(res==0 && commande==10 && commandeSelection==11){


R1 =(Uint8) R;
G1 =(Uint8) G;
B1 =(Uint8) B;
remplissage_selection(imagedata,texture,R1,G1,B1, x,y,w,h);
commande=0;

}


/*** Remplissage  ***/
if(commande==4){



R1 =(Uint8) R;
G1 =(Uint8) G;
B1 =(Uint8) B;

    remplissage_all(imagedata, texture, R1, G1, B1);
   SDL_UpdateTexture(texture, NULL, imagedata->pixels, imagedata->w * sizeof(Uint32));
  commande=0;

}



/** negatif **/
if(commande==5){

negatif(imagedata, texture);

commande=0;

}



if(commande==16){

negatif_selection(imagedata, texture,x,y,w,h);
  commande=0;
}


/** floutage **/
if(commande==15){

floutage(imagedata,texture);

commande=0;

}

/** luminosite **/

if(commande==6){

luminosite_selection(imagedata,texture,valeurN,x,y,w,h);
commande=0;
}


if(commande==7){

luminosite(imagedata,texture,valeurN);
commande=0;
}

/** contraste **/
if(commande==8){

contraste(imagedata,texture,valeurN );
commande=0;
}

if(commande==80 && commandeSelection==11){

contraste_selection(imagedata,texture,valeurN,x,y,w,h );
commande=0;
}


/** gris **/
if(commande==12){

gris(imagedata,texture);

   commande=0;
}

/** gris selection **/
if(commande==17 && commandeSelection==11){

    gris_selection(imagedata,texture,x,y,w,h);

}

/** annuler toutes les modifications **/

if(commande==22){

if(imagedata->w != originalPic->w){
SDL_SetWindowSize(window,originalPic->w, originalPic->h);
SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED );
imagedata=modif_taille(imagedata, originalPic->w,originalPic->h);
}

SDL_BlitSurface(originalPic, NULL,imagedata,NULL);
texture = SDL_CreateTextureFromSurface(renderer,imagedata );
SDL_UpdateTexture(texture, NULL, originalPic->pixels, originalPic->w * sizeof(Uint32));

commande=0;
commandeSelection=0;
res=1;
res2=1;

}



if(commande==23){
imagedata=modif_taille(imagedata, w_commande,h_commande);

/**SDL_BlitSurface(imagedata, NULL,imagedata,NULL);
texture = SDL_CreateTextureFromSurface(renderer,imagedata );
SDL_UpdateTexture(texture, NULL, imagedata->pixels, imagedata->w * sizeof(Uint32));**/

SDL_SetWindowSize(window,w_commande, h_commande);
SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED );

commande=0;

}

/** ROTATION 90 **/

if(commande==34){

        imagedata=rotation(imagedata);
        SDL_SetWindowSize(window,imagedata->w, imagedata->h);
        texture = SDL_CreateTextureFromSurface(renderer,imagedata );
        SDL_UpdateTexture(texture, NULL, imagedata->pixels, imagedata->w * sizeof(Uint32));
        SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED );

commande=0;

}

/** ROTATION 180 **/

if(commande==35){

        symetrie(imagedata, "horizontale",NULL);
        symetrie(imagedata, "verticale",NULL);
        SDL_SetWindowSize(window,imagedata->w, imagedata->h);
        texture = SDL_CreateTextureFromSurface(renderer,imagedata );
        SDL_UpdateTexture(texture, NULL, imagedata->pixels, imagedata->w * sizeof(Uint32));
        SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED );

        commande=0;

}

/** ROTATION 270 **/

if(commande==36){

        symetrie(imagedata, "horizontale",NULL);
        symetrie(imagedata, "verticale",NULL);
        imagedata=rotation(imagedata);
        SDL_SetWindowSize(window,imagedata->w, imagedata->h);
        texture = SDL_CreateTextureFromSurface(renderer,imagedata );
        SDL_UpdateTexture(texture, NULL, imagedata->pixels, imagedata->w * sizeof(Uint32));
        SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED );
        commande=0;

}


/** symetrie horizontale **/

if(commande==24){

symetrie(imagedata, "horizontale",texture);

commande=0;


}

/** symetrie verticale **/
if(commande==25){

symetrie(imagedata, "verticale",texture);
commande=0;

}

if(commande==60){

    black_white(imagedata, texture,0,0,0,0);
    commande = 0;
}

if(commande==61){

    black_white(imagedata,texture,x,y,w,h);
    commande = 0;
}



/** ajout d'une marge autour de l'image selectionné **/
if(commande==26){


add_marge(imagedata,texture,x,y,w,h);
/**pour effacer la selection **/
commande=18;

}





if(commande==101){
commande=0;
break;
}


        SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		/** deuxieme fenetre **/
  if(second_renderer) {

            SDL_RenderCopy(second_renderer, second_texture, NULL, NULL);
            SDL_RenderPresent(second_renderer);
        }
  if(renderer_copier) {
            SDL_RenderPresent(renderer_copier);
            SDL_RenderCopy(renderer_copier, texture_copier, NULL, NULL);

        }
		}


commande=0;

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);



 /** Attente jusqu'à la fin du thread ***/


SDL_WaitThread(thread,&threadReturnValue);

return imagedata;
}


void free_image_data(SDL_Surface** image_data) {
    for (int i = 0; i < NB_SURFACES; i++) {
        SDL_FreeSurface(image_data[i]);
    }
	IMG_Quit();
	SDL_Quit();
}
