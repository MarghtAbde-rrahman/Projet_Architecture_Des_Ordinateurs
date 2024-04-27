#ifndef DEF_MACHINE
#define DEF_MACHINE


/*-------------------------------Structures-----------------------------------*/
typedef struct{
    int SP;
    int PC;
    int tableau_pile[5000];
}Machine;

/*-------------------------------Fonctions------------------------------------*/
int nombre_ligne_fichier_hexa(char*);
int recuperation_instruction_donnee_fichier_hexa(char*,int*,int*);
void initialisation_pile(Machine*);
void AfficherPile(const Machine*);
void push(Machine*,int);
void push_constante(Machine*, int);
void ipush(Machine*);
void pop(Machine*,int);
void ipop(Machine*);
void dup(Machine*);
void op(Machine*,int);
void jump(Machine*,int);
void jpz(Machine*,int);
void rnd(Machine*,int);
void read(Machine*,int);
void write(Machine*,int);
void call(Machine*,int);
void ret(Machine*);
void execution_principale(Machine*,int*,int*,int);

#endif
