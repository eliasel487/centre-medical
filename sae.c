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

    int ind = -1;
    for(i=0; i<centre->nbSpecialites; i++){
        if (strcmp(centre->tSpecialites[i].nomSpecialite, nomSpe) == 0){
            ind = i;
            break;
        }
    }

    if (ind == -1) {
        ind = centre->nbSpecialites;
        strcpy(centre->tSpecialites[ind].nomSpecialite, nomSpe);
        centre->tSpecialites[ind].listePraticiens = NULL;
        centre->tSpecialites[ind].nbPraticiens = 0;
        centre->nbSpecialites++;
    }

    MaillonPraticien *tmp = (MaillonPraticien*)malloc(sizeof(MaillonPraticien));
    if (tmp == NULL){
        printf("Pb malloc.\n");
        exit(1);}
    strcpy(tmp->donnee.nom, nomDr);
    tmp->donnee.salleAttente = filenouv();
    tmp->donnee.maPatientele.nbPatients = 0;

    tmp->donnee.maPatientele.capaciteMax = capacitemax;
    tmp->donnee.maPatientele.listePatients = (Patient*)malloc(capacitemax * sizeof(Patient));
    tmp->suivant = centre->tSpecialites[ind].listePraticiens;

    centre->tSpecialites[ind].listePraticiens = tmp;
    centre->tSpecialites[ind].nbPraticiens++;
    printf("Praticien ajouté avec succès.\n");
}



void supprimerPraticien(CentreMedical *centre) {
    char nomSpe[50], nomDr[50];
    
    printf("Spécialité du praticien : ");
    scanf("%s", nomSpe);
    
    int idxSpe = rechercherSpecialite(centre, nomSpe);
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
            if (precedent == NULL) {
                centre->tSpecialites[idxSpe].listePraticiens = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }
            free(courant->donnee.maPatientele.listePatients);         
            while(!estVide(courant->donnee.salleAttente)) {
                courant->donnee.salleAttente = supt(courant->donnee.salleAttente);
            }
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
              if (p->donnee.maPatientele.nbPatients < p->donnee.maPatientele.capaciteMax) {
                    printf("-%s (Places : %d/%d)\n", p->donnee.nom, p->donnee.maPatientele.nbPatients,p->donnee.maPatientele.capaciteMax);
                }
                p = p->suivant;
            }
            return;
        }
    }
    printf("La specialite '%s' n'existe pas.\n", nom_specialite);
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
void triParEchangeSpecialites(Specialite tab[], int n) {
    int i, j, min;
    Specialite temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(tab[j].nomSpecialite, tab[min].nomSpecialite) < 0) {
                min = j;
            }
        }
        temp = tab[min];
        tab[min] = tab[i];
        tab[i] = temp;
    }
}
void afficherSpecialites(CentreMedical *centre) {
    int i;
    if (centre->nbSpecialites == 0) {
        printf("Aucune spécialité n'est enregistrée dans le centre.\n");
        return;
    }
    triParEchangeSpecialites(centre->tSpecialites, centre->nbSpecialites);
    printf("Liste des Spécialités : \n");
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

Patient retirerPatientFile(Praticien *praticien) {
    if (fileVide(praticien)) {
        printf("Erreur : La file d'attente est vide.\n");
        exit(1); 
    }
    Patient p = tete(praticien->salleAttente);
    praticien->salleAttente = supt(praticien->salleAttente);
    return p;
}

int fileVide(Praticien *praticien) {
    if (estVide(praticien->salleAttente) == VRAI) {
        return 1;
    }
    return 0;
}

int rechercheLineairePatient(Patient tab[], int n, char numero_secu[]) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(tab[i].numSecu, numero_secu) == 0) {
            return i;
        }
    }
    return -1;
}

void appelerProchainPatient(Praticien *praticien) {
    if (fileVide(praticien)) {
        printf("La salle d'attente est vide.\n");
        return;
    }
    Patient p = retirerPatientFile(praticien);
    printf("\nAppel du patient : %s\n", p.nom);
    int trouve = -1;
    if (strcmp(p.numSecu, "Inconnu") != 0) {
        trouve = rechercheLineairePatient(praticien->maPatientele.listePatients,praticien->maPatientele.nbPatients, p.numSecu);
    }
    if (trouve != -1) {
        mettreAJourDateVisite(praticien, p.numSecu);
    } else {
        if (praticien->maPatientele.nbPatients < praticien->maPatientele.capaciteMax) {
            printf("Nouveau patient. Ajouter a la clientele ? (1:Oui / 0:Non) : ");
            int rep;
            if (scanf("%d", &rep) == 0) {
                char poubelle[50];
                scanf("%s", poubelle);
                rep = 0; }
            if (rep == 1) {
                printf("Numero de Secu : "); scanf("%s", p.numSecu);
                printf("Jour (JJ) : "); scanf("%d", &p.derniereVisite.jour);
                printf("Mois (MM) :"); scanf("%d", &p.derniereVisite.mois);
                printf("Annee (YYYY) :"); scanf("%d", &p.derniereVisite.annee);
                praticien->maPatientele.listePatients[praticien->maPatientele.nbPatients] = p;
                praticien->maPatientele.nbPatients++;}
        } else {
            printf("Clientele complete. Consultation simple uniquement.\n");
        }
    }
}

