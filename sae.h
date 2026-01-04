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
void initialiserCentre(CentreMedical *centre);
void ajouterPraticien(CentreMedical *centre);
void supprimerPraticien(CentreMedical *centre);

//Fonction pour les Files
File filenouv(void);
Booleen estVide(File f);
File adjq(File f, Patient x);
File supt(File f);
int longueur(File f);
void afficher(File f);
Patient tete(File f);