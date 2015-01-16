#include <stdlib.h>
#include <stdio.h>

#define BIN_PATH_STANDARD "./bin/"
#define POPULATION_NAME_STANDARD "population.txt"
#define QUESTIONS_NAME_STANDARD "questions.txt"
#define NB_MOY_QUESTION 20
/**
 * formated name : BDD
 */
/*******************STRUCTURES***********************/
struct question {
    int index;/*numéro de la question, commence a 0. Directement lié au tableau de réponse des personnages.*/
    char* q;/*question*/
    struct question *next;/*élément suivant*/
};

struct personnage {
    int note;/*note du personnage pour la partie (initialement a 0)*/
    char* nom;/*nom du personnage*/
    char* reponses;/*tableau contenant les différentes réponses a chaque questions de la base de donnée, elle doit être alloué et se terminer par '-'. L'index est directement lié avec l'index des questions.*/
    struct personnage *next;/*élément suivant*/
};

typedef struct question * Questions;
typedef struct personnage * Personnages;

/**
 * Libère la base de donnée de personnage.
 * @param personnage : base de personnage.
 */
void BDD_free_personnages(Personnages personnage);
/**
 * Libère la base de questions.
 * @param questions : base de questions.
 */
void BDD_free_questions(Questions questions);

/**
 * Returs the standard path of question file.
 * 
 */
void BDD_get_standard_path_for_questions(char ** path);
/**
 * Returs the standard path of question file.
 * 
 */
void BDD_get_standard_path_for_popuation(char ** path);
/*
 * Fonction utilisateur qui permet de récupérer une question dans une base de question.
 * @param question: base de données de questions non NULL.
 * @param index: numéro de la question.
 * 
 */
char * BDD_USER_get_questions(Questions * question, int index);

/*
 * Fonction utilisateur qui charge les questions de la base de données dans une structure Questions, l'allocation est géré par cette fonction.
 * @param question: pointeur null.
 * @param path: chemin vers la base de données de questions.
 */
void BDD_USER_load_questions(Questions* question, char* path);


/*
 * Fonction utilisateur qui charge les personnage de la de données dans une structure Personnages, l'allocation est géré par cette fonction.
 * Il faut avoir chargé une base de données de question pour charger une base de données Personnage.
 * @param personnage: pointeur null.
 * @param path: chemin vers la base de données de personnages.
 * @param nb_questions: nombres de question dans la base données de question. A noter que pour récupérer le nombre de question il suffit de regarder l'index+1 du première élément d'une structure Questions.
 */
void BDD_USER_load_personnages(Personnages* personnage, char* path, int nb_questions);

/*
 * Fonction non utilisateur qui ajoute(en tête) une question dans une base de données, l'allocation est géré par cette fonction.
 * @param question: base de données de questions destinataire.
 * @param q: question a ajouter.
 */
void BDD_add_question(Questions* question, char* q);

/*
 * Fonction non utilisateur qui ajoute (en tête) un personnage dans une base de données, l'allocation est géré par cette fonction.
 * @param personnage: base de données de personnages destinataire.
 * @param nom: nom du nouveau personnage.
 * @param reponses: base de données de réponse du personnage(tableau de valeurs entre 0 et 5).
 */
void BDD_add_personnage(Personnages* personnage, char* nom, char* reponses);

/*
 * Fonction de test qui affiche une base de données de question.
 * @param question: base de données de questions a afficher.
 */
void BDD_print_question(Questions question);

/*
 * Fonction de test qui affiche une base de données de personnage
 * @param personnage: base de données de personnages a afficher.
 */
void BDD_print_personnage(Personnages personnage);

/*
 * Fonction qui permet d'ajouter une question dans une base de données de questions, l'allocation est géré par cette fonction.
 * @param question: base de données de questions destinataire.
 * @param new_question: nouvelle question a ajouter dans la base de données destinataire.
 * @param personnages: base de données de personnages lié a la base de données de questions destinataire.
 * @param nom: nom du personnage lié a la nouvelle question.
 * @param reponse: reponse a la nouvelle question pour le personnage lié a la nouvelle question.
 */
void BDD_USER_add_question_in_DB(Questions* question, char* new_question, Personnages* personnages, char* nom, char reponse);

/*
 * Fonction qui permet d'ajouter un personnage dans une base de données de personnages, l'allocation est géré par cette fonction.
 * @param personnages: base de données de personnages destinataire.
 * @param nom: nom du nouveau personnage a ajouter.
 * @param reponses: base de données de réponse du personnage(tableau de valeurs entre 0 et 5) et elle doit avoir été alloué par malloc et le dernière élément du tableau doit être '-'.
 */
void BDD_USER_add_personnage_in_DB(Personnages* personnages, char* nom, int nb_questions);


/*
 * Fonction qui sauvgarde une base de données de question.
 * @param question: base de données de questions a sauvegarder.
 * @param path: chemin vers le point de sauvegarde.
 */
void BDD_USER_save_questions(Questions question, char* path);

/*
 * Fonction non utilisateur qui permet un parcours recursif de la base de données de questions pour la sauvegarde des éléments de la base.
 * @param question: base de données de questions a sauvegarder.
 * @param f: flux vers le point de sauvegarde.
 * @param last_question: la dernière question a être ajouté dans la base (la question en tête).
 */
void BDD_rec_save_questions(Questions question, FILE * f, int last_question);


/*
 * Fonction qui sauvgarde une base de données de personnages.
 * @param question: base de données de personnages a sauvegarder.
 * @param path: chemin vers le point de sauvegarde.
 */
void BDD_USER_save_personnages(Personnages personnage, char* path);

/*
 * Fonction non utilisateur qui permet un parcours recursif de la base de données de personnages pour la sauvegarde des éléments de la base.
 * @param personnage: base de données de personnages a sauvegarder.
 * @param f: flux vers le point de sauvegarde.
 * @param last_personnage: le dernier personnage a être ajouté dans la base (la question en tête).
 */
void BDD_rec_save_personnages(Personnages personnage, FILE* f, char* last_perso);