void mettreAJourDateVisite(Praticien *praticien, char numero_secu[]) {
    int trouve = rechercheLineairePatient(praticien->maPatientele.listePatients, praticien->maPatientele.nbPatients, numero_secu);
    if (trouve != -1) {
        printf("Mise a jour pour %s.\n", praticien->maPatientele.listePatients[trouve].nom);    
        printf("Nouveau jour : "); 
        scanf("%d", &praticien->maPatientele.listePatients[trouve].derniereVisite.jour);   
        printf("Nouveau mois : "); 
        scanf("%d", &praticien->maPatientele.listePatients[trouve].derniereVisite.mois);
        printf("Nouvelle annee : "); 
        scanf("%d", &praticien->maPatientele.listePatients[trouve].derniereVisite.annee);
    } else {
        printf("Aucun patient trouve avec ce numero de secu\n");}
}

void menuSecretaire(CentreMedical *centre) {
    int choix = -1,i,idxSpe;
    char nomSpe[50],nomPrat[50],poubelle[50];
    while (choix != 0) {
        printf("\n------ MENU SECRETAIRE ------\n");
        printf("1 - Ajouter un praticien\n");
        printf("2 - Supprimer un praticien\n");
        printf("3 - Afficher toutes les specialites\n");
        printf("4 - Afficher les praticiens d'une specialite acceptant de prendre de nouveaux patients\n");
        printf("5 - Afficher tout le centre medical\n");
        printf("6 - Enregistrer l'arrivee d'un patient\n");
        printf("0 - Retour\n");
        printf("Votre choix : ");
        if (scanf("%d", &choix) == 0) {
            scanf("%s", poubelle);
            choix = -1;}
        if (choix == 1) {
            ajouterPraticien(centre);}
        else if (choix == 2) {
            supprimerPraticien(centre);}
        else if (choix == 3) {
            afficherSpecialites(centre);}
        else if (choix == 4) {
            printf("Nom de la specialite : ");
            scanf("%s", nomSpe);
            afficherPraticiensParSpecialite(centre, nomSpe);}
        else if (choix == 5) {
            afficherCentre(centre); }
        else if (choix == 6) {
            enregistrerArriveePatient(centre); }
        else if (choix == 0) {
            return; }
        else { 
            printf("Choix invalide.\n");} 
    }
}


void menuPraticien(CentreMedical *centre){
    int choix = -1,idxSpe;
    char nomSpe[50], nomPrat[50],numSecu[20],poubelle[50];
    printf("Nom de la specialite : ");
    scanf("%s", nomSpe);
    idxSpe = rechercherSpecialite(centre, nomSpe);
    if (idxSpe == -1) {
        printf("Specialite inexistante.\n");
        return;
    }
    printf("Nom du praticien : ");
    scanf("%s", nomPrat);
    MaillonPraticien *p = centre->tSpecialites[idxSpe].listePraticiens;
    while (p != NULL && strcmp(p->donnee.nom, nomPrat) != 0) {
        p = p->suivant; }
    if (p == NULL) {
        printf("Praticien introuvable.\n");
        return;}
    Praticien *praticien = &p->donnee;
    while (choix != 0) {
        printf("\n------ MENU PRATICIEN ------\n");
        printf("1 - Appeler le prochain patient\n");
        printf("2 - Afficher la patientele (ordre alphabetique)\n");
        printf("3 - Afficher la patientele (visite recente -> ancienne)\n");
        printf("4 - Afficher les patients absents depuis une certaine date\n");
        printf("5 - Supprimer un patient de la patientele\n");
        printf("0 - Retour\n");
        printf("Votre choix : ");
        if (scanf("%d", &choix) == 0) {
            scanf("%s", poubelle);
            choix = -1;
        }
        if (choix == 1) {
            appelerProchainPatient(praticien);}
        else if (choix == 2) {
            afficherPatienteleAlphabetique(praticien);}
        else if (choix == 3) {
            afficherPatienteleParDate(praticien);}
        else if (choix == 4) {
            afficherPatientsAbsents(praticien);}
        else if (choix == 5) {
            printf("Numero de secu du patient a supprimer : ");
            scanf("%s", numSecu);
            supprimerPatientDePatientele(praticien, numSecu);}
        else if (choix == 0) {
            return;}
        else { 
            printf("Choix invalide.\n"); } 
    }
}



