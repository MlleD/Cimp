#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "../load_save/load.h"
#include "../load_save/save.h"
#include "../sdlutils.h"
#include "../view.h"

extern Uint8 R1,G1,B1;

extern int commande;
extern int commandeSelection;
extern Uint8 threshold;
extern long int R,G,B;
extern int valeurN;
extern int h_commande,w_commande;

int is_script_mode;
FILE* script_fd;
#define SCRIPT_COMMENT_SYMBOL '#'
/* Traitement des commandes*/
void process_command();
int edit_command();
int edit_command_lot();
void print_help();
void print_help_edit();


/* *
 * @param argc : nombre d'arguments du programme
 * @param argv : tableau d'arguments du programme
 * Verifie que les arguments du programme sont corrects
 * @return 1 en cas de succès, 0 sinon
*/
int check_arguments(int argc, char** argv);

