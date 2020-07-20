#include <stdlib.h>
#include <string.h>
#include "cliconstants.h"

/* cmdargs est un tableau de string (type char**) contenant
 * - indice 0 : le nom de la commande
 * - indice 1 à n : les arguments de la commande
*/

/* Allocation en mémoire et mise à zéro de cmdargs */
char** new_cmdargs();

/* Remplissage de cmdargs à partir d'un input */
void fill_cmdargs(char input[], char* cmdargs[]);

/* Libération de la mémoire allouée pour cmdargs */
void free_cmdargs(char* cmdargs[]);