void chargerCentre(CentreMedical *centre, char *nom_fichier) {
    FILE *f;
    int i, j, k, nbPrat, nbP;
    MaillonPraticien *nouveauPrat;
    f = fopen(nom_fichier, "r");
    if (f == NULL) {
        centre->nbSpecialites = 0;
        return;
    }
    if (fscanf(f, "%d", &centre->nbSpecialites) != 1) {
        centre->nbSpecialites = 0;
        fclose(f);
        return;
    }
    for (i = 0; i < centre->nbSpecialites; i++) {
        fscanf(f, "%s", centre->tSpecialites[i].nomSpecialite);
        fscanf(f, "%d", &nbPrat);  
        centre->tSpecialites[i].nbPraticiens = 0;
        centre->tSpecialites[i].listePraticiens = NULL;
        for (j = 0; j < nbPrat; j++) {
            nouveauPrat = (MaillonPraticien *)malloc(sizeof(MaillonPraticien));
            if (nouveauPrat == NULL) exit(1);  
            fscanf(f, "%s %d %d", nouveauPrat->donnee.nom, &nouveauPrat->donnee.maPatientele.capaciteMax, &nouveauPrat->donnee.maPatientele.nbPatients);
            nouveauPrat->donnee.salleAttente.t = NULL;
            nouveauPrat->donnee.salleAttente.q = NULL;
            nbP = nouveauPrat->donnee.maPatientele.nbPatients;
            nouveauPrat->donnee.maPatientele.listePatients = (Patient *)malloc(sizeof(Patient) * nouveauPrat->donnee.maPatientele.capaciteMax);
            if (nouveauPrat->donnee.maPatientele.listePatients == NULL){ 
                exit(1);}
            for (k = 0; k < nbP; k++) {
                fscanf(f, "%s %s %d/%d/%d", nouveauPrat->donnee.maPatientele.listePatients[k].nom,nouveauPrat->donnee.maPatientele.listePatients[k].numSecu,&nouveauPrat->donnee.maPatientele.listePatients[k].derniereVisite.jour,&nouveauPrat->donnee.maPatientele.listePatients[k].derniereVisite.mois,&nouveauPrat->donnee.maPatientele.listePatients[k].derniereVisite.annee);
            }
            nouveauPrat->suivant = centre->tSpecialites[i].listePraticiens;
            centre->tSpecialites[i].listePraticiens = nouveauPrat;
            centre->tSpecialites[i].nbPraticiens++;
        }
    }
    fclose(f);
}

void sauvegarderCentre(CentreMedical *centre, char *nom_fichier) {
    FILE *f;
    int i, k, nbP;
    MaillonPraticien *courantPrat;
    
    f = fopen(nom_fichier, "w");
    if (f == NULL) {
        return;
    }
    fprintf(f, "%d\n", centre->nbSpecialites);
    for (i = 0; i < centre->nbSpecialites; i++) {
        fprintf(f, "%s\n", centre->tSpecialites[i].nomSpecialite);
        fprintf(f, "%d\n", centre->tSpecialites[i].nbPraticiens);
        courantPrat = centre->tSpecialites[i].listePraticiens;
        while (courantPrat != NULL) {
            fprintf(f, "%s %d %d\n", courantPrat->donnee.nom, courantPrat->donnee.maPatientele.capaciteMax,courantPrat->donnee.maPatientele.nbPatients);
            nbP = courantPrat->donnee.maPatientele.nbPatients;
            for (k = 0; k < nbP; k++) {
                fprintf(f, "%s %s %d/%d/%d\n", courantPrat->donnee.maPatientele.listePatients[k].nom,courantPrat->donnee.maPatientele.listePatients[k].numSecu, courantPrat->donnee.maPatientele.listePatients[k].derniereVisite.jour,courantPrat->donnee.maPatientele.listePatients[k].derniereVisite.mois,courantPrat->donnee.maPatientele.listePatients[k].derniereVisite.annee);
            }
            courantPrat = courantPrat->suivant;
        }
    }
    fclose(f);
}

