
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "save.h"


//Sauvegarder une image dans un autre format ou dans le même format




void TO_JPG(SDL_Surface * imagedata, char *nom){

 if (imagedata == NULL) {
	fprintf(stderr, "Impossible de charger l'image ou de creer la surface : %s\n",
		SDL_GetError());
	exit(1);
    }

    IMG_SaveJPG(imagedata, nom, 100);


}


void TO_PNG(SDL_Surface * imagedata, char *nom){

 if (imagedata == NULL) {
	fprintf(stderr, "Impossible de charger l'image ou de creer la surface : %s\n",
		SDL_GetError());
	exit(1);
    }

    IMG_SavePNG(imagedata, nom);


}

void TO_BMP(SDL_Surface * imagedata, char *nom){

 if (imagedata == NULL) {
	fprintf(stderr, "Impossible de charger l'image ou de creer la surface : %s\n",
		SDL_GetError());
	exit(1);
    }

    SDL_SaveBMP(imagedata, nom);


}




