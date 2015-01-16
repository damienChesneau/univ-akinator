#include<stdio.h>
#include<stdlib.h>
#include<MLV/MLV_all.h>
/**
 * Se fichier permet d'accèder à la base de données
 * @author Steeve Sivanantham <steeve.sivanantham@gmail.com>
 */

/*******************STRUCTURE***********************/
struct question {
    int index;
    char* q;
    struct question *next;
};

typedef struct question* Questions;

struct personnage {
    int note;
    char* nom;
    char* reponses;
    struct personnage *next;
};

typedef struct personnage* Personnages;
/****************************************************/

void load_questions(Questions* question, char* path);
void load_personnages(Personnages* personnage, char* path, int nb_questions);

void add_question(Questions* question, char* q);
void add_personnage(Personnages* personnage, char* nom, char* reponses);

void print_question(Questions question);
void print_personnage(Personnages personnage);

void add_question_in_DB(Questions* question, char* new_question, Personnages* personnages, char* nom, char reponse);
void add_personnage_in_DB(Personnages* personnages, char* nom, char* reponses);

void save_questions(Questions question, char* path); /* A TESTER */
void rec_save_questions(Questions question, FILE* f, int last_question); /* A TESTER */

void save_personnages(Personnages personnage, char* path); /* A TESTER */
void rec_save_personnages(Personnages personnage, FILE* f, char* last_perso); /* A TESTER */

/****************************************************/
int main(int argc, char* argv[]) {
    /****TEST****/;

    /**LOAD**/
    Questions question = NULL;
    load_questions(&question, "./bin/questions.txt");
    print_question(question);

    printf("\n");

    Personnages personnages = NULL;
    load_personnages(&personnages, "./bin/population.txt", question->index + 1);
    print_personnage(personnages);

    /*******/

    /***********/
    return 0;
}
/**************************************************/
void save_personnages(Personnages personnage, char* path) {
    FILE *f;

    if ((f = fopen(path, "w")) == NULL)
        fprintf(stderr, "Erreur d'ouverture de la base de données de personnagess!");
    rec_save_personnages(personnage, f, personnage->nom);
    fclose(f);
}

void rec_save_personnages(Personnages personnage, FILE* f, char* last_perso) {
    if (personnage == NULL)
        return;

    rec_save_personnages(personnage->next, f, last_perso);
    int i;
    for (i = 0; personnage->nom[i] != '\0'; i++) {
        putc(personnage->nom[i], f);
    }
    putc('\n', f);
    for (i = 0; personnage->reponses[i] != '-'; i++) {
        putc(personnage->reponses[i], f);
    }
    if (strcmp(last_perso, personnage->nom) != 0)
        putc('\n', f);
}

void save_questions(Questions question, char* path) {
    FILE *f;

    if ((f = fopen(path, "w")) == NULL)
        fprintf(stderr, "Erreur d'ouverture de la base de données de personnagess!");
    rec_save_questions(question, f, question->index);
    fclose(f);
}

void rec_save_questions(Questions question, FILE* f, int last_question) {
    if (question == NULL)
        return;
    rec_save_questions(question->next, f, last_question);
    int i;
    for (i = 0; question->q[i] != '\0'; i++) {
        putc(question->q[i], f);
    }
    if (question->index != last_question)
        putc('\n', f);
}

void add_personnage_in_DB(Personnages* personnages, char* nom, char* reponses) {
    add_personnage(personnages, nom, reponses);
}

void add_question_in_DB(Questions* question, char* new_question, Personnages* personnages, char* nom, char reponse) {
    add_question(question, new_question);
    int num_question = (*question)->index;

    while (*personnages != NULL) {

        if (((*personnages)->reponses = (char*) malloc((num_question + 2) * sizeof (char))) == NULL)
            fprintf(stderr, "Erreur de réallocation");

        if (strcmp((*personnages)->nom, nom) == 0) {
            (*personnages)->reponses[num_question] = reponse;
            (*personnages)->reponses[num_question + 1] = '-';
        } else {
            (*personnages)->reponses[num_question] = '0';
            (*personnages)->reponses[num_question + 1] = '-';
        }
    }
}

void print_personnage(Personnages personnage) {
    int i;
    if (personnage == NULL)
        return;
    print_personnage(personnage->next);
    printf("%s:\n", personnage->nom);
    for (i = 0; personnage->reponses[i] != '-'; i++)
        printf("%c ", personnage->reponses[i]);
    printf("\n");
}

void load_personnages(Personnages* personnage, char* path, int nb_questions) {
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
            while ((buffer[last_read] = getc(f)) != '\n' && buffer[last_read]);
            i = 0;




            add_personnage(personnage, nom, reponses);
        }

    }

    fclose(f);
}

void load_questions(Questions* question, char* path) {
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
        if (buffer[last_read] != EOF) {
            if ((line = (char*) malloc((i + 1) * sizeof (char))) == NULL)
                fprintf(stderr, "Erreur d'allocation");

            line[i] = '\0';

            while (i > 0) {
                i--;
                line[i] = buffer[i];
            }

            add_question(question, line);
        }
    }

    fclose(f);
}

void add_personnage(Personnages* personnage, char* nom, char* reponses) {
    Personnages temp = *personnage;

    if ((*personnage = (Personnages) malloc(sizeof (struct personnage))) == NULL)
        fprintf(stderr, "Erreur d'allocation!");

    (*personnage)->nom = nom;
    (*personnage)->reponses = reponses;
    (*personnage)->note = 0;
    (*personnage)->next = temp;
}

void add_question(Questions* question, char* q) {

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

void print_question(Questions question) {
    if (question == NULL)
        return;
    print_question(question->next);
    printf("%d. %s\n", question->index, question->q);
}