void afficherCentre(CentreMedical *centre) {
    if (centre->nbSpecialites == 0) {
        printf("Le centre ne contient aucune specialite.\n");
        return;
    }

    printf("\n--- AFFICHE DU CENTRE MEDICAL ---\n");
    triParEchangeSpecialites(centre->tSpecialites, centre->nbSpecialites);

    for (int i = 0; i < centre->nbSpecialites; i++) {
        printf("\nSPECIALITE : %s\n", centre->tSpecialites[i].nomSpecialite);
        MaillonPraticien *courant = centre->tSpecialites[i].listePraticiens;
        if (courant == NULL) {
            printf("  (Aucun praticien enregistre)\n");
        }
        while (courant != NULL) {
            printf("%-15s | Patientele : %d/%d | En attente : %d\n", courant->donnee.nom, courant->donnee.maPatientele.nbPatients, courant->donnee.maPatientele.capaciteMax,longueur(courant->donnee.salleAttente));          
            courant = courant->suivant;
        }
    }
}

void enregistrerArriveePatient(CentreMedical *centre) {
    char nomPat[50], nomSpe[50], nomDr[50];
    int aDejaMedecin;

    printf("Nom du patient : "); 
    scanf("%s", nomPat);
    printf("Specialite demandee : "); 
    scanf("%s", nomSpe);

    int idxSpe = rechercherSpecialite(centre, nomSpe);
    if (idxSpe == -1) {
        printf("Desole, pas de praticien de cette specialite dans le centre.\n"); 
        return;
    }
    printf("Etes-vous deja suivi par un praticien ici ? (1:Oui / 0:Non) : ");
    scanf("%d", &aDejaMedecin);
    Praticien *choisi = NULL;
    MaillonPraticien *courant = centre->tSpecialites[idxSpe].listePraticiens;
    if (aDejaMedecin == 1) {
        printf("Nom de votre praticien : "); scanf("%s", nomDr);
        while (courant != NULL) {
            if (strcmp(courant->donnee.nom, nomDr) == 0) {
                choisi = &(courant->donnee);
                break;
            }
            courant = courant->suivant;
        }
    } else {
        while (courant != NULL) {
            if (courant->donnee.maPatientele.nbPatients < courant->donnee.maPatientele.capaciteMax) {
                choisi = &(courant->donnee);
                break;
            }
            courant = courant->suivant;
        }
    }
    if (choisi != NULL) {
        Patient nouveau;
        strcpy(nouveau.nom, nomPat);
        strcpy(nouveau.numSecu, "Inconnu");
        nouveau.derniereVisite.jour = 0;
        ajouterPatientFile(choisi, nouveau);
        printf("Patient enregistre dans la file de Dr. %s.\n", choisi->nom);} 
        else {
            printf("Pas de place disponible pour un nouveau patient chez nos praticiens.\n");
    }
}


void echangerPatient(Patient tab[], int i, int j) {
    Patient aux;
    aux = tab[i];
    tab[i] = tab[j];
    tab[j] = aux;
}

int plusGrandPatientNom(Patient tab[], int n) {
    int i, pge = 0;
    for (i = 0; i < n; i++) {
        if (strcmp(tab[i].nom, tab[pge].nom) > 0)
            pge = i;
    }
    return pge;
}

void triParEchangePatientNom(Patient tab[], int n) {
    int pge;
    while (n > 1) {
        pge = plusGrandPatientNom(tab, n);
        echangerPatient(tab, pge, n - 1);
        n = n - 1;
    }
}

void afficherPatienteleAlphabetique(Praticien *praticien) {
    int n = praticien->maPatientele.nbPatients;
    if (n == 0) {
        printf("La clientele de Dr. %s est vide.\n", praticien->nom);
        return;
    }
    Patient *temp = (Patient*)malloc(n * sizeof(Patient));
    if (temp == NULL){
        printf("Pb malloc.\n");
        exit(1);}
    for(int i = 0; i < n; i++) {
        temp[i] = praticien->maPatientele.listePatients[i];
    }
    triParEchangePatientNom(temp, n);
    printf("\nClientele de Dr. %s\n", praticien->nom);
    for (int i = 0; i < n; i++) {
        printf("%-20s | Secu: %s | Visite: %02d/%02d/%d\n", temp[i].nom, temp[i].numSecu,temp[i].derniereVisite.jour, temp[i].derniereVisite.mois, temp[i].derniereVisite.annee);
    }
    free(temp);
}

