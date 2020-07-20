

extern  SDL_Surface *selection_color(SDL_Color *color, Uint8 tolerance, SDL_Surface *imagedata, int posx, int posy);
extern int remplissage_all(SDL_Surface *surface, SDL_Texture *texture, Uint8 R, Uint8 G,Uint8 B);
extern int remplissage_selection(SDL_Surface *surface,SDL_Texture *texture, Uint8 R, Uint8 G,Uint8 B,int x,int y,int w,int h);
extern void gris(SDL_Surface *image, SDL_Texture *texture);
extern void negatif(SDL_Surface *image, SDL_Texture *texture);
extern void luminosite(SDL_Surface *image, SDL_Texture *texture,int n);
extern Uint8 fonction_luminosite(Uint8 c, int n);
extern void contraste(SDL_Surface *image, SDL_Texture *texture,int n);
extern Uint8 fonction_contraste(Uint8 c, double n);
extern void luminosite_selection(SDL_Surface *image, SDL_Texture *texture, int n,int x,int y,int w,int h);
extern void contraste_selection(SDL_Surface *image, SDL_Texture *texture,int n,int x,int y,int w,int h);
extern void negatif_selection(SDL_Surface *image, SDL_Texture *texture, int x,int y,int w,int h);
extern void gris_selection(SDL_Surface *image, SDL_Texture *texture, int x,int y,int w,int h);
extern void black_white(SDL_Surface *image, SDL_Texture *texture, int x,int y,int w,int h);
