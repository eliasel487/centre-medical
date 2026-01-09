/**
 * @file sae.h
 * @brief Gestion d'un centre médical (spécialités, praticiens, patients)
 *
 * Ce programe permet de gérer un centre médical avec :
 * - des spécialités
 * - des praticiens
 * - des patients
 * - une salle d'attente (file)
 *
 * SAE
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPECIALITES 20

/**
 * @enum Booleen
 * @brief Booléen personnalisé
 */
typedef enum {
    FAUX,
    VRAI
} Booleen;

/**
 * @struct Date
 * @brief Représente une date (jour/mois/année)
 */
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

/**
 * @struct Patient
 * @brief Informations d'un patient
 */
typedef struct {
    char nom[50];
    char numSecu[16];
    Date derniereVisite;
} Patient;

/**
 * @struct Patientele
 * @brief Liste des patients suivis par un praticien
 */
typedef struct {
    Patient *listePatients;
    int nbPatients;
    int capaciteMax;
} Patientele;

/**
 * @struct Maillon
 * @brief Maillon de la file des patients
 */
typedef struct maillon {
    Patient info;
    struct maillon *suiv;
} Maillon;

/**
 * @struct File
 * @brief File FIFO représentant une salle d'attente
 */
typedef struct {
    Maillon *t;
    Maillon *q;
} File;

/**
 * @struct Praticien
 * @brief Représente un médecin du centre médical
 */
typedef struct {
    char nom[50];
    Patientele maPatientele;
    File salleAttente;
} Praticien;

/**
 * @struct MaillonPraticien
 * @brief Maillon de la liste chaînée des praticiens
 */
typedef struct MaillonPraticien {
    Praticien donnee;
    struct MaillonPraticien *suivant;
} MaillonPraticien;

/**
 * @struct Specialite
 * @brief Spécialité médicale (ex : cardiologie)
 */
typedef struct {
    char nomSpecialite[50];
    MaillonPraticien *listePraticiens;
    int nbPraticiens;
} Specialite;

/**
 * @struct CentreMedical
 * @brief Structure principale du centre médical
 */
typedef struct {
    Specialite tSpecialites[MAX_SPECIALITES];
    int nbSpecialites;
} CentreMedical;

/*  GESTION DU CENTRE  */

/**
 * @brief Initialise un centre médical vide
 * @param centre pointeur vers le centre médical
 */
void initialiserCentre(CentreMedical *centre);

/**
 * @brief Charge les données du centre depuis un fichier
 * @param centre pointeur vers le centre
 * @param nom_fichier nom du fichier
 */
void chargerCentre(CentreMedical *centre, char *nom_fichier);

/**
 * @brief Sauvegarde les données du centre dans un fichier
 * @param centre pointeur vers le centre
 * @param nom_fichier nom du fichier
 */
void sauvegarderCentre(CentreMedical *centre, char *nom_fichier);

/**
 * @brief Affiche l'état global du centre médical
 * @param centre pointeur vers le centre
 */
void afficherCentre(CentreMedical *centre);

/**
 * @brief Recherche une spécialité par son nom
 * @param centre pointeur vers le centre
 * @param nom_specialite nom recherché
 * @return indice de la spécialité ou -1 si absente
 */
int rechercherSpecialite(CentreMedical *centre, char nom_specialite[]);

/**
 * @brief Ajoute une spécialité au centre
 * @param centre pointeur vers le centre
 * @param nom_specialite nom de la spécialité
 * @return 1 si ajout réussi, 0 sinon
 */
int ajouterSpecialite(CentreMedical *centre, char nom_specialite[]);

/**
 * @brief Supprime une spécialité et tous ses praticiens
 * @param centre pointeur vers le centre
 */
void supprimerSpecialite(CentreMedical *centre);

/*  PRATICIENS  */

/**
 * @brief Ajoute un praticien à une spécialité du centre médical
 * @param centre pointeur vers le centre médical
 */
void ajouterPraticien(CentreMedical *centre);

/**
 * @brief Supprime un praticien d'une spécialité
 * @param centre pointeur vers le centre médical
 */
void supprimerPraticien(CentreMedical *centre);

