#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "../transformations/modification.h"
#include "cmdprocessing.h"
#include "cmdargs.h"





/* Vérifie si str est un nom de fichier
 * Return : 1 si oui, 0 sinon
 */
int is_filename(char* str) {
    FILE* filedescriptor = fopen(str, "r");
    if (filedescriptor == NULL) {
        return 0;
    }
    fclose(filedescriptor);
    return 1;
}

/* Vérifie si str est un nom de fichier
 * Affiche un message d'erreur et retourne 0 si ce n'est pas le cas
 * Retourn 1 sinon
 */
int verify_filename(char* str) {
    if (!is_filename(str)) {
        fprintf(stderr, "Fichier inexistant\n");
        return 0;
    }
    return 1;
}


void get_command_interactive_mode(char input[])
{
    fgets(input, MAX_INPUT_LENGTH, stdin);
}

void get_command_script_mode(char input[], FILE* filename)
{
    fgets(input, MAX_INPUT_LENGTH, filename);
     while (input[0] == SCRIPT_COMMENT_SYMBOL)
   {
               fgets(input, MAX_INPUT_LENGTH, filename);
    }

}


int check_arguments(int argc, char** argv)
{

    /* Vérification des arguments en cli entrés pour exécuter le programme */
    /* Lancement du traitement de la commande ou du script si les arguments sont corrects*/

    int has_arg_error = 0;
    if (argc == 2)
    {
        if(strncmp(argv[1], "-i", 3) == 0)
        {
            is_script_mode = 0;
            script_fd = NULL;
            process_command();
        }
        else
        {
            has_arg_error = 1;
        }
    }
    else if (argc == 3)
    {
        if (strncmp(argv[1], "-s", 3) == 0)
        {
            FILE* fd = fopen(argv[2], "r");
            if (fd != NULL)
            {

                is_script_mode = 1;
                script_fd = fd;
                process_command();
                fclose(script_fd);
            }
            else
            {
                fprintf(stderr, "Fichier inexistant\n");
                return EXIT_FAILURE;
            }
        }
        else
        {
            has_arg_error = 1;
        }
    }
    else
    {
        has_arg_error = 1;
    }
    if (has_arg_error)
    {
        fprintf(stderr, "Usage: -i ou -s <scriptfile>\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


void process_command(){


    char input[MAX_INPUT_LENGTH];
    char** cmdargs = new_cmdargs();
   // structure.imagedata = init_image_data();

     while (1) {
        /* Récupération de la commande à traiter */
         if (!is_script_mode)
         {
             get_command_interactive_mode(input);
         }
         else
         {
             get_command_script_mode(input, script_fd);

         }

        fill_cmdargs(input, cmdargs);

 if (strcmp(cmdargs[0], "edit") == 0  && strcmp(cmdargs[1], "-all") == 0 ) {
    traitement_lot(structure.imagedata);
    continue;

        }

 if (strcmp(cmdargs[0], "load") == 0 && cmdargs[1] != 0)
        {
            if ((strcmp(cmdargs[1], "image1") == 0) || (strcmp(cmdargs[1], "image2") == 0) || (strcmp(cmdargs[1], "image3") == 0))
            {
                int num_image = cmdargs[1][5]-48;
                int index = num_image - 1;
                if (!verify_filename(cmdargs[2]))
                {
                    continue;
                } //structure.imagedata = init_image_data();
                //SDL_Surface *newOne;
                structure.imagedata[index] = load_image(cmdargs[2], structure.imagedata[index]);
                structure.originalPic[index] = load_image(cmdargs[2], structure.originalPic[index]);
                continue;
            }
        }



    /******* PARTIE SAUVEGARDE ********/


 else if ((strcmp(cmdargs[0], "save") == 0) && cmdargs[1] != 0 && cmdargs[2] != 0)
        {
            char *delimiter = ".";
            char *filename = strtok(cmdargs[2], delimiter);
            char *format = strtok(NULL, delimiter);
            sprintf(filename, "%s.%s", filename, format);
            if (strcmp(format, "jpg") == 0 || strcmp(format, "jpeg") == 0)
            {
                if ((strcmp(cmdargs[1], "image1") == 0) || (strcmp(cmdargs[1], "image2") == 0) || (strcmp(cmdargs[1], "image3") == 0))
                {
                    int num_image = cmdargs[1][5] - 48;
                    int index = num_image - 1;
                    if (structure.imagedata[index] != NULL)
                    {
                        TO_JPG(structure.imagedata[index], cmdargs[2]);
                        continue;
                    }
                }
                else
                {
                    printf("veuillez charger une image d'abord.\n");
                }
            }
            if (strcmp(format, "png") == 0)
            {
                if ((strcmp(cmdargs[1], "image1") == 0) || (strcmp(cmdargs[1], "image2") == 0) || (strcmp(cmdargs[1], "image3") == 0))
                {
                    int num_image = cmdargs[1][5] - 48;
                    int index = num_image - 1;
                    if (structure.imagedata[index] != NULL)
                    {
                        TO_PNG(structure.imagedata[index], cmdargs[2]);
                        continue;
                    }
                }
                else
                {
                    printf("veuillez charger une image d'abord.\n");
                }
            }
            else if (strcmp(format, "bmp") == 0)
            {
                if ((strcmp(cmdargs[1], "image1") == 0) || (strcmp(cmdargs[1], "image2") == 0) || (strcmp(cmdargs[1], "image3") == 0))
                {
                    int num_image = cmdargs[1][5] - 48;
                    int index = num_image - 1;
                    if (structure.imagedata[index] != NULL)
                    {
                        TO_BMP(structure.imagedata[index], cmdargs[2]);
                        continue;
                    }
                }
                else
                {
                    printf("veuillez charger une image d'abord.\n");
                }
            }
            else
            {
                printf("Veuillez choisir un format jpg, png ou bmp\n");
            }
        }


else if (strcmp(cmdargs[0], "edit") == 0 && (cmdargs[1] != 0)){
            if ((strcmp(cmdargs[1], "image1") == 0) || (strcmp(cmdargs[1], "image2") == 0) || (strcmp(cmdargs[1], "image3") == 0))
            {
                int num_image = cmdargs[1][5] - 48;
                int index = num_image - 1;
                edit_image(structure.imagedata[index], structure.originalPic[index], structure.texture[index]);
                continue;
            }
        }

 else if (strcmp(cmdargs[0], "view") == 0 && cmdargs[1] != 0)
        {
            if ((strcmp(cmdargs[1], "image1") == 0) || (strcmp(cmdargs[1], "image2") == 0) || (strcmp(cmdargs[1], "image3") == 0))
            {
                int num_image = cmdargs[1][5] - 48;
                int index = num_image - 1;
                if (structure.imagedata[index] == NULL)
                {
                    printf("Veuillez charger d'abord une image!\n");
                }
                else
                {
                    view_one(structure.imagedata[index]);
                }
                continue;
            }
            else if (strcmp(cmdargs[1], "-all") == 0)
            {
                view_all(structure.imagedata);
                continue;
            }
        }

      else if (strcmp(cmdargs[0], "exit") == 0 &&  cmdargs[1]==0) {
      break;
    }
    else if (memcmp(cmdargs[0], "help", 5) == 0) {
        print_help();
    }
    else {
        printf("Commande inconnue :(\n");
    }


    }


   free_cmdargs(cmdargs);
   free_image_data(structure.imagedata);


}





/******* Fonction pour les commandes d'edition d'image  *************/



 int commande;
 int commandeSelection;
 Uint8 threshold;
 long int R,G,B;
 Uint8 R1,G1,B1;
 int valeurN;
 int h_commande, w_commande;

int edit_command(){



char** cmdargs = new_cmdargs();
char buf[MAX_INPUT_LENGTH];
printf("Vous etes maintenant dans le mode view & edit! \n");

//int quit=0;

while (1){

 /* Récupération de la commande à traiter */
         if (!is_script_mode)
         {
             get_command_interactive_mode(buf);
         }
         else
         {
            get_command_script_mode(buf, script_fd);
         }


fill_cmdargs(buf, cmdargs);


if((strcmp(cmdargs[0],"remplissage")==0) && cmdargs[1]!=0 && (strcmp(cmdargs[1],"-all")==0) &&  cmdargs[2]!=0 && cmdargs[3]!=0 && cmdargs[4]!=0){


R=atol(cmdargs[2]);
G=atol(cmdargs[3]);
B=atol(cmdargs[4]);

//color=cmdargs[2];
commande=4;

continue;

}

if((strcmp(cmdargs[0],"remplissage")==0) && cmdargs[1]!=0 && (strcmp(cmdargs[1],"-selection")==0) && cmdargs[2]!=0 &&
   cmdargs[3]!=0 && cmdargs[4]!=0
   ){

        if(commandeSelection==11){
            commande=10;
            R=atol(cmdargs[2]);
            G=atol(cmdargs[3]);
            B=atol(cmdargs[4]);
            }

        else{
                   printf("Veuillez selectionner une region pour la modifier.\n");
            }
continue;
}


/********* NEGATIF *********/

if(strcmp(cmdargs[0],"negatif")==0){


     if(cmdargs[1]==0){

        commande=5;
        commandeSelection=0;
        continue;
     }

     if((cmdargs[1]!=0) && commandeSelection==11 && (strcmp(cmdargs[1],"-selection")==0)){

            commande=16;
            commandeSelection=0;

     }
     else {

      printf("Veuillez selectionner une region pour la rendre negatif.\n");

}
 continue;

}



if((strcmp(cmdargs[0],"floutage")==0)){

commande=15;
continue;

}
/********* NIVEAUX DE GRIS ***********/

if((strcmp(cmdargs[0],"gris")==0)){

 if((cmdargs[1]==0)){
            commande=12;
            commandeSelection=0;
continue;
}

if((cmdargs[1]!=0) && commandeSelection==11 && (strcmp(cmdargs[1],"-selection")==0)){
         // printf(cmdargs[0]);
            commande=17;

continue;
}
else {

    printf("Veuillez selectionner une région pour la rendre grise.\n");
    continue;
}

}


if(strcmp(cmdargs[0],"contrast")==0){


if(cmdargs[1]!=0 && cmdargs[2]==0 ){

valeurN=atoi(cmdargs[1]);
commande=8;
continue;

}

if(cmdargs[1]!=0 && strcmp(cmdargs[2],"-selection")==0){

valeurN=atoi(cmdargs[1]);
commande=80;
continue;

}


}




if(strcmp(cmdargs[0],"selection")==0){

           if(cmdargs[1]==0){
            commandeSelection=11;
            continue;
            }

            if (strcmp(cmdargs[1], "pixel") == 0 && cmdargs[2]!=0 && cmdargs[3]!=0 && cmdargs[4]!=0 && cmdargs[5]!=0){

            commande=27;

             threshold = (Uint8) strtol(cmdargs[2], NULL, 10);
            R1=(Uint8)atol(cmdargs[3]);
            G1=(Uint8)atol(cmdargs[4]);
            B1=(Uint8)atol(cmdargs[5]);


continue;
}



}


if((strcmp(cmdargs[0],"selection1")==0) && (cmdargs[1]==0)){
         // printf(cmdargs[0]);
            commande=19;
            commandeSelection=11;
continue;

}
if(strcmp(cmdargs[0],"selection2")==0){

        if(cmdargs[1]==0){
            commande=20;
            commandeSelection=0;
}

if((cmdargs[1]!=0) && strcmp(cmdargs[1],"autre_image")==0){

    commande=31;
    commandeSelection=0;
}


continue;

}


if((strcmp(cmdargs[0],"view")==0)){


         if(cmdargs[1]!=0 && strcmp(cmdargs[1],"image2")==0){

                commande=29;
                continue;
         }
         if(cmdargs[1]!=0 && strcmp(cmdargs[1],"image1")==0){

                commande=45;
                continue;
         }
         if(cmdargs[1]!=0 && strcmp(cmdargs[1],"image3")==0){

                commande=46;
                continue;
         }

}

if((strcmp(cmdargs[0],"copier")==0)){

if(cmdargs[1]==0){
  commande=21;
  commandeSelection=0;
  continue;
  }

else if (strcmp(cmdargs[1], "destination") == 0)
            {
                if (strcmp(cmdargs[2], "image2") == 0)
                {
                    commande = 32;
                    continue;
                }
                else if (strcmp(cmdargs[2], "image1") == 0)
                {
                    commande = 48;
                    continue;
                }
                else if (strcmp(cmdargs[2], "image3") == 0)
                {
                    commande = 49;
                    continue;
                }
            }

}

if((strcmp(cmdargs[0],"couper")==0)){


if(cmdargs[1]==0){

  commande=28;
  commandeSelection=0;
  continue;
  }

   if(strcmp(cmdargs[1],"destination")==0 && strcmp(cmdargs[2],"image2")==0 ){
    commande=33;
    continue;
  }
   if(strcmp(cmdargs[1],"destination")==0 && strcmp(cmdargs[2],"image3")==0 ){
    commande=50;
    continue;
  }
  if(strcmp(cmdargs[1],"destination")==0 && strcmp(cmdargs[2],"image1")==0 ){
    commande=51;
    continue;
  }

}



if((strcmp(cmdargs[0],"resize")==0) && cmdargs[1]!=0 && cmdargs[2]!=0 ){

        w_commande=atoi(cmdargs[1]);
        h_commande=atoi(cmdargs[2]);

        commande=23;
        continue;

}

if((strcmp(cmdargs[0],"rotation")==0) && (strcmp(cmdargs[1],"90")==0)){
        commande=34;
        continue;

}

if((strcmp(cmdargs[0],"rotation")==0) && (strcmp(cmdargs[1],"180")==0)){
        commande=35;
        continue;

}

if((strcmp(cmdargs[0],"rotation")==0) && (strcmp(cmdargs[1],"270")==0)){
        commande=36;
        continue;

}
/** A FAIRE
if((strcmp(cmdargs[0],"copier")==0) && (cmdargs[1]!=0) && (cmdargs[2]!=0) && (strcmp(cmdargs[1],"destination")==0) && (strcmp(cmdargs[1],"image2")==0)){

continue;

}
**/

if(strcmp(cmdargs[0],"blackwhite")==0 && cmdargs[1]==0){

            commande = 60;

continue;
}

if(strcmp(cmdargs[0],"blackwhite")==0 && strcmp(cmdargs[1],"-selection")==0){

            commande = 61;

continue;
}


if(strcmp(cmdargs[0],"clear")==0){

    if((cmdargs[1]!=0) && (strcmp(cmdargs[1],"-selection")==0)){

            commande=18;
            commandeSelection=0;
    }
    if((cmdargs[1]!=0) && (strcmp(cmdargs[1],"-all")==0)){

            commande=22;
            commandeSelection=0;

    }
 continue;
}



/****** RECADRAGE ********/

if((strcmp(cmdargs[0],"recadrage")==0) && (strcmp(cmdargs[1],"-selection")==0)){
            commande=13;
continue;
}

if((strcmp(cmdargs[0],"save")==0) && (strcmp(cmdargs[1],"recadrage")==0) && cmdargs[2]!=0){

       if(structure.secondSurface==NULL){

        printf("Veuillez recadrez d'abord!\n");
         continue;
       }

else{
        char* delimiter = ".";
        char* filename = strtok(cmdargs[2], delimiter);
        char* format = strtok(NULL, delimiter);

        sprintf(filename, "%s.%s", filename, format);


        if (strcmp(format, "jpg") == 0 || strcmp(format, "jpeg") == 0) {

                   TO_JPG(structure.secondSurface,cmdargs[2]);
         continue;
                }
        if (strcmp(format, "png") == 0) {

                   TO_PNG(structure.secondSurface,cmdargs[2]);
         continue;
                }
        if (strcmp(format, "bmp") == 0) {

                   TO_BMP(structure.secondSurface,cmdargs[2]);
         continue;
                }
}
           }



if((strcmp(cmdargs[0],"recadrage")==0) && cmdargs[1]!=0 && (strcmp(cmdargs[1],"-marge")==0)){

        if(commandeSelection!=11){

            printf("Veuillez selectionner une region pour la modifier.\n");
            continue;
        }
commande=26;

continue;
}



if((strcmp(cmdargs[0],"symetrie")==0) && cmdargs[1]!=0 && (strcmp(cmdargs[1],"horizontale")==0)){
commande=24;

continue;
}
if((strcmp(cmdargs[0],"symetrie")==0) && cmdargs[1]!=0 && (strcmp(cmdargs[1],"verticale")==0)){
commande=25;

continue;
}





if(strcmp(buf,"click")==0){
            commande=1;

}

/********* LUMINOSITE ***********/

if((strcmp(cmdargs[0],"luminosite")==0) && cmdargs[1]!=0){
         // printf(cmdargs[0]);


if((cmdargs[2]==0)){
commande=7;
commandeSelection=0;
valeurN=atoi(cmdargs[1]);
continue;

    }

if(strcmp(cmdargs[2],"-selection")==0 && commandeSelection==11 ){
         // printf(cmdargs[0]);


commande=6;
valeurN=atoi(cmdargs[1]);
continue;

}

else {

    printf("Veuillez selectionner une region pour la modifier.\n");
    continue;
}


}


/**
if(strcmp(buf,"new")==0){
newWindow();

              continue;

}**/

if(strcmp(cmdargs[0],"help")==0){
     print_help_edit();

}



else if(strcmp(cmdargs[0],"exit")==0 && strcmp(cmdargs[1],"edit")==0){
     commande=101;
        break;

}


else {
        printf("Commande inconnue!\n");
    }


}

printf("sortie de edit \n");
commande=0;
return 0;

}





int edit_command_lot(){



char** cmdargs = new_cmdargs();
char buf[128];
printf("Vous etes maintenant dans le mode edit! \n");

//int quit=0;

while (1){




fgets(buf, 128, stdin);
fill_cmdargs(buf, cmdargs);



if(strcmp(cmdargs[0],"gris")==0 && cmdargs[1]!=0 && strcmp(cmdargs[1],"-all")==0){

    commande=12;

 continue;

}


if(strcmp(cmdargs[0],"negatif")==0 && strcmp(cmdargs[1],"-all")==0){

        commande=5;
        continue;
}
if((strcmp(cmdargs[0],"remplissage")==0) && cmdargs[1]!=0 && (strcmp(cmdargs[1],"-all")==0) &&  cmdargs[2]!=0 && cmdargs[3]!=0 && cmdargs[4]!=0){


R=atol(cmdargs[2]);
G=atol(cmdargs[3]);
B=atol(cmdargs[4]);


commande=6;

continue;

}

if(strcmp(cmdargs[0],"noirblanc")==0 && strcmp(cmdargs[1],"-all")==0){


commande=7;

continue;

}

if(strcmp(cmdargs[0],"symetrie")==0 && strcmp(cmdargs[1],"verticale")==0){


commande=8;

continue;

}

if(strcmp(cmdargs[0],"symetrie")==0 && strcmp(cmdargs[1],"horizontale")==0){


commande=9;

continue;

}
else if(strcmp(cmdargs[0],"exit")==0 && strcmp(cmdargs[1],"edit")==0){

        break;

}

else {
        printf("Commande inconnue!\n");
    }


}

return 0;

}






/** A remplir encore **/
void print_help() {
    printf("Voici la liste des commandes de CIMP et leur description succinte :\n");
    printf("Attention a ne pas ecrire les <> dans une commande\n");
    printf(">  load image1 <nom de l'image> : charge une 1ere image \n");
    printf(">  load image2 <nom de l'image> : charge une 2eme image\n");
    printf(">  load image3 <nom de l'image> : charge une 3eme image\n");
    printf(">  save <nom du fichier initial> <nom du fichier final> : sauvegarde une image\n");
    printf(">  view image1 : permet de visualiser la 1ere image\n");
    printf(">  view image2 : permet de visualiser la 2eme image\n");
    printf(">  view image3 : permet de visualiser la 3eme image\n");
    printf(">  view -all   : permet de visualiser toutes les images\n");
    printf(">  edit image1 : permet d'entrer dans le mode edit pour editer la 1ere image\n");
    printf(">  edit image2 : permet d'entrer dans le mode edit pour editer la 2eme image\n");
    printf(">  edit image3 : permet d'entrer dans le mode edit pour editer la 3eme image\n");

}


/** A remplir encore**/
/** affiche les commandes dans le mode edit **/
void print_help_edit(){

    printf("Commandes du mode edit\n");
    printf("\n");
    printf(">  POUR QUITTER LE MODE EDIT :\n");
    printf(">  fermer la fenetre :\n");
    printf(">  taper exit edit :\n");
    printf("-------------------------------\n");
    printf(">  clear -all  : supprime toutes les modifications faites\n");
    printf(">  selection   : permet d'avoir une selection rectangulaire dans l'image\n");
    printf("\n");
    printf(">  POUR COPIER/COUPER UNE PARTIE DE L'IMAGE \n");
    printf(">  selection1   : pour avoir la 1ere selection\n");
    printf(">  selection2   : pour avoir la 2eme selection\n");
    printf(">  copier   : copier dans la meme image\n");
    printf(">  couper   : couper dans la meme image\n");
    printf("\n");
    printf(">  gris        : mise en niveaux de gris sur toute l'image\n");
    printf(">  gris -selection : mise en niveaux de gris sur une selection rectangulaire\n");
    printf(">  negatif   : mise en negatif sur toute l'image\n");
    printf(">  negatif -selection : mise en negatif sur une selection rectangulaire\n");
    printf(">  symetrie horizontale \n");
    printf(">  symetrie verticale \n");





}

