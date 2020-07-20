#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void update_color_rect(SDL_Surface *image,SDL_Texture *texture,int x,int y,int w,int h,int r,int g, int b);

void load_window_test(char *img){

	bool quit = false;
	SDL_Event event;

    //SDL_Init(SDL_INIT_VIDEO);
	//IMG_Init(IMG_INIT_JPG);

	SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface *image = IMG_Load(img);


    image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);
    //Uint32 * pixels = (Uint32 *)image->pixels;


/**
SDL_Color colors[256];
int i;

for(i = 0; i < 256; i++)
{
    colors[i].r = colors[i].g = colors[i].b = i;
}


int palette=SDL_SetPaletteColors(image->format->palette, colors, 0, 256);


SDL_SetSurfacePalette(image, palette);
**/





//SDL_Surface* crop= crop_surface(image,100, 200, 200, 200);



//SDL_Renderer *rendererRectangle;
SDL_Rect rectangle;
   rectangle.x=10;
   rectangle.y=10;
   rectangle.w=200;
 rectangle.h=200;


	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
	while (!quit)
	{



int res;
int startx, starty;
int endx, endy;
		SDL_WaitEvent(&event);
   //bool leftMouseButtonDown = false;
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;

             case SDL_MOUSEBUTTONDOWN:
                  //leftMouseButtonDown = true;
				  SDL_GetMouseState(&startx, &starty);

			 case SDL_MOUSEBUTTONUP:
			 	SDL_GetMouseState(&endx, &endy);






		res=SDL_SetRenderDrawColor(renderer,255,0,0,0);


                  rectangle.x=event.motion.x;
                  rectangle.y=event.motion.y;
                  break;




		}


if(res==0){
    SDL_RenderFillRect(renderer,&rectangle);


}


	//SDL_Rect dstrect = { 5, 5, 320, 240 };
		//SDL_RenderCopy(renderer, texture, NULL, &rectangle);


		SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	}



	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();


}

void load2(char * img) {

	bool quit = false;
	SDL_Event event;
	SDL_Surface *image = IMG_Load(img);
	SDL_Window *window = SDL_CreateWindow("SDL2 Displaying Image",
										  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image->w, image->h, 0);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);


	image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

	SDL_Rect rectangle;

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);


   int x=0;
   int y=0;
   int h=0;
   int w=0;
   int res;
	while (!quit) {
		SDL_WaitEvent(&event);
		bool leftMouseButtonDown;
		switch (event.type) {
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_ENTER) {
				leftMouseButtonDown = false;
			}
            break;
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&rectangle.x, &rectangle.y);
			leftMouseButtonDown = true;
			break;
		case SDL_MOUSEBUTTONUP:
            leftMouseButtonDown = false;
			break;
        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown) {
                //int x, y;
                //SDL_GetMouseState(&x, &y);
                rectangle.w = event.motion.x - rectangle.x;
                rectangle.h = event.motion.y - rectangle.y;
                res=SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer, &rectangle);

                x=rectangle.x;
                y=rectangle.y;
               h=rectangle.h;
               w=rectangle.w;
            }
            break;
		}


		if(res==0 ){


 SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
 SDL_RenderDrawRect(renderer, &rectangle);
 SDL_RenderFillRect(renderer,&rectangle);
 SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));

		}

		SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

	}
  update_color_rect(image,texture, x,y,w , h,200,0, 0);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


/**** Asmaa : fonction pour la sauvegarde ***/

void update_color_rect(SDL_Surface *image,SDL_Texture *texture,int x,int y,int w,int h,int r,int g, int b){

SDL_Rect rect={x,y,w,h};
SDL_FillRect(image,&rect,SDL_MapRGB(image->format , 255 , 0 , 0 ));
//remplissage
//SDL_FillRect(image,NULL,SDL_MapRGB(image->format , 255 , 0 , 0 ));
//SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));
IMG_SaveJPG(image, "test_0418ver2.jpg",100);
}


/*
 * refpixel : pixel de référence
 * comppixel : pixel à comparer
 * tolerance : seuil de tolérance de la comparaison
 *
 * retourne true si les composantes rouge, vert, bleu du pixel à comparer ont chacune
 * une différence en-dessous du seuil de tolérance, avec le pixel de référence
 * */
bool is_under_threshold(SDL_Color refpixel, SDL_Color comppixel, Uint8 tolerance) {
    return abs(refpixel.r - comppixel.r) <= tolerance
    && abs(refpixel.g - comppixel.g) <= tolerance
    && abs(refpixel.b - comppixel.b) <= tolerance;
}
/*
 * color : couleur à sélectionner
 * tolerance : pixel ok si entre color et (color + t)
 *
 * Selection des zones dans une image des pixels d'une couleur color, avec une marge de tolérance
 * */
void selection_color(SDL_Color* color, Uint8 tolerance) {

	SDL_Surface *image = IMG_Load("flower.jpeg");
	SDL_Window *window = SDL_CreateWindow("SDL2 Displaying Image",
										  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image->w, image->h, 0);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

    SDL_Texture *texture_image = SDL_CreateTextureFromSurface(renderer, image);

    SDL_RenderCopy(renderer, texture_image, NULL, NULL);
    SDL_RenderPresent(renderer);

    void* tmp;
    Uint32* pixels;

    int pitch;

    image->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    Uint32* refimg = (Uint32*) image->pixels;

    Uint32 max_index = (image->w * image->h) - 1;
    Uint32 color_selection_border = SDL_MapRGB(image->format, 177, 42, 177);

    bool quit = false;
    SDL_Event event;
    int posx, posy;
    while (!quit) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&posx, &posy);
            SDL_Log("x:%d y:%d", posx, posy);
            SDL_GetRGB(refimg[posy * image->w + posx], image->format, &color->r, &color->g, &color->b);
            SDL_Texture* texture_selection = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                                image->w, image->h);
            SDL_SetTextureBlendMode(texture_selection, SDL_BLENDMODE_BLEND);
            SDL_LockTexture(texture_selection, NULL, &tmp, &pitch);
            pixels = tmp;
            for (Uint32 current_index = 0; current_index < max_index; current_index++) {
                SDL_Color current_pixel;
                SDL_GetRGB(refimg[current_index], image->format, &current_pixel.r, &current_pixel.g, &current_pixel.b);

                if (is_under_threshold(*color, current_pixel, tolerance))
                    pixels[current_index] = color_selection_border;
            }
            SDL_UpdateTexture(texture_selection, NULL, pixels, 32);
            SDL_UnlockTexture(texture_selection);
            SDL_RenderCopy(renderer, texture_image, NULL, NULL);
            SDL_RenderCopy(renderer, texture_selection, NULL, NULL);
            SDL_DestroyTexture(texture_selection);
            SDL_RenderPresent(renderer);
            break;
        }
    }

	SDL_DestroyTexture(texture_image);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

/*
int main(int argc, char* argv[]){

    //Test

    //TO_JPG("Nature.jpg");
    //load_window_test("Nature.jpg");
   //load2("Nature.jpg");
   SDL_Color color = {.r = 173, .g = 107, .b = 12};
   selection_color(&color, 5);
//TO_JPG("Nature.jpg");
//load_window_test("Nature.jpg");
   load2("flower.jpeg");
 //  SDL_Color color = {.r = 255, .g = 255, .b = 255};
  // selection_color(&color, 0);
  	IMG_Quit();
	SDL_Quit();
   return 0;
}
*/
