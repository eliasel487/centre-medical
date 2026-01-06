#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_SPECIALITES 20

typedef enum {
    FAUX,
    VRAI
} Booleen;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    char nom[50];
    char numSecu[16]; 
    Date derniereVisite;
} Patient;

typedef struct {
    Patient *listePatients; 
    int nbPatients;
    int capaciteMax;        
} Patientele;

typedef struct maillon {
    Patient info;
    struct maillon *suiv;
} Maillon;

typedef struct {
    Maillon *t;
    Maillon *q;
} File;

typedef struct {
    char nom[50];
    Patientele maPatientele;
    File salleAttente;
} Praticien;

typedef struct MaillonPraticien {
    Praticien donnee;
    struct MaillonPraticien *suivant;
} MaillonPraticien;

typedef struct {
    char nomSpecialite[50];
    MaillonPraticien *listePraticiens;
    int nbPraticiens;
} Specialite;


typedef struct {
    Specialite tSpecialites[MAX_SPECIALITES];
    int nbSpecialites;
} CentreMedical;

//Fonction 
void initialiserCentre(CentreMedical *centre); //fait

void ajouterPraticien(CentreMedical *centre);  //fait

void supprimerPraticien(CentreMedical *centre); //fait

void chargerCentre(CentreMedical *centre, const char *nom_fichier); //elias

void sauvegarderCentre(CentreMedical *centre, const char *nom_fichier); //elias

int ajouterSpecialite(CentreMedical *centre, char nom_specialite[]); //fait

int rechercherSpecialite(CentreMedical *centre, char nom_specialite[]); //fait

void afficherSpecialites(CentreMedical *centre); //fait

void afficherPraticiensParSpecialite(CentreMedical *centre, char nom_specialite[]); //fait

void afficherCentre(CentreMedical *centre); 

void enregistrerArriveePatient(CentreMedical *centre);

int praticienPeutPrendrePatient(Praticien *praticien); //fait

void ajouterPatientFile(Praticien *praticien, Patient patient); //fait

Patient retirerPatientFile(Praticien *praticien);//fait

int fileVide(Praticien *praticien);//fait

void appelerProchainPatient(Praticien *praticien);//fait

void mettreAJourDateVisite(Praticien *praticien, char numero_secu[]);//fait

void afficherPatienteleAlphabetique(Praticien *praticien);

void afficherPatienteleParDate(Praticien *praticien);

void afficherPatientsAbsentsDepuis(Praticien *praticien, char date[]);

int rechercheLineairePatient(Patient tab[], char numero_secu[]);

int rechercherSpecialite(CentreMedical *centre, char nom_specialite[]);

void triPatientsAlphabetique(Patient tab[]);

void triPatientsParDate(Patient tab[]);

void afficherMenuPrincipal(CentreMedical *centre); //fait a comparer

void menuPraticien(CentreMedical *centre); //fait

void menuSecretaire(CentreMedical *centre); //elias ok

void menuPraticien(CentreMedical *centre); //elias ok
int main(void);//elias ok
void chargerCentre(CentreMedical *centre, const char *nom_fichier); //elias ok
void sauvegarderCentre(CentreMedical *centre, const char *nom_fichier); //elias ok


//Fonction pour les Files
File filenouv(void);
Booleen estVide(File f);
File adjq(File f, Patient x);
File supt(File f);
int longueur(File f);
void afficher(File f);
Patient tete(File f);