int estPlusRecent(Date d1, Date d2) {
    if (d1.annee > d2.annee){
        return 1;}
    if (d1.annee < d2.annee){ 
        return 0;}   
    if (d1.mois > d2.mois){
        return 1;}
    if (d1.mois < d2.mois){
        return 0;}
    if (d1.jour >= d2.jour){ 
        return 1;}
    return 0;
}

void copierPatients(Patient source[], int debut, int fin, Patient dest[]) {
    int k = 0;
    int i = debut;
    while (i < fin) {
        dest[k] = source[i];
        i++;
        k++;
    }
}

void fusionPatientsDate(Patient R[], int n, Patient S[], int m, Patient T[]) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (estPlusRecent(R[i].derniereVisite, S[j].derniereVisite)) {
            T[k] = R[i];
            i++;
        } else {
            T[k] = S[j];
            j++;
        }
        k++;
    }
    while (i < n) {
        T[k] = R[i];
        i++; k++;
    }
    while (j < m) {
        T[k] = S[j];
        j++; k++;
    }
}

void trifusionPatientsDate(Patient tab[], int n) {
    if (n <= 1)
        return;
    Patient *R, *S;
    R = (Patient*)malloc((n / 2) * sizeof(Patient));
    S = (Patient*)malloc((n - n / 2) * sizeof(Patient));
    if (R == NULL || S == NULL){
        printf("Pb malloc.\n");
        exit(1);}
    copierPatients(tab,0,n/2,R);
    copierPatients(tab,n/2,n,S);
    trifusionPatientsDate(R,n/2);
    trifusionPatientsDate(S,n-n/2);
    fusionPatientsDate(R,n/2,S,n-n/2,tab);
    free(R);
    free(S);
}

void afficherPatienteleParDate(Praticien *praticien) {
    int n = praticien->maPatientele.nbPatients;
    
    if (n == 0) {
        printf("La clientele de Dr. %s est vide.\n", praticien->nom);
        return;
    }
    Patient *temp = (Patient*)malloc(n * sizeof(Patient));
    if (temp == NULL){
        printf("Pb malloc.\n");
        exit(1);}
    for(int i = 0; i < n; i++) {
        temp[i] = praticien->maPatientele.listePatients[i];
    }
    trifusionPatientsDate(temp, n);
    printf("\nClientele de Dr. %s\n", praticien->nom);
    for (int i = 0; i < n; i++) {
        printf("%02d/%02d/%d | %s\n", temp[i].derniereVisite.jour, temp[i].derniereVisite.mois, temp[i].derniereVisite.annee, temp[i].nom);
    }
    free(temp);
}

void afficherPatientsAbsents(Praticien *praticien) {
    int jourLim, moisLim, anneeLim;
    int i;
    printf("Entrez la date limite (JJ MM AAAA) : ");
    scanf("%d %d %d", &jourLim, &moisLim, &anneeLim);
    printf("\n--- Patients qui ne sont pas venus depuis cette date ---\n");
    for (i = 0; i < praticien->maPatientele.nbPatients; i++) {
        Patient p = praticien->maPatientele.listePatients[i];
        int estVieux = 0; 
        if (p.derniereVisite.annee < anneeLim) {
            estVieux = 1;}
        else if (p.derniereVisite.annee == anneeLim) {
            if (p.derniereVisite.mois < moisLim) {
                estVieux = 1;}
            else if (p.derniereVisite.mois == moisLim) {
                if (p.derniereVisite.jour < jourLim) {
                    estVieux = 1;}
            }
        }
        if (estVieux == 1) {
            printf("- %s (Date : %d/%d/%d)\n", p.nom, p.derniereVisite.jour, p.derniereVisite.mois, p.derniereVisite.annee);
        }
    }
}

void supprimerPatientDePatientele(Praticien *praticien, char numero_secu[]) {
    int ind = rechercheLineairePatient(praticien->maPatientele.listePatients, praticien->maPatientele.nbPatients, numero_secu);
    if (ind == -1){
        printf("Erreur : Aucun patient trouvé avec le numéro de sécu %s.\n", numero_secu);
        return;}
    printf("Suppression du patient %s...\n", praticien->maPatientele.listePatients[ind].nom);
    for (int i = ind; i < praticien->maPatientele.nbPatients - 1; i++) {
        praticien->maPatientele.listePatients[i] = praticien->maPatientele.listePatients[i+1];
    }
    praticien->maPatientele.nbPatients--;
    printf("Le patient a été supprimé de la patientèle avec succès.\n");
}


