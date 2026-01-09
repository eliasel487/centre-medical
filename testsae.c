#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sae.h"

int main(void) {
    CentreMedical monCentre;
    int choix = -1;
    char poubelle[50];
    initialiserCentre(&monCentre);
    chargerCentre(&monCentre, "donnees_centre.txt");

    while (choix != 0) {
        printf("\n==============================\n");
        printf("  CENTRE MEDICAL\n");
        printf("==============================\n");
        printf("1 - Secretaire\n");
        printf("2 - Praticien\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");
        if (scanf("%d", &choix) == 0) {
            scanf("%s", poubelle);
            choix = -1;
        }
        if (choix == 1) {
            menuSecretaire(&monCentre);
        }
        else if (choix == 2) {
            menuPraticien(&monCentre);
        }
        else if (choix == 0) {
            printf("Fermeture du programme.\n");
            sauvegarderCentre(&monCentre, "donnees_centre.txt");
            exit(1);
        }
        else {
            printf("Choix invalide.\n");
            continue;
        }
    }
    return 0;
}

