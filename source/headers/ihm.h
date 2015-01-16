#include <stdio.h>
/**
 * formated name : IHM
 */
/**
 * Request the user to think to a character
 */
void IHM_demander_penser_personage();
/** 
 * Pose une question et retourne la reponse de l'utilisateur.
 * Ask the query and return the user response. 
 * @return -1 if error, 1,2,3,4,5 are the workable returns
 */
int IHM_poser_question_utilisateur(char * question); 
/** returns if users are agree with that.<br>
 * return 1 if yes <br>
 * return 2 if no
 */
int IHM_proposer_reponse(char * reponse, char * img);
/** Asks the name of the new user and returns. */
char * IHM_ajouter_personnage();
/**
 * 
 * @param char tab pointer personnages
 * @param int nb_personnages
 * @return selected personnage or -1 if is not in the list.
 */
int IHM_afficher_liste_personages(char * personnages[], int nb_personnages);

char * IHM_ajouter_question();
/**
 * For something like that should not waste time typing of unnecessary doc that no one will read Haha.
 */
void IHM_close(void);