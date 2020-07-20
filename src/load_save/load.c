#include "load.h"



SDL_Surface *load_image(char *img, SDL_Surface *imagedata){
	imagedata = IMG_Load(img);
	imagedata = SDL_ConvertSurfaceFormat(imagedata, SDL_PIXELFORMAT_ARGB8888, 0);
	return imagedata;
}

