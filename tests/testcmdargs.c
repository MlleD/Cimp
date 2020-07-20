#include <check.h>
#include "../src/cli/cmdargs.h"
#include "main_template.h"

// Input avec des mots séparés par des espaces
START_TEST (test_fill_with_s_input)
{
    char** cmdargs = new_cmdargs();
    if (cmdargs != NULL) 
    {
        char input[] = "Test d'une commande";
        fill_cmdargs(input, cmdargs);
        ck_assert_str_eq(cmdargs[0], "Test");
        ck_assert_str_eq(cmdargs[1], "d'une");
        ck_assert_str_eq(cmdargs[2], "commande");
        free_cmdargs(cmdargs);
    }
}
END_TEST

// Input avec whitespaces
START_TEST (test_fill_with_ws_input)
{
    char** cmdargs = new_cmdargs();
    if (cmdargs != NULL) 
    {
        char input[] = "Test    d'une commande";
        fill_cmdargs(input, cmdargs);
        ck_assert_str_eq(cmdargs[0], "Test");
        ck_assert_str_eq(cmdargs[1], "d'une");
        ck_assert_str_eq(cmdargs[2], "commande");
        free_cmdargs(cmdargs);
    }
}
END_TEST

// Deux remplissages successifs
START_TEST (test_double_fill)
{
    char** cmdargs = new_cmdargs();
    if (cmdargs != NULL) 
    {
        char input[25];
        strncpy(input, "Test    d'une commande", 23);
        fill_cmdargs(input, cmdargs);
        ck_assert_str_eq(cmdargs[0], "Test");
        ck_assert_str_eq(cmdargs[1], "d'une");
        ck_assert_str_eq(cmdargs[2], "commande");
        strncpy(input, "Deuxième commande", 19);
        fill_cmdargs(input, cmdargs);
        ck_assert_str_eq(cmdargs[0], "Deuxième");
        ck_assert_str_eq(cmdargs[1], "commande");
        free_cmdargs(cmdargs);
    }
}
END_TEST

Suite *cmdargs_suite (void)
{
    TCase *tc_fill;
    Suite *s;
    tc_fill = tcase_create ("Cmdargs_fill");
    tcase_add_test (tc_fill, test_fill_with_s_input);
    tcase_add_test (tc_fill, test_fill_with_ws_input);
    tcase_add_test (tc_fill, test_double_fill);

    s = suite_create ("Cmdargs");
    suite_add_tcase (s, tc_fill);
    return s;
}

int main(void) {
    return main_template(cmdargs_suite);
}