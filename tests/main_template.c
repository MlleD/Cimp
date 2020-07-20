#include "main_template.h"

int main_template(Suite* (*pf) (void))
{
    int failures;
    Suite *s;
    SRunner *sr;
    s = pf ();
    sr = srunner_create (s);
    srunner_run_all (sr, CK_VERBOSE);
    failures = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}