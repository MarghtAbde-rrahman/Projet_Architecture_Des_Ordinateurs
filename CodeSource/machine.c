#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"machine.h"


#define nombre_caractere_max_ligne 1000

/*--------------------------------Fonctions--------------------------------------*/

int nombre_ligne_fichier_hexa(char* nom_fichier){
/*--------Renvoie le nombre de fois où on trouve dans un certain fichier le caractère saut de ligne--------*/
/* ----------------Attention ne renvoie pas le nombre de ligne visible par l'utilisateur-------------------*/
/*Renvoie le nombre de fois où on a appuyer sur entrée pour sauter une ligne lors de la création du fichier*/
/*------------On verifiera si le fichier est bien ouvert--------------*/
/*Si problème d'ouverture, la fonction va renvoyer -1 pour le signaler*/
FILE* fichier=NULL;
fichier=fopen(nom_fichier,"r");
int cpt=0; /*Pour compter le nombre de ligne*/
char caractere_courant; /*Pour stocker le caractère qu'on est en train de lire*/
if(fichier!=NULL){
    while( (caractere_courant=fgetc(fichier) ) != EOF ){
        if(caractere_courant == '\n'){
        cpt++;
            }
        }
    }
else{
printf("Erreur Ouverture fichier.");
cpt=-2;
}
fclose(fichier);
return cpt;
}

int recuperation_instruction_donnee_fichier_hexa(char* nom_fichier,int* instruction_courante,int* donnee_courante){
    FILE* fichier=NULL;
    fichier= fopen(nom_fichier,"r");
    int n=nombre_ligne_fichier_hexa(nom_fichier);
    if(fichier!=NULL){
        for(int i=0;i<n;i++){   //on parcourt toutes les lignes
        fscanf(fichier,"%x %x",&instruction_courante[i],&donnee_courante[i]);
        }
        fclose(fichier);
        return 0;
    }
    else{
        fclose(fichier);
        return -1; //ouverture fichier impossible
    }
}

void initialisation_pile(Machine* m){
    m->PC=0;
    m->SP=0;
    for(int j=0;j<5000;j++){
        m->tableau_pile[j]=0; //On met a 0 par defaut.
    }
}

void AfficherPile(const Machine* m){
    int i=0;
    printf("PC: %d\nSP: %d\n",m->PC,m->SP);
    while (i<=(m->SP)){
        printf("Tableau_pile[%d]=%d\n",i,m->tableau_pile[i]);
        i++;
    }
}

void push(Machine* m,int x){
    m->tableau_pile[m->SP]=(m->tableau_pile)[x];
    m->SP++;
}

void push_constante(Machine* m, int entier){
    m->tableau_pile[m->SP]=entier;
    m->SP++;
}

void ipush(Machine* m){
    int n=m->tableau_pile[(m->SP)-1];
    m->tableau_pile[(m->SP)-1]=m->tableau_pile[n];
}

void pop(Machine* m,int x){
    (m->SP)--;
    (m->tableau_pile[x])=(m->tableau_pile[m->SP]);
}

void ipop(Machine* m){
    int n=m->tableau_pile[(m->SP)-1];
    m->tableau_pile[n]=m->tableau_pile[(m->SP)-2];
    m->SP-=2;
}

void dup(Machine* m){
    m->tableau_pile[m->SP]=m->tableau_pile[(m->SP)-1];
    m->SP++;
}

