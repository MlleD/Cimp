#include "view.h"





/** fonction pour voir une image **/

void view_one(SDL_Surface * imagedata){

     SDL_Window *window;
     SDL_Renderer *renderer;
     SDL_Texture *texture;

     window = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  imagedata->w, imagedata->h, 0);
     renderer = SDL_CreateRenderer(window, -1, 0);
     texture= SDL_CreateTextureFromSurface(renderer, imagedata);

    int quit=0;
    SDL_Event event;

  while (!quit) {

      SDL_WaitEvent(&event);
      switch (event.type) {

        case SDL_QUIT:
                quit = 1;
                break;

    }

     SDL_RenderPresent(renderer);
     SDL_RenderCopy(renderer, texture, NULL, NULL);

}

SDL_DestroyWindow(window);

}


/** fonction pour voir toutes les images **/

void view_all(SDL_Surface * imagedata[]){
    int max_window = 3;
    SDL_Window *window[3];
    SDL_Renderer *renderer[3];
    SDL_Texture *texture[3];
    char window_name[15];
    int size_window_name = sizeof window_name;
    memset(window_name, 0, size_window_name);

    // Création des fenêtres, et éventuellement renderer et texture
    for (int i = 0; i < max_window; i++)
    {
        SDL_snprintf(window_name, size_window_name, "cimp - image%d", i + 1);
        if (imagedata[i] == NULL)
        {
            SDL_snprintf(window_name, size_window_name, "cimp - image%d", i + 1);
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
                        // SDL_Log("ferme %d",event.window.windowID);
                        SDL_DestroyWindow(SDL_GetWindowFromID(event.window.windowID));
                        break;
                }
                break;
        }
        for (int i = 0; i < max_window; i++)
        {
            if (imagedata[i] != NULL)
            {
                SDL_RenderPresent(renderer[i]);
                SDL_RenderCopy(renderer[i], texture[i], NULL, NULL);
            }
        }
    }
    for (int i = 0; i < max_window; i++)
    {
        if (imagedata[i] != NULL)
        {
            SDL_DestroyRenderer(renderer[i]);
        }
    }
}
