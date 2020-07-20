#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface * modif_taille(SDL_Surface *surface, int w, int h)
{

    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = w;
    dest.h = h;
    SDL_Surface *resize = SDL_CreateRGBSurface(surface->flags, w, h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    SDL_BlitScaled(surface, NULL, resize, &dest);

    return resize;
}




int copier(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture,int x,int y,int w,int h,int x2,int y2){

    int res;
    SDL_Rect srcrect1 = { x, y, w, h };
    SDL_Rect dstrect = { x2, y2, w, h };

    SDL_BlitSurface( surface1, &srcrect1, surface2, &dstrect );
    // SDL_FillRect(imagedata[0],&srcrect1,SDL_MapRGB(imagedata[0]->format , 0 , 0 , 0 ));
    res=SDL_UpdateTexture(texture, NULL, surface2->pixels, surface2->w * sizeof(Uint32));

    return res;

 }

int couper(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture1, SDL_Texture *texture2, int x, int y, int w, int h, int x2, int y2)
{
    int res;
    SDL_Rect srcrect1 = {x, y, w, h};
    SDL_Rect dstrect = {x2, y2, w, h};

    SDL_BlitSurface(surface1, &srcrect1, surface2, &dstrect);
    SDL_FillRect(surface1, &srcrect1, SDL_MapRGB(surface1->format, 0, 0, 0));
    res=SDL_UpdateTexture(texture1, NULL, surface1->pixels, surface1->w * sizeof(Uint32));

    if (texture2 != NULL)
    {
        res=SDL_UpdateTexture(texture2, NULL, surface2->pixels, surface2->w * sizeof(Uint32));
    }

    return res;

}

SDL_Surface *rotation(SDL_Surface *source)
{
    SDL_Surface *reverse = SDL_CreateRGBSurface(source->flags, source->h, source->w, source->format->BitsPerPixel, source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
    Uint32 *pixels = (Uint32 *)reverse->pixels;
    Uint32 *pixelsSource = (Uint32 *)source->pixels;
    for (int x = 0, rx = reverse->h - 1; x < reverse->h; x++, rx--)
    {
        for (int y = 0, ry = reverse->w - 1; y < reverse->w; y++, ry--)
        {
            Uint32 pixel = pixelsSource[(y * source->w) + x];

            pixels[(x * reverse->w) + ry] = pixel;
        }
    }

    return reverse;
}

void symetrie(SDL_Surface *source, char *modif, SDL_Texture *texture)
{
    SDL_Surface *reverse = SDL_CreateRGBSurface(source->flags, source->w, source->h, source->format->BitsPerPixel, source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
    Uint32 *pixels = (Uint32 *)reverse->pixels;
    Uint32 *pixelsSource = (Uint32 *)source->pixels;
    for (int x = 0, rx = reverse->w - 1; x < reverse->w; x++, rx--)
    {
        for (int y = 0, ry = reverse->h - 1; y < reverse->h; y++, ry--)
        {
            Uint32 pixel = pixelsSource[(y * source->w) + x];

            if (strcmp(modif, "horizontale") == 0)
            {
                pixels[(y * reverse->w) + rx] = pixel;
            }

            if (strcmp(modif, "verticale") == 0)
            {
                pixels[(ry * reverse->w) + x] = pixel;
            }
        }
    }
    SDL_BlitSurface(reverse, NULL, source, NULL);
    if (texture != NULL)
    {
        SDL_UpdateTexture(texture, NULL, reverse->pixels, reverse->w * sizeof(Uint32));
    }
}

SDL_Surface *coupe_surf(SDL_Surface *image, int x, int y, int width, int height)

{
    SDL_Surface *surface = SDL_CreateRGBSurface(image->flags, width, height, image->format->BitsPerPixel, image->format->Rmask, image->format->Gmask, image->format->Bmask, image->format->Amask);
    SDL_Rect rect = {x, y, width, height};
    SDL_BlitSurface(image, &rect, surface, 0);

    return surface;
}

int add_marge(SDL_Surface *surface, SDL_Texture *texture, int x, int y, int w, int h)
{
    int res;
    SDL_Surface *selection = coupe_surf(surface, x, y, w, h);

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));

    SDL_Rect destination = {x, y, w, h};
    /** pour placer l'image dans le centre **/
    destination.x = surface->w / 2 - selection->w / 2;
    destination.y = surface->h / 2 - selection->h / 2;
    SDL_BlitSurface(selection, NULL, surface, &destination);
    res=SDL_UpdateTexture(texture, NULL, surface->pixels, surface->w * sizeof(Uint32));

    return res;
}

Uint32 moyenne(SDL_Surface *surface, int i, int j, int n)
{
    int debuth = SDL_max(i - n, 0);
    int debutw = SDL_max(j - n, 0);
    int finh = SDL_min(i + n, surface->h - 1);
    int finw = SDL_min(j + n, surface->w - 1);
    int nb_pixel = ((finh - debuth) * (finw - debutw));
    Uint32 *p = surface->pixels;

    Uint32 sum_r = 0, sum_g = 0, sum_b = 0;
    SDL_Color color;

    for (i = debuth; i < finh; i++)
        for (j = debutw; j < finw; j++)
        {
            SDL_GetRGB(p[i * surface->w + j], surface->format, &color.r, &color.g, &color.b);
            sum_r += color.r;
            sum_g += color.g;
            sum_b += color.b;
        }

    return SDL_MapRGB(surface->format, sum_r / nb_pixel, sum_g / nb_pixel, sum_b / nb_pixel);
}

void floutage(SDL_Surface *imagedata, SDL_Texture *texture)
{

    Uint32 *pixels = (Uint32 *)imagedata->pixels;
    for (int i = 0; i < imagedata->h; i++)
    {
        for (int j = 0; j < imagedata->w; j++)
        {
            pixels[i * imagedata->w + j] = moyenne(imagedata, i, j, 6);
        }
    }
    SDL_UpdateTexture(texture, NULL, imagedata->pixels, imagedata->w * sizeof(Uint32));
}

