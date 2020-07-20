#include "cmdargs.h"

/* Fonction appelée seulement dans ce fichier :*/
/* Vidage des arguments de cmdargs */
void flush_args(char* cmdargs[]);

char** new_cmdargs() {
    char** cmdargs = calloc(MAX_ARGS, sizeof(*cmdargs));
    return cmdargs;
}

void fill_cmdargs(char input[], char* cmdargs[]) {
    flush_args(cmdargs);
    char* delimiters = " \t\n\v\f\r";
    char* word = strtok(input, delimiters);
    int i = 0;
    while(word != NULL) {
        size_t argsize = strlen(word) + 1;
        cmdargs[i] = calloc(argsize, sizeof(*cmdargs[i]));
        strncpy(cmdargs[i], word, argsize);
        word = strtok(NULL, delimiters);
        i++;
    }
}

void flush_args(char* cmdargs[]) {
    for (int i = 0; i < MAX_ARGS; i++) {
        if (cmdargs[i] != NULL) {
            free(cmdargs[i]);
            cmdargs[i] = NULL;
        }
    }
}

void free_cmdargs(char* cmdargs[]) {
    flush_args(cmdargs);
    free(cmdargs);
    cmdargs = NULL;
}
