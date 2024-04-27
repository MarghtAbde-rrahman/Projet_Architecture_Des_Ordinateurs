#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"assembleur.h"
#include"machine.h"


int main(int argc,char* argv[]){

  /*Partie Assembleur*/
  int verif=assembleur(argv[1]);
  if(verif==1){
    return 0;
  }


  /*Partie Machine*/
  Machine m;
  Machine* pointeur_m=&m;
  initialisation_pile(pointeur_m);

  int nombre_ligne=nombre_ligne_fichier("hexa.txt");
  if(nombre_ligne==-1){
    printf("Erreur lors de l'ouverture du fichier hexa.txt. Impossible de lancer l'execution de la machine a pile.\n");
  }
  int instruction_courante[nombre_ligne];
  int donnee_courante[nombre_ligne];


  verif=recuperation_instruction_donnee_fichier_hexa("hexa.txt",instruction_courante,donnee_courante);
  if(verif==-1){
    printf("Erreur lors de l'ouverture du fichier hexa.txt. Impossible de lancer l'execution de la machine a pile.\n");
  }

  execution_principale(pointeur_m,instruction_courante,donnee_courante,nombre_ligne);
  printf("\n---------------------------------------------------------------------------------------------------\n");
  printf("Fin execution du code en langage machine.\n");
  return 0;
}
