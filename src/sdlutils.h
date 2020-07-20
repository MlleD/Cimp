#ifndef SDLUTILS_H
#define SDLUTILS_H
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>




#define MAX_WINDOWS 3
struct fenetre {
  /** les images chargées **/
  SDL_Surface* imagedata[MAX_WINDOWS];
  /** pour garder une référence vers l'image original **/
  SDL_Surface* originalPic[MAX_WINDOWS];
  /** les textures des images chargées **/
  SDL_Texture * texture[MAX_WINDOWS];
  SDL_Surface *secondSurface;

};

struct fenetre structure;


/* Les données d'une image (image_data) sont représentées
 * par un tableau de type SDL_Surface**
 * dont l'indice 0 correspond à l'image et
 * les indices suivants, à des surfaces sur l'image
*/

/* Initialise une image_data */
SDL_Surface** init_image_data();


SDL_Surface *edit_image(SDL_Surface *imagedata, SDL_Surface *originalPic,SDL_Texture * texture);
void traitement_lot(SDL_Surface * imagedata[]);

/*Libère la mémoire associée à image_data*/
void free_image_data(SDL_Surface** image_data);
#endif // SDLUTILS_H