void op(Machine* m,int i){
    if (i<0 || i>15) return;
    else{
        if(i==0){
            m->SP--;
            m->tableau_pile[(m->SP)-1]+=m->tableau_pile[m->SP];
        }
        if(i==1){
            m->SP--;
            m->tableau_pile[(m->SP)-1]-=m->tableau_pile[m->SP];
        }
        if(i==2){
            m->SP--;
            m->tableau_pile[(m->SP)-1]*=m->tableau_pile[m->SP];
        }
        if(i==3){
            m->SP--;
            m->tableau_pile[(m->SP)-1]/=m->tableau_pile[m->SP];
        }
        if(i==4){
            m->SP--;
            m->tableau_pile[(m->SP)-1]%=m->tableau_pile[m->SP];
        }
        if(i==5){
            m->tableau_pile[(m->SP)-1]=-1*(m->tableau_pile[(m->SP)-1]);
        }
        if(i==6){
            m->SP--;
            if((m->tableau_pile[(m->SP)-1])==(m->tableau_pile[m->SP])){
                m->tableau_pile[(m->SP)-1]=0;
            }
            else{
                m->tableau_pile[(m->SP)-1]=1;
            }
        }
        if(i==7){
            m->SP--;
            if((m->tableau_pile[(m->SP)-1])!=(m->tableau_pile[m->SP])){
                m->tableau_pile[(m->SP)-1]=0;
            }
            else{
                m->tableau_pile[(m->SP)-1]=1;
            }
        }
        if(i==8){
            m->SP--;
            if((m->tableau_pile[(m->SP)-1])>(m->tableau_pile[m->SP])){
                m->tableau_pile[(m->SP)-1]=0;
            }
            else{
                m->tableau_pile[(m->SP)-1]=1;
            }
        }
        if(i==9){
            m->SP--;
            if((m->tableau_pile[(m->SP)-1])>=(m->tableau_pile[m->SP])){
                m->tableau_pile[(m->SP)-1]=0;
            }
            else{
                m->tableau_pile[(m->SP)-1]=1;
            }
        }
        if(i==10){
            m->SP--;
            if((m->tableau_pile[(m->SP)-1])<(m->tableau_pile[m->SP])){
                m->tableau_pile[(m->SP)-1]=0;
            }
            else{
                m->tableau_pile[(m->SP)-1]=1;
            }
        }
        if(i==11){
            m->SP--;
            if((m->tableau_pile[(m->SP)-1])<=(m->tableau_pile[m->SP])){
                m->tableau_pile[(m->SP)-1]=0;
            }
            else{
                m->tableau_pile[(m->SP)-1]=1;
            }
        }
        if(i==12){
            m->SP--;
            m->tableau_pile[(m->SP)-1]&=m->tableau_pile[m->SP];
        }
        if(i==13){
            m->SP--;
            m->tableau_pile[(m->SP)-1]|=m->tableau_pile[m->SP];
        }
        if(i==14){
            m->SP--;
            m->tableau_pile[(m->SP)-1]^=m->tableau_pile[m->SP];
        }
        if(i==15){
            m->tableau_pile[(m->SP)-1]=~m->tableau_pile[(m->SP)-1];
        }
    }
}

void jump(Machine* m,int Adr){
    (m->PC)+=Adr;
}

void jpz(Machine* m,int Adr){
    m->SP--;
    int x=m->tableau_pile[(m->SP)]; //element au sommet de la pile
    if(x==0){
        (m->PC)+=Adr;
    }
}

void rnd(Machine* m,int x){
    int random=rand()%x;  //random est un entier entre 0 et x-1
    m->tableau_pile[m->SP]=random;
    m->SP++;
}

void read(Machine* m,int x){
    printf("Entrer une valeur svp : ");
    //printf("Valeur a rentrer a l'adresse %d: ",x);
    scanf("%d",&(m->tableau_pile[x]));
}

void write(Machine* m,int x){
  printf("%d\n",m->tableau_pile[x]);
  //printf("Valeur de la variable a l'adresse %d: %d\n",x,m->tableau_pile[x]);
}

void call(Machine* m,int Adr){
    push_constante(m,(m->PC));
    m->PC+=Adr;
}

void ret(Machine* m){
    m->SP=(m->SP)-1;
}

void execution_principale(Machine* m,int* instruction_courante,int* donnee_courante,int nombre_ligne){

  while((m->PC)<nombre_ligne){
      if(instruction_courante[m->PC]==0){
          (m->PC)++;
          push(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==1){
          (m->PC)++;
          push_constante(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==2){
          (m->PC)++;
          ipush(m);
          continue;
      }
      if(instruction_courante[m->PC]==3){
          (m->PC)++;
          pop(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==4){
          (m->PC)++;
          ipop(m);
          continue;
      }
      if(instruction_courante[m->PC]==5){
        (m->PC)++;
        dup(m);
        continue;
      }
      if(instruction_courante[m->PC]==6){
          (m->PC)++;
          op(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==7){
          (m->PC)++;
          jump(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==8){
          (m->PC)++;
          jpz(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==9){
          (m->PC)++;
          rnd(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==10){
          (m->PC)++;
          read(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==11){
          (m->PC)++;
          write(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==12){
          (m->PC)++;
          call(m,donnee_courante[(m->PC)-1]);
          continue;
      }
      if(instruction_courante[m->PC]==13){
          (m->PC)++;
          ret(m);
          continue;
      }
      if(instruction_courante[m->PC]==14){
          break;
      }
  }
}
