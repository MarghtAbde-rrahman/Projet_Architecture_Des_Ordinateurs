#ifndef DEF_ASSEMBLEUR

#define DEF_ASSEMBLEUR
int nombre_ligne_fichier(char*);
int verif_fichier_vide(char*);
int actualisation_fichier_code_assembleur(char*);
int recuperation_etiquette(char*,int,char**);
int verif_etiquette(int,char**);
void liberation_espace_memoire_tab_etiquette(int,char**);
int verif_instruction_donnee(char*,int,char**);
int traduction_instruction_octect_poids_fort(char*,int,int*);
int recuperation_donnee(char*,int,int*,char**,int*);
int creation_fichier_langage_machine(int,int*,int*);
int assembleur(char*);

#endif
