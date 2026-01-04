#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sae.h"


void global(void){
    File f = filenouv();
    Patient p1 = {"Alice", "123456789012345", {10, 3, 2024}};
    Patient p2 = {"Bob", "987654321098765", {15, 4, 2024}};
    Patient p3 = {"Charly", "111222333444555", {20, 5, 2024}};
    f = adjq(f, p1);
    f = adjq(f, p2);
    f = adjq(f, p3);
    afficher(f);
    printf("Longueur : %d\n", longueur(f));
    Patient p = tete(f);    
    printf("Tete : %s %s\n", p.nom, p.numSecu);
    f = supt(f);
    afficher(f);
    f = supt(f);
    f = supt(f);
    if(estVide(f)){
        printf("File vide\n");
    }
}

int main(void){
    global();
    return 0;
}

