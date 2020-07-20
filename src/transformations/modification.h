#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



extern SDL_Surface * modif_taille(SDL_Surface *surface, int w,int h);
extern int copier(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture,int x,int y,int w,int h,int x2,int y2);
extern int couper(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture1,SDL_Texture *texture2,int x,int y,int w,int h,int x2,int y2);
extern SDL_Surface *rotation(SDL_Surface *source);
extern void symetrie(SDL_Surface *source, char *modif,SDL_Texture *texture);
extern void add_marge(SDL_Surface *surface, SDL_Texture *texture, int x,int y,int w,int h);
extern SDL_Surface* coupe_surf(SDL_Surface* image, int x, int y, int width, int height);
extern Uint32 moyenne(SDL_Surface *surface, int i, int j, int n);
extern void floutage(SDL_Surface *imagedata,SDL_Texture *texture);
