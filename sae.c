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

void initialiserCentre(CentreMedical *centre){
    centre->nbSpecialites = 0;
}


void ajouterPraticien(CentreMedical *centre){
    char nomSpe[50], nomDr[50];
    int capaMax;

    if (centre->nbSpecialites >= MAX_SPECIALITES) {
        printf("Erreur : Le centre a atteint son nombre maximal de spécialités.\n"); [cite: 25]
        return;
    }

    printf("Nom de la spécialité : ");
    scanf("%s", nomSpe);
    printf("Nom du praticien : ");
    scanf("%s", nomDr);
    printf("Capacité maximale de sa patientèle : "); [cite: 29]
    scanf("%d", &capaMax);

    // 1. Chercher si la spécialité _existe déjà
    int idxSpe = -1;
    for(int i = 0; i < centre->nbSpecialites; i++){
        if (strcmp(centre->tSpecialites[i].nomSpecialite, nomSpe) == 0){
            idxSpe = i;
            break;
        }
    }
    // 2. Si elle n'existe pas, on la crée
    if (idxSpe == -1) {
        idxSpe = centre->nbSpecialites;
        strcpy(centre->tSpecialites[idxSpe].nomSpecialite, nomSpe);
        centre->tSpecialites[idxSpe].listePraticiens = NULL;
        centre->tSpecialites[idxSpe].nbPraticiens = 0;
        centre->nbSpecialites++;
    }
    // 3. Créer le nouveau(tmp) maillon praticien (Liste chaînée)
    MaillonPraticien *tmp = (MaillonPraticien*)malloc(sizeof(MaillonPraticien));
    if (tmp == NULL) exit(1);

    strcpy(tmp->donnee.nom, nomDr);
    tmp->donnee.salleAttente = filenouv();

    // Initialisation de la patientèle (Tableau dynamique)
    tmp->donnee.maPatientele.nbPatients = 0;
    tmp->donnee.maPatientele.capaciteMax = capaMax;
    tmp->donnee.maPatientele.listePatients = (Patient*)malloc(capaMax * sizeof(Patient));

    // 4. Ajout en tête de la liste des praticiens de la spécialité [cite: 26, 27]
    tmp->suivant = centre->tSpecialites[idxSpe].listePraticiens;
    centre->tSpecialites[idxSpe].listePraticiens = tmp;
    centre->tSpecialites[idxSpe].nbPraticiens++;

    printf("Praticien ajouté avec succès.\n");
}



void supprimerPraticien(CentreMedical *centre) {
    char nomSpe[50], nomDr[50];
    
    printf("Spécialité du praticien : ");
    scanf("%s", nomSpe);
    
    int idxSpe = trouverSpecialite(centre, nomSpe); // On réutilise la fonction de recherche
    if (idxSpe == -1) {
        printf("Spécialité introuvable.\n");
        return;
    }

    printf("Nom du praticien à supprimer : ");
    scanf("%s", nomDr);

    MaillonPraticien *courant = centre->tSpecialites[idxSpe].listePraticiens;
    MaillonPraticien *precedent = NULL;

    while (courant != NULL) {
        if (strcmp(courant->donnee.nom, nomDr) == 0) {
            // 1. Gérer le chaînage pour ne pas casser la liste
            if (precedent == NULL) {
                // C'est le premier de la liste
                centre->tSpecialites[idxSpe].listePraticiens = courant->suivant;
            } else {
                // Il est au milieu ou à la fin
                precedent->suivant = courant->suivant;
            }

            // 2. Libérer la mémoire spécifique (Important pour la note !)
            // On libère le tableau dynamique des patients
            free(courant->donnee.maPatientele.listePatients); 
            
            // On devrait aussi vider la file d'attente si elle n'est pas vide
            while(!estVide(courant->donnee.salleAttente)) {
                courant->donnee.salleAttente = supt(courant->donnee.salleAttente);
            }

            // 3. Libérer le maillon lui-même
            free(courant);
            
            centre->tSpecialites[idxSpe].nbPraticiens--;
            printf("Le praticien %s a été supprimé avec succès.\n", nomDr);
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }

    printf("Praticien %s non trouvé dans la spécialité %s.\n", nomDr, nomSpe);
}

void afficherPraticiensParSpecialite(CentreMedical *centre, char nom_specialite[]) {
    int i;
    MaillonPraticien *p;

    for (i = 0; i < centre->nbSpecialites; i++) {
        if (strcmp(centre->tSpecialites[i].nomSpecialite, nom_specialite) == 0) {

            p = centre->tSpecialites[i].listePraticiens;
            while (p != NULL) {
                printf("%s\n", p->donnee.nom);
                p = p->suivant;
            }
            return;
        }
    }
}

int rechercherSpecialite(CentreMedical *centre, char nom_specialite[]) {
    int i;

    for (i = 0; i < centre->nbSpecialites; i++) {
        if (strcmp(centre->tSpecialites[i].nomSpecialite, nom_specialite) == 0) {
            return i;
        }
    }
    return -1;
}

int ajouterSpecialite(CentreMedical *centre, char nom_specialite[]) {

    if (centre->nbSpecialites >= MAX_SPECIALITES) {
        return 0;
    }

    if (rechercherSpecialite(centre, nom_specialite) != -1) {
        return 0;
    }

    strcpy(centre->tSpecialites[centre->nbSpecialites].nomSpecialite, nom_specialite);
    centre->tSpecialites[centre->nbSpecialites].listePraticiens = NULL;
    centre->tSpecialites[centre->nbSpecialites].nbPraticiens = 0;

    centre->nbSpecialites++;
    return 1;
}