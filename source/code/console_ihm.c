#include "../headers/ihm.h"
/**
 * Se fichier permet de gerer l'interface utilisateur ici nous sommes dans l'implémentaion console
 * @author Damien Chesneau <contact@damienchesneau.fr>
 */
void IHM_demander_penser_personage(){
    printf("Pensez a une personne.\n");
}
int IHM_poser_question_utilisateur(char * question){
  printf("%s\n",question);
}/* retourne la reponse de l'utilisateur.'*/
int IHM_proposer_reponse(char * reponse, char * img){ // Heu pour l'image on va attendre un peut.
  printf("Nous pensons que votre personnage est : %s\n",reponse);
}/* retourne si le'utilisateurs est d'accord avec cela.'*/

