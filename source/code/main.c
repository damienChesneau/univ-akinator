#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/ihm.h"
#include "../headers/heart.h"

/*
 * Main file the input of this program
 */

char * serie_of_querys(Questions * questions, Personnages * personages, int reponses[2][NB_MOY_QUESTION]);
void querys(Questions * questions, Personnages * personages, int reponses[2][NB_MOY_QUESTION], Questions * copie_questions);
char * test = NULL;

int main(int argc, char** argv) {
    char path[80];
    int reponses[2][NB_MOY_QUESTION];
    int i;

    for (i = 0; i < NB_MOY_QUESTION; i++) {
        reponses[0][i] = -1;
    }
    Questions questions = NULL;
    Personnages personages = NULL;
    Questions copie_questions = NULL;

    HEART_get_path_questions((char **) &path);
    BDD_USER_load_questions(&questions, path);
    BDD_USER_load_questions(&copie_questions, path);
    
    
    HEART_get_path_personnage((char **) &path);
    BDD_USER_load_personnages(&personages, path, questions->index+1);

    IHM_demander_penser_personage();
    querys(&questions, &personages, reponses, &copie_questions);
    IHM_close();
    return (EXIT_SUCCESS);
}

void querys(Questions * questions, Personnages * personages, int reponses[2][NB_MOY_QUESTION], Questions * copie_questions) {
    char * pesrsonnage = NULL;
   
    char path_q[80];
    char path_p[80];
    
    HEART_get_path_questions((char **) &path_q);
    HEART_get_path_personnage((char **) &path_p);

    int nb_questions = (*copie_questions)->index+1;
    pesrsonnage = serie_of_querys(questions, personages, reponses);
    /*printf("OK5 %s\n", test);*/
    int resultat = 0;
    pesrsonnage = test;
    if (pesrsonnage != NULL) { /* It's throws error beacause personnage is NULL; :/ */
        resultat = IHM_proposer_reponse(pesrsonnage, NULL);
    }
    if (resultat == 1) {
        HEART_update_personnage(*personages, pesrsonnage, reponses);
        BDD_USER_save_questions(*copie_questions,path_q);
        BDD_USER_save_personnages(*personages,path_p);
        IHM_close();

    } else if (resultat == 2) {
        char * best_ten[10];
        HEART_best_ten_personnage(best_ten, *personages);
        int res_of_best_ten = IHM_afficher_liste_personages(best_ten, 9);
        if (res_of_best_ten != -1) {
            HEART_update_personnage(*personages, best_ten[res_of_best_ten - 1], reponses);
            char * query = IHM_ajouter_question();
            int reponse = IHM_poser_question_utilisateur(query);
            /*BDD_print_personnage(*personages);
            printf("\n");*/
            BDD_USER_add_question_in_DB(copie_questions, query, personages, best_ten[res_of_best_ten - 1],(char) (reponse + 48));
           /* BDD_print_personnage(*personages);
            printf("\n");*/

            BDD_USER_save_questions(*copie_questions,path_q);
            BDD_USER_save_personnages(*personages,path_p);
            IHM_close();
        } else {
            char * nom_personnage = IHM_ajouter_personnage();
            /*BDD_print_personnage(*personages);
            printf("\n");*/
            BDD_USER_add_personnage_in_DB(personages,nom_personnage, nb_questions);
            /*BDD_print_personnage(*personages);
            printf("\n");*/
            HEART_update_personnage(*personages,nom_personnage, reponses);
            BDD_USER_save_questions(*copie_questions,path_q);
            BDD_USER_save_personnages(*personages,path_p);
            /*BDD_print_personnage(*personages);
            printf("\n");*/
            IHM_close();
        }

    } else {
        /** Oulalala gros souci :/ */
    }
}

char * serie_of_querys(Questions * questions, Personnages * personages, int reponses[2][NB_MOY_QUESTION]) {
    static int nb = 0;
    char * best_q = NULL;
       /* BDD_print_question(*questions);*/
    if(nb<3)
        best_q = HEART_best_question(questions, *personages, 0, reponses);
    else
        best_q = HEART_best_question(questions, *personages, nb, reponses);
    /* BDD_print_question(*questions);*/
   /* printf("q : %s\n", best_q);*/
    /*printf("num question %d\n",nb);*/
   /* BDD_print_personnage(*personages);*/
    if (best_q == NULL) {
        char * quest = HEART_best_personnage(*personages);
        test = quest;
      /*  printf("1 %s\n", quest);*/
        return quest;
    } else {
        /* printf("OK2\n");*/
        int resultat = IHM_poser_question_utilisateur(best_q); /*resultat == -1, is it normal????*/
        /*printf("resultat ihm : %d\n", resultat);*/
        reponses[1][nb] = resultat;
        nb++;
        HEART_update_db(*personages, resultat, reponses[0][nb - 1]);
        if (resultat != -1) {
            if (nb <= NB_MOY_QUESTION) {
                serie_of_querys(questions, personages, reponses);
            } else {
                free(best_q);
                char * d = NULL;
                d = HEART_best_personnage(*personages); /* Propose a response*/
                test = d;
                return d;
            }
        } else {
            serie_of_querys(questions, personages, reponses);
        }
    }
    return NULL;
}
