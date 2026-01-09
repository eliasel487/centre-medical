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


void initialiserCentre(CentreMedical *centre); //fait
void chargerCentre(CentreMedical *centre, char *nom_fichier); //fait
void sauvegarderCentre(CentreMedical *centre, char *nom_fichier); //fait
void afficherCentre(CentreMedical *centre); //fait
int rechercherSpecialite(CentreMedical *centre, char nom_specialite[]); //fait
int ajouterSpecialite(CentreMedical *centre, char nom_specialite[]); //fait
void afficherSpecialites(CentreMedical *centre); //fait
void afficherPraticiensParSpecialite(CentreMedical *centre, char nom_specialite[]); //fait
void ajouterPraticien(CentreMedical *centre);  //fait
void supprimerPraticien(CentreMedical *centre); //fait
int praticienPeutPrendrePatient(Praticien *praticien); //fait
void enregistrerArriveePatient(CentreMedical *centre);//fait 
void ajouterPatientFile(Praticien *praticien, Patient patient); //fait
Patient retirerPatientFile(Praticien *praticien);//fait
int fileVide(Praticien *praticien);//fait
void appelerProchainPatient(Praticien *praticien);//fait
void mettreAJourDateVisite(Praticien *praticien, char numero_secu[]);//fait
void afficherPatienteleAlphabetique(Praticien *praticien);//fait
void afficherPatienteleParDate(Praticien *praticien);//fait
void faireMenagePatientele(Praticien *praticien);int rechercheLineairePatient(Patient tab[], int n, char numero_secu[]); //fait
void menuPraticien(CentreMedical *centre); //fait
void menuSecretaire(CentreMedical *centre); //fait
void supprimerPatientDePatientele(Praticien *praticien, char numero_secu[]);
void supprimerSpecialite(CentreMedical *centre);
int main(void);//fait


//Fonction pour les Files
File filenouv(void);
Booleen estVide(File f);
File adjq(File f, Patient x);
File supt(File f);
int longueur(File f);
void afficher(File f);
Patient tete(File f);

//Fonction pour les tri 
void triParEchangeSpecialites(Specialite tab[], int n);
void triParEchangePatientNom(Patient tab[], int n);
void trifusionPatientsDate(Patient tab[], int n);
void echangerPatient(Patient tab[], int i, int j);
int plusGrandPatientNom(Patient tab[], int n);
int estPlusRecent(Date d1, Date d2);
void copierPatients(Patient source[], int debut, int fin, Patient dest[]);
void fusionPatientsDate(Patient R[], int n, Patient S[], int m, Patient T[]);