/**
 * @brief Affiche les praticiens d'une spécialité pouvant accepter de nouveaux patients
 * @param centre pointeur vers le centre médical
 * @param nom_specialite nom de la spécialité concernée
 */
void afficherPraticiensParSpecialite(CentreMedical *centre, char nom_specialite[]);

/**
 * @brief Indique si un praticien peut encore accepter des patients
 * @param praticien pointeur vers le praticien
 * @return 1 si oui, 0 sinon
 */
int praticienPeutPrendrePatient(Praticien *praticien);


/*  PATIENTS  */

/**
 * @brief Enregistre l'arrivée d'un patient dans le centre médical
 * @param centre pointeur vers le centre médical
 */
void enregistrerArriveePatient(CentreMedical *centre);

/**
 * @brief Appelle le prochain patient de la salle d'attente
 * @param praticien pointeur vers le praticien
 */
void appelerProchainPatient(Praticien *praticien);

/**
 * @brief Met à jour la date de dernière visite d'un patient
 * @param praticien pointeur vers le praticien
 * @param numero_secu numéro de sécurité sociale du patient
 */
void mettreAJourDateVisite(Praticien *praticien, char numero_secu[]);

/**
 * @brief Affiche la patientèle par ordre alphabétique
 * @param praticien pointeur vers le praticien
 */
void afficherPatienteleAlphabetique(Praticien *praticien);

/**
 * @brief Affiche la patientèle du plus récent au plus ancien
 * @param praticien pointeur vers le praticien
 */
void afficherPatienteleParDate(Praticien *praticien);

/**
 * @brief Supprime les patients absents depuis une date donnée
 * @param praticien pointeur vers le praticien
 */
void faireMenagePatientele(Praticien *praticien);

/**
 * @brief Supprime un patient de la patientèle
 * @param praticien pointeur vers le praticien
 * @param numero_secu numéro de sécurité sociale du patient
 */
void supprimerPatientDePatientele(Praticien *praticien, char numero_secu[]);


/*  FILE (SALLE D'ATTENTE)  */

/**
 * @brief Crée une file vide
 * @return une file initialisée
 */
File filenouv(void);

/**
 * @brief Indique si une file est vide
 * @param f file à tester
 * @return VRAI si vide, FAUX sinon
 */
Booleen estVide(File f);

/**
 * @brief Ajoute un patient en fin de file
 * @param f file
 * @param x patient à ajouter
 * @return nouvelle file
 */
File adjq(File f, Patient x);

/**
 * @brief Supprime l'élément en tête de file
 * @param f file
 * @return nouvelle file
 */
File supt(File f);

/**
 * @brief Calcule le nombre d'éléments d'une file
 * @param f file
 * @return longueur de la file
 */
int longueur(File f);

/**
 * @brief Affiche le contenu de la file
 * @param f file à afficher
 */
void afficher(File f);

/**
 * @brief Renvoie le patient en tête de file
 * @param f file
 * @return patient en tête
 */
Patient tete(File f);


/*  TRI & UTILITAIRES  */

/**
 * @brief Recherche un patient par numéro de sécurité sociale
 * @param tab tableau de patients
 * @param n taille du tableau
 * @param numero_secu numéro recherché
 * @return indice du patient ou -1 si absent
 */
int rechercheLineairePatient(Patient tab[], int n, char numero_secu[]);

/**
 * @brief Trie les spécialités par ordre alphabétique
 * @param tab tableau de spécialités
 * @param n nombre de spécialités
 */
void triParEchangeSpecialites(Specialite tab[], int n);

/**
 * @brief Trie les patients par ordre alphabétique
 * @param tab tableau de patients
 * @param n nombre de patients
 */
void triParEchangePatientNom(Patient tab[], int n);

/**
 * @brief Trie les patients par date de visite (plus récent au plus ancien)
 * @param tab tableau de patients
 * @param n nombre de patients
 */
void trifusionPatientsDate(Patient tab[], int n);


/*  MENUS  */

/**
 * @brief Menu pour un praticien
 * @param centre pointeur vers le centre médical
 */
void menuPraticien(CentreMedical *centre);

/**
 * @brief Menu pour la secrétaire
 * @param centre pointeur vers le centre médical
 */
void menuSecretaire(CentreMedical *centre);