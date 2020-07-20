#include <stdlib.h>
#include <check.h>
#include "../src/transformations/modification.h"
#include "../src/load_save/load.h"
#include "main_template.h"
#include "../src/load_save/save.h"

START_TEST(test_copier) {

  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 0, 0, 32, SDL_PIXELFORMAT_RGBA32);

  surface = load_image("../images/flying.bmp", surface);
  SDL_Window *window = SDL_CreateWindow("cimp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, surface->w, surface->h, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  int result = copier(surface, surface, texture, 40, 60, 500, 200, 10, 10);

  ck_assert_int_eq(result, 0);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

END_TEST

START_TEST(test_couper) {

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 0, 0, 32, SDL_PIXELFORMAT_RGBA32);

    surface=load_image("../images/flying.bmp", surface);
    SDL_Window *window = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  surface->w, surface->h, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture= SDL_CreateTextureFromSurface(renderer, surface);

    int result=couper(surface, surface,texture,NULL,40,60,500,200,10,10);

    ck_assert_int_eq(result, 0);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

END_TEST

START_TEST(test_add_marge) {

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 0, 0, 32, SDL_PIXELFORMAT_RGBA32);

    surface=load_image("../images/flying.bmp", surface);
    SDL_Window *window = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  surface->w, surface->h, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture= SDL_CreateTextureFromSurface(renderer, surface);

    int result=add_marge(surface,texture,40,60,500,200);

    ck_assert_int_eq(result, 0);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

END_TEST

Suite *modif_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("MODIFICATION CIMP");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_copier);
  tcase_add_test(tc_core, test_couper);
  tcase_add_test(tc_core, test_add_marge);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
    return main_template(modif_suite);
}
