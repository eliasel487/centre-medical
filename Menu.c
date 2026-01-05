#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sae.h"

void menuSecretaire(CentreMedical *centre) {
    int choix = -1;
    char nomSpe[50];

    while (choix != 0) {
        printf("\n--- MENU SECRETAIRE ---\n");
        printf("1. Ajouter un praticien\n");
        printf("2. Supprimer un praticien\n");
        printf("3. Afficher toutes les specialites (ordre alphabetique)\n");
        printf("4. Afficher les praticiens d'une specialite\n");
        printf("5. Afficher tout le centre (structure complete)\n");
        printf("6. Enregistrer l'arrivee d'un patient\n");
        printf("0. Retour au menu principal\n");
        printf("Choix : ");
        scanf("%d", &choix);

        if (choix == 1) ajouterPraticien(centre); [cite: 12]
        if (choix == 2) supprimerPraticien(centre); [cite: 13]
        if (choix == 3) afficherSpecialites(centre); [cite: 14]
        if (choix == 4) {
            printf("Nom de la specialite : ");
            scanf("%s", nomSpe);
            afficherPraticiensParSpecialite(centre, nomSpe); [cite: 15]
        }
        if (choix == 5) afficherCentre(centre); [cite: 16]
        if (choix == 6) enregistrerArriveePatient(centre); [cite: 17]
    }
}

void menuPraticien(CentreMedical *centre) {
    char nomDr[50], nomSpe[50];
    printf("\nIdentification du Praticien :\n");
    printf("Votre specialite : "); scanf("%s", nomSpe);
    printf("Votre nom : "); scanf("%s", nomDr);

    // Recherche du pointeur vers le praticien pour passer ses donnees aux fonctions
    int idx = rechercherSpecialite(centre, nomSpe);
    if (idx == -1) {
        printf("Specialite inexistante.\n");
        return;
    }

    MaillonPraticien *courant = centre->tSpecialites[idx].listePraticiens;
    Praticien *p = NULL;
    while (courant != NULL) {
        if (strcmp(courant->donnee.nom, nomDr) == 0) {
            p = &(courant->donnee);
            break;
        }
        courant = courant->suivant;
    }

    if (p == NULL) {
        printf("Praticien introuvable.\n");
        return;
    }

    int choix = -1;
    while (choix != 0) {
        printf("\n--- ESPACE DR. %s ---\n", p->nom);
        printf("1. Appeler le prochain patient\n");
        printf("2. Afficher la patientele (A-Z)\n");
        printf("3. Afficher la patientele (Par date de visite)\n");
        printf("4. Supprimer un patient precis\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choix);

        if (choix == 1) appelerProchainPatient(p); [cite: 19]
        if (choix == 2) afficherPatienteleAlphabetique(p); [cite: 20]
        if (choix == 3) afficherPatienteleParDate(p); [cite: 21]
        if (choix == 4) {
            // Ici tu appelleras la fonction de suppression de patient
            printf("Fonctionnalite a venir...\n"); [cite: 21, 36]
        }
    }
}

void afficherMenuPrincipal(CentreMedical *centre) {
    int choix = -1;
    while (choix != 0) {
        printf("\n==============================\n");
        printf("   GESTION DU CENTRE MEDICAL\n");
        printf("==============================\n");
        printf("1. Acceder au Menu SECRETAIRE\n");
        printf("2. Acceder au Menu PRATICIEN\n");
        printf("0. Quitter l'application\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) menuSecretaire(centre);
        if (choix == 2) menuPraticien(centre);
        if (choix == 0) {
            sauvegarderCentre(centre, "donnees_centre.dat"); [cite: 23]
            printf("Fichiers enregistres. Au revoir.\n");
        }
    }
}