#include <string.h>
#include "../headers/bdd.h"


/**
 * Se fichier permet d'accèder à la base de données
 * @author Steeve Sivanantham <steeve.sivanantham@gmail.com>
 */
/***
int main(int argc, char* argv[]) {
    Questions question = NULL;
    BDD_USER_load_questions(&question, "./test_bdd/bin/questions.txt");

    Personnages personnages = NULL;
    BDD_USER_load_personnages(&personnages, "./test_bdd/bin/population.txt", question->index + 1);



    char* test_rep = NULL;
    test_rep = (char*) malloc(8 * sizeof (char));
    int i;
    for (i = 0; i < 8; i++) {
        test_rep[i] = '0';
    }
    test_rep[i] = '-';
    BDD_USER_add_personnage_in_DB(&personnages, "test", test_rep);

   BDD_USER_add_question_in_DB(&question, "test?", &personnages, "test", '2');

  BDD_print_question(question);
    printf("\n");
  BDD_print_personnage(personnages);
    BDD_USER_save_personnages(personnages, "./test_bdd/bin/population_save_test.txt");
    BDD_USER_save_questions(question, "./test_bdd/bin/questions_save_test.txt");


    return 0;
}
****/
void concatenate_string(char **original, char *add);

void BDD_free_personnages(Personnages personnage){  
    if (personnage == NULL)
        return;
    
    BDD_free_personnages(personnage->next);
    
    free(personnage->nom);
    personnage->nom = NULL;
    free(personnage->reponses);
    personnage->reponses = NULL;
    free(personnage);
    personnage = NULL;
}

void BDD_free_questions(Questions question){  
    if (question == NULL)
        return;
    
    BDD_free_questions(question->next);
    
    free(question->q);
    question->q = NULL;
    free(question);
    question = NULL;
}

char * BDD_USER_get_questions(Questions * question, int index) {
    char * res = NULL;
    Questions temp =  *question;
    Questions prev = NULL;
    
    if(temp == NULL)
        return NULL;
    
    while (temp != NULL) {
        if (temp->index == index) {
            res = temp->q;
            Questions next = temp->next;
            if(prev != NULL){
                free(prev->next);
                prev->next = next;
            }else{
                *question = (*question)->next;
                free(temp);
            }
        }else{
            prev = temp;
        }
        temp = temp->next;
    }
    return res;
}

void BDD_USER_save_personnages(Personnages personnage, char* path) {
    FILE *f;

    if ((f = fopen(path, "w")) == NULL)
        fprintf(stderr, "Erreur d'ouverture de la base de données de personnagess!");
    BDD_rec_save_personnages(personnage, f, personnage->nom);
    fclose(f);
    BDD_free_personnages(personnage);
}

void BDD_rec_save_personnages(Personnages personnage, FILE* f, char* last_perso) {
    if (personnage == NULL)
        return;

    BDD_rec_save_personnages(personnage->next, f, last_perso);
    int i;
    for (i = 0; personnage->nom[i] != '\0'; i++) {
        putc(personnage->nom[i], f);
    }
    putc('\n', f);
    for (i = 0; personnage->reponses[i] != '-'; i++) {
        putc(personnage->reponses[i], f);
        putc(' ', f);
    }
    putc('-', f);
    putc('1', f);
    if (strcmp(last_perso, personnage->nom) != 0)
        putc('\n', f);
}

void BDD_USER_save_questions(Questions question, char* path) {
    FILE *f;

    if ((f = fopen(path, "w")) == NULL)
        fprintf(stderr, "Erreur d'ouverture de la base de données de personnagess!");
    BDD_rec_save_questions(question, f, question->index);
    fclose(f);
    BDD_free_questions(question);
}

void BDD_rec_save_questions(Questions question, FILE* f, int last_question) {
    if (question == NULL)
        return;
    BDD_rec_save_questions(question->next, f, last_question);
    int i;
    for (i = 0; question->q[i] != '\0'; i++) {
        putc(question->q[i], f);
    }
    if (question->index != last_question)
        putc('\n', f);
    
}

void BDD_USER_add_personnage_in_DB(Personnages* personnages, char* nom,int nb_questions) {
    char * reponses;
    if((reponses = (char *)malloc((nb_questions+1) * sizeof(char))) == NULL ){
        fprintf(stderr,"ERREUR D'ALLOCATION");
    }
    int i;
    for(i = 0; i<nb_questions;i++){
        reponses[i] = '0';
    }
    reponses[i] = '-';
    BDD_add_personnage(personnages, nom, reponses);
}

void BDD_USER_add_question_in_DB(Questions* question, char* new_question, Personnages* personnages, char* nom, char reponse) {
    BDD_add_question(question, new_question);
    int num_question = (*question)->index;
    Personnages temp = *personnages;
    while (temp != NULL) {
        if ((temp->reponses = (char*) realloc(temp->reponses, (num_question + 2) * sizeof (char))) == NULL)
            fprintf(stderr, "Erreur de réallocation");

        if (strcmp(temp->nom, nom) == 0) {
            temp->reponses[num_question] = reponse;
            temp->reponses[num_question + 1] = '-';
        } else {
            temp->reponses[num_question] = '0';
            temp->reponses[num_question + 1] = '-';
        }
        temp = temp->next;
    }
}

void BDD_print_personnage(Personnages personnage) {
    int i;
    if (personnage == NULL)
        return;
    BDD_print_personnage(personnage->next);
    printf("%s:\n", personnage->nom);
    for (i = 0; personnage->reponses[i] != '-'; i++)
        printf("%c ", personnage->reponses[i]);
    printf("\n");
}

void BDD_USER_load_personnages(Personnages* personnage, char* path, int nb_questions) {
    FILE *f;
    char buffer[255];
    char *nom = NULL;
    char* reponses = NULL;
    int i = 0;
    int last_read = i;


    buffer[last_read] = 'a';

    if ((f = fopen(path, "r")) == NULL)
        fprintf(stderr, "Erreur d'ouverture de la base de données de personnagess!");

    while (buffer[last_read] != EOF) {

        while ((buffer[i] = getc(f)) != '\n' && buffer[i] != EOF) {
            i++;
        }

        last_read = i;

        if (buffer[last_read] != EOF) {


            if ((nom = (char*) malloc((i + 1) * sizeof (char))) == NULL)
                fprintf(stderr, "Erreur d'allocation");

            nom[i] = '\0';

            while (i > 0) {
                i--;
                nom[i] = buffer[i];
            }

            if ((reponses = (char*) malloc((nb_questions + 1) * sizeof (char))) == NULL)/*+1 pour le caractère de fin de tableau ('-')*/
                fprintf(stderr, "Erreur d'allocation");

            for (i = 0; (reponses[i] = getc(f)) != '-'; i++) {
                getc(f);
            }
            while ((buffer[last_read] = getc(f)) != '\n' && buffer[last_read] != EOF);
            i = 0;



            BDD_add_personnage(personnage, nom, reponses);
        }

    }

    fclose(f);
}

void BDD_USER_load_questions(Questions* question, char* path) {
    FILE *f;
    char buffer[255];
    char *line = NULL;
    int i = 0;
    int last_read = i;


    buffer[last_read] = 'a';

    if ((f = fopen(path, "r")) == NULL)
        fprintf(stderr, "Erreur d'ouverture de la base de données de questions!");

    while (buffer[last_read] != EOF) {

        while ((buffer[i] = getc(f)) != '\n' && buffer[i] != EOF) {
            i++;
        }

        last_read = i;
        if (buffer[last_read] != EOF || last_read != 0) {
            if ((line = (char*) malloc((i + 1) * sizeof (char))) == NULL)
                fprintf(stderr, "Erreur d'allocation");

            line[i] = '\0';

            while (i > 0) {
                i--;
                line[i] = buffer[i];
            }


            BDD_add_question(question, line);
        }
    }

    fclose(f);
}

void BDD_add_personnage(Personnages* personnage, char* nom, char* reponses) {
    Personnages temp = *personnage;

    if ((*personnage = (Personnages) malloc(sizeof (struct personnage))) == NULL)
        fprintf(stderr, "Erreur d'allocation!");

    (*personnage)->nom = nom;
    (*personnage)->reponses = reponses;
    (*personnage)->note = 0;
    (*personnage)->next = temp;
}

void BDD_add_question(Questions* question, char* q) {

    Questions temp = *question;

    if ((*question = (Questions) malloc(sizeof (struct question))) == NULL)
        fprintf(stderr, "Erreur d'allocation!");

    (*question)->q = q;
    if (temp == NULL)
        (*question)->index = 0;
    else
        (*question)->index = temp->index + 1;
    (*question)->next = temp;
}

void BDD_print_question(Questions question) {
    if (question == NULL)
        return;
    BDD_print_question(question->next);
    printf("%d. %s\n", question->index, question->q);
}

void BDD_get_standard_path_for_questions(char ** path) {
    char * ret = BIN_PATH_STANDARD;
    concatenate_string(path, ret);
    char * add = QUESTIONS_NAME_STANDARD;
    concatenate_string(path, add);
    
}

void BDD_get_standard_path_for_popuation(char ** path) {
    char * ret = BIN_PATH_STANDARD;
    char * add = POPULATION_NAME_STANDARD;
    concatenate_string(&ret, add);
}

void concatenate_string(char ** original, char * add) {
    /*char  s1[100], s2[100], i, j;*/
    char s1[100], s2[100], i, j;
    strcpy(s1, *original);
    strcpy(s2, add);
    for (i = 0; s1[i] != '\0'; ++i); /* i contains length of string s1. */
    for (j = 0; s2[j] != '\0'; ++j, ++i) {
        s1[i] = s2[j];
    }
    s1[i] = '\0';
    *original = s1;
}