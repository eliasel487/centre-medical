#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sae.h"

File filenouv(void){
    File f;
    f.t=NULL;
    f.q=NULL;
    return f;
}

Booleen estVide(File f){
    return f.t==NULL&&f.q==NULL;
}

File adjq(File f, Patient x){
    Maillon *m;
    m=(Maillon*)malloc(sizeof(Maillon));
    if(m==NULL){
        printf("Pb malloc\n");
        exit(1);
    }
    m->suiv=NULL;
    m->info=x;
    if(estVide(f)){
        f.t=m;
        f.q=m;
        return f;
    }
    f.q->suiv=m;
    f.q=m;
    return f;
}


File supt(File f){
    Maillon *m;
    if(estVide(f)){
        printf("op interdite\n");
        exit(1);
    }
    if(f.t==f.q){
        free(f.t);
        return filenouv();
    }
    m=f.t;
    f.t=f.t->suiv;
    free(m);
    return f;
}

int longueur(File f){
    int l=0;
    while(f.t!=NULL){
        l++;
        f.t=f.t->suiv;
    }
    return l;
}

void afficher(File f){
    while(f.t!=NULL){
        printf("%s ", f.t->info.nom);
        f.t=f.t->suiv;
    }
    printf("\n");
}

Patient tete(File f){
    if(estVide(f)){
        printf("op interdite\n");
        exit(1);
    }
    return f.t->info;
}
