#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//Structure 
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
void initialiserCentre(CentreMedical *centre);
void chargerCentre(CentreMedical *centre, const char *nom_fichier);
void sauvegarderCentre(CentreMedical *centre, const char *nom_fichier);
int ajouterSpecialite(CentreMedical *centre, char nom_specialite[]); //fait
int rechercherSpecialite(CentreMedical *centre, char nom_specialite[]); //fait
void afficherSpecialites(CentreMedical *centre);
int ajouterPraticien(CentreMedical *centre);
void supprimerPraticien(CentreMedical *centre);
void afficherPraticiensParSpecialite(CentreMedical *centre, char nom_specialite[]); //fait
void afficherCentre(CentreMedical *centre);
void enregistrerArriveePatient(CentreMedical *centre);
int praticienPeutPrendrePatient(Praticien *praticien);
void ajouterPatientFile(Praticien *praticien, Patient patient);
Patient retirerPatientFile(Praticien *praticien);
int fileVide(Praticien *praticien);
void appelerProchainPatient(Praticien *praticien);
void mettreAJourDateVisite(Praticien *praticien, char numero_secu[], char nouvelle_date[]);
void afficherPatienteleAlphabetique(Praticien *praticien);
void afficherPatienteleParDate(Praticien *praticien);
void afficherPatientsAbsentsDepuis(Praticien *praticien, char date[]);
int rechercheLineairePatient(CellulePatient *liste, char numero_secu[]);
int rechercherSpecialite(CentreMedical *centre, char nom_specialite[]);
void triPatientsAlphabetique(CellulePatient **liste);
void triPatientsParDate(CellulePatient **liste);
void afficherMenuPrincipal();
void saisirChaine(char message[], char resultat[], int taille);


//Fonction pour les Files
File filenouv(void);
Booleen estVide(File f);
File adjq(File f, Patient x);
File supt(File f);
int longueur(File f);
void afficher(File f);
Patient tete(File f);