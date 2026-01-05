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

void triParEchange(int tab[], int n){
    int pge;
    while (n>1){
        pge = plusGrand(tab,n);
        echanger(tab,pge,n-1);
        n = n - 1;
    }
}

void echanger(int tab[], int i, int j){
    int aux;
    aux = tab[i];
    tab[i] = tab[j];
    tab[j] = aux;
}

int plusGrand(int tab[], int n){
    int i, pge=0;
    for (i=0;i<n;i++){
        if (tab[i]>tab[pge])
            pge = i;
    }
    return pge;
}

void fusion(int R[], int n, int S[], int m, int T[]){
    int i=0, j=0, k=0;
    while (i<n && j<m){
        if (R[i] <= S[j]){
            T[k] = R[i];
            i++;
            k++;
        }
        else{
            T[k]=S[j];
            j++;
            k++;
        }
    }
    while(i<n){
        T[k]=R[i];
        i++;
        k++;

    }
    while(j<m){
        T[k]=S[j];
        j++;
        k++
    }
}

void copier(int T[], int i, int j, int R[]){
    int k=0;
    while(i<j){
        R[k]=T[i];
        i++;
        k++;
    }
}

void trifusion(int tab[], int m){
    if (n==1)
        return;
    int *R, *S;
    R = (int*)malloc((n/2)*sizeof(int));
    S = (int*)malloc((n-n/2)*sizeof(int));
    if (R == NULL || S == NULL)
        exit(1);
    copier(T,0,n/2,R);
    copier(T,n/2,n,S);
    trifusion(R,n/2);
    trifusionf(S,n-n/2);
    fusion(R,n/2,S,n-n/2,T);
    free(R);
    free(S);
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
    int capacitemax, i;

    if (centre->nbSpecialites >= MAX_SPECIALITES) {
        printf("Le centre a atteint son nombre maximal de spécialités.\n");
        return;
    }

    printf("Nom de la spécialité : ");
    scanf("%s", nomSpe);
    printf("Nom du praticien : ");
    scanf("%s", nomDr);
    printf("Capacité maximale de sa patientèle : ");
    scanf("%d", &capacitemax);

    // 1. Chercher si la spécialité _existe déjà
    int ind = -1;
    for(i=0; i<centre->nbSpecialites; i++){
        if (strcmp(centre->tSpecialites[i].nomSpecialite, nomSpe) == 0){
            ind = i;
            break;
        }
    }
    // 2. Si elle n'existe pas, on la crée
    if (ind == -1) {
        ind = centre->nbSpecialites;
        strcpy(centre->tSpecialites[ind].nomSpecialite, nomSpe);
        centre->tSpecialites[ind].listePraticiens = NULL;
        centre->tSpecialites[ind].nbPraticiens = 0;
        centre->nbSpecialites++;
    }
    // 3. Créer le nouveau(tmp) maillon praticien (Liste chaînée)
    MaillonPraticien *tmp = (MaillonPraticien*)malloc(sizeof(MaillonPraticien));
    if (tmp == NULL) exit(1);

    strcpy(tmp->donnee.nom, nomDr);
    tmp->donnee.salleAttente = filenouv();

    // Initialisation de la patientèle (Tableau dynamique)
    tmp->donnee.maPatientele.nbPatients = 0;
    tmp->donnee.maPatientele.capaciteMax = capacitemax;
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

void afficherSpecialites(CentreMedical *centre) {
    int i;
    if (centre->nbSpecialites == 0) {
        printf("Aucune spécialité n'est enregistrée dans le centre.\n");
        return;
    }
    triParEchangeSpecialites(centre->tSpecialites, centre->nbSpecialites);
    printf("Liste des Spécialités (Ordre Lexicographique)\n");
    for (i=0;i<centre->nbSpecialites;i++) {
        printf("%s\n", centre->tSpecialites[i].nomSpecialite);
    }
}

int praticienPeutPrendrePatient(Praticien *praticien) {
    if (praticien->maPatientele.nbPatients < praticien->maPatientele.capaciteMax) {
        return 1;
    }
    return 0;
}

void ajouterPatientFile(Praticien *praticien, Patient patient) {
    praticien->salleAttente = adjq(praticien->salleAttente, patient);
    printf("Patient ajoute a la file d'attente du Dr %s.\n", praticien->nom);
}

// Retire et retourne le patient en tête de la file d'attente
Patient retirerPatientFile(Praticien *praticien) {
    if (fileVide(praticien)) {
        printf("Erreur : La file d'attente est vide.\n");
        exit(1); 
    }
    Patient p = tete(praticien->salleAttente);
    praticien->salleAttente = supt(praticien->salleAttente);
    return p;
}

// Vérifie si la salle d'attente est vide
int fileVide(Praticien *praticien) {
    if (estVide(praticien->salleAttente) == VRAI) {
        return 1;
    }
    return 0;
}

void appelerProchainPatient(Praticien *praticien) {
    // 1. Vérifier si la salle d'attente est vide
    if (fileVide(praticien)) {
        printf("La salle d'attente est vide.\n");
        return;
    }

    // 2. Récupérer et retirer le patient (FIFO)
    Patient p = retirerPatientFile(praticien);
    printf("\nAppel du patient : %s\n", p.nom [cite: 19]);

    // 3. Chercher si le patient est déjà dans la patientèle
    int trouve = -1;
    for (int i = 0; i < praticien->maPatientele.nbPatients; i++) {
        if (strcmp(praticien->maPatientele.listePatients[i].numSecu, p.numSecu) == 0) {
            trouve = i;
            break;
        }
    }

    if (trouve != -1) {
        // Patient déjà connu : on met à jour sa date [cite: 19]
        printf("Patient deja suivi. Mise a jour de la date de visite.\n");
        printf("Jour de la visite : "); scanf("%d", &praticien->maPatientele.listePatients[trouve].derniereVisite.jour);
        printf("Mois de la visite : "); scanf("%d", &praticien->maPatientele.listePatients[trouve].derniereVisite.mois);
        printf("Annee de la visite : "); scanf("%d", &praticien->maPatientele.listePatients[trouve].derniereVisite.annee);
    } else {
        // Nouveau patient : on vérifie la capacité max [cite: 29, 30]
        if (praticien->maPatientele.nbPatients < praticien->maPatientele.capaciteMax) {
            printf("Nouveau patient. Ajouter a la clientele ? (1:Oui / 0:Non) : ");
            int rep;
            scanf("%d", &rep);
            if (rep == 1) {
                printf("Numero de Secu : "); scanf("%s", p.numSecu);
                printf("Jour : "); scanf("%d", &p.derniereVisite.jour);
                printf("Mois : "); scanf("%d", &p.derniereVisite.mois);
                printf("Annee : "); scanf("%d", &p.derniereVisite.annee);

                // On l'ajoute dans le tableau [cite: 19]
                praticien->maPatientele.listePatients[praticien->maPatientele.nbPatients] = p;
                praticien->maPatientele.nbPatients++;
            }
        } else {
            printf("Clientele complete[cite: 17]. Consultation simple uniquement.\n");
        }
    }
}

void mettreAJourDateVisite(Praticien *praticien, char numero_secu[]) {
    int trouve = 0;
    
    for (int i = 0; i < praticien->maPatientele.nbPatients; i++) {
        if (strcmp(praticien->maPatientele.listePatients[i].numSecu, numero_secu) == 0) {
            printf("Mise a jour pour %s.\n", praticien->maPatientele.listePatients[i].nom);
            
            printf("Nouveau jour : "); 
            scanf("%d", &praticien->maPatientele.listePatients[i].derniereVisite.jour);
            
            printf("Nouveau mois : "); 
            scanf("%d", &praticien->maPatientele.listePatients[i].derniereVisite.mois);
            
            printf("Nouvelle annee : "); 
            scanf("%d", &praticien->maPatientele.listePatients[i].derniereVisite.annee [cite: 19]);
            
            trouve = 1;
            break;
        }
    }

    if (trouve == 0) {
        printf("Aucun patient trouve avec ce numero de secu[cite: 17].\n");
    }
}