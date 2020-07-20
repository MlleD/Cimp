#include <stdlib.h>
#include <check.h>
#include "../src/transformations/trans_couleurs.h"
#include "../src/load_save/load.h"
#include "main_template.h"


START_TEST(test_remplissage_all) {

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 0, 0, 32, SDL_PIXELFORMAT_RGBA32);

    surface = load_image("../images/flying.bmp", surface);
    SDL_Window *window = SDL_CreateWindow("cimp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, surface->w, surface->h, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    ck_assert_int_eq(remplissage_all(surface, texture, 255, 0, 0), 0);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
END_TEST

START_TEST(test_remplissage_selection) {

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 0, 0, 32, SDL_PIXELFORMAT_RGBA32);

    surface=load_image("../images/flying.bmp", surface);
    SDL_Window *window = SDL_CreateWindow("cimp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, surface->w, surface->h, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    ck_assert_int_eq(remplissage_selection(surface, texture, 255, 0, 0, 40, 20, 200, 200), 0);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
END_TEST


Suite *modif_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("TRANSFORMATION COULEURS CIMP");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_remplissage_all);
  tcase_add_test(tc_core, test_remplissage_selection);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
    return main_template(modif_suite);
}
