#include <stdio.h>
#include <stdlib.h>
#include "../headers/ihm.h"
#include "../headers/heart.h"
/*
 * Main file the input of this program
 */
extern void get_path_questions(char ** path);
extern void get_path_personnage(char ** path);

char * serie_of_querys(Questions * questions, Personnages * personages);
void querys(Questions * questions, Personnages * personages);

int main(int argc, char** argv) {
    /*char* tab[] = {"Damien ", "Steeve", "Steeve", "Steeve", "Steeve", "Steeve", "Steeve", "Steeve", "Steeve", "Steeve", "Steeve", "Steeve"};
    int result = IHM_afficher_liste_personages(tab, 10);
    printf("%d,\n",result);*/
    char * ds = IHM_ajouter_question();
    printf("tes= %s \n",ds);
    while (1) {

    }
    IHM_close();

    return (EXIT_SUCCESS);
}

void querys(Questions * questions, Personnages * personages) {
    char * personnage = serie_of_querys(questions, personages);
    int resultat = IHM_proposer_reponse(personnage, NULL);

    if (resultat == 1) {
        IHM_close();
    } else if (resultat == 2) {
        querys(questions, personages);
    } else {
        /** Oulalala gros souci :/ */
    }
}

/* Que doit faire cette question contenir des personnage?(cf variable) ou des questions?*/
char * serie_of_querys(Questions * questions, Personnages * personages) {
    static int nb = 0;
  /*  int resultat = IHM_poser_question_utilisateur(HEART_best_question(*questions, *personages));
    nb++;
    if (resultat != -1) {
        if (nb <= NB_MOY_QUESTION) {
            printf("dez\n");
            serie_of_querys(questions, personages);
        } else {
            return "Damien Chesneau"; /* Propose a response*//*
        }
    } else {
        serie_of_querys(questions, personages);
    }*/
    return NULL;
}
