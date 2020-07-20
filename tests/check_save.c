#include <stdlib.h>
#include <check.h>
#include "../src/load_save/save.h"
#include "../src/load_save/load.h"
#include "main_template.h"


START_TEST(test_save_surface) {

  SDL_Surface *surface = NULL;

  surface = load_image("../images/flying.bmp", surface);

  /** méthode à tester **/

  ck_assert_int_eq(TO_BMP(surface, "../images/bird2.bmp"), 0);
  ck_assert_int_eq(TO_JPG(surface, "../images/bird2.jpg"), 0);
  ck_assert_int_eq(TO_PNG(surface, "../images/bird2.png"), 0);

  SDL_FreeSurface(surface);
}

END_TEST


Suite *save_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("SAVE CIMP");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_save_surface);
  suite_add_tcase(s, tc_core);

  return s;
}


int main(void) {
  return main_template(save_suite);
}
