#include "../headers/heart.h"
/**
 * Se fichier est le coeur de l'application les décisions et reflexions serons faites ici.
 * @author Damien Chesneau <contact@damienchesneau.fr>
 */
char intToChar(int a);
int charToInt(char a);
int index_of_max(int *tab, int size);
int index_of_min(int* tab,int size);

int index_of_min(int* tab,int size){
    int i;
    int res = 0;
    for (i = 0; i < size; i++) {
        if (tab[res] > tab[i])
            res = i;
    }
    return res;
}

void HEART_best_ten_personnage(char * noms[10], Personnages personnages){
    int notes[10];
    int i;
    for(i = 0; i<10;i++){
        notes[i] = -1000;
    }
    while(personnages != NULL){
        int index = index_of_min(notes,10);
        if(personnages->note > notes[index]){
            notes[index] = personnages->note;
            noms[index] = personnages->nom;
        }
        personnages = personnages->next;
    }
}

/*
 * Fonction qui renvoie la question de la base la plus apte a etre posé.
 */
char * HEART_best_question(Questions * questions, Personnages personnages, int min_note,  int reponses[2][NB_MOY_QUESTION]) {
    if(*questions == NULL)
        return NULL;
    int values[(*questions)->index + 1][6];
    int res[(*questions)->index + 1];
    
    int i;
    int j;
    
    for (i = 0; i < (*questions)->index + 1; i++) {
            for (j = 0; j < 6; j++) {
                 values[i][j] = 0;
             }
            res[i] = 1;
    }
    
    for(i = 0; i<(*questions)->index + 1; i++){
        for(j = 0; j<NB_MOY_QUESTION; j++){
            if(i == reponses[0][j]){
                res[i] = 0;
            }
        }
    }
    Personnages perso_t = personnages;
    while(perso_t != NULL){
        if(perso_t->note >= min_note){
            for(i = 0; perso_t->reponses[i] != '-';i++){
                values[i][charToInt(perso_t->reponses[i])]++;
            }
        }
        perso_t = perso_t->next; 
    }
    for(j = 0; j<=(*questions)->index; j++){
        for(i = 1; i < 6; i++){
            res[j] *= (values[j][i]+1);
            /*printf("%d\n",values[j][i]+1);*/
        }
        /*printf(" res %d : %d \n",j,res[j]);*/
    }
    /*printf("\n");*/
    
    int index = index_of_max(res, (*questions)->index+1);

    for(i = 0; i< NB_MOY_QUESTION && reponses[0][i] != -1;i++);
    if(i!= NB_MOY_QUESTION )
        reponses[0][i] = index;
    /*printf("index %d\n",index);*/
    return BDD_USER_get_questions(questions, index);
}

Personnages HEART_new_personnages(char * path, int nbPersonnage) {
    Personnages personnage;
    BDD_USER_load_personnages(&personnage, path, nbPersonnage);
    return personnage;
}

Questions HEART_new_questions(char * path) {
    Questions questions;
    BDD_USER_load_questions(&questions, path);
    return questions;
}

void HEART_update_db(Personnages personnages, int value, int index_question) {
    while(personnages != NULL){
        int perso_value = charToInt(personnages->reponses[index_question]);
        if(perso_value != 0){
            int eval = value - perso_value;
            switch(eval){
                case -4:
                    personnages->note +=-3;
                    break;
                case -3:
                    personnages->note +=-2;
                    break;
                case -2:
                    personnages->note +=-1;
                    break;
                case -1:
                    personnages->note +=1;
                    break;
                case 0:
                    personnages->note +=3;
                    break;
                case 1:
                    personnages->note +=1;
                    break;
                case 2:
                    personnages->note +=-1;
                    break;
                case 3:
                    personnages->note +=-2;
                    break;
                case 4:
                    personnages->note +=-3;
                    break;
                default:
                    fprintf(stderr,"erreur note perso\n");
                    break;
            }
        }
        personnages = personnages->next;
    }
}

void HEART_update_personnage(Personnages  personnages, char* nom,  int reponses[2][NB_MOY_QUESTION]) {
    while(personnages != NULL){
        if(strcmp(personnages->nom,nom)==0){
            int i = 0;
            for( i = 0; i<NB_MOY_QUESTION; i++){
             if(personnages->reponses[reponses[0][i]] == '0'){
                personnages->reponses[reponses[0][i]] = intToChar(reponses[1][i]); 
             }
            }
        }
        personnages = personnages->next;
    }
}

void HEART_get_path_questions(char ** path) {
    strcpy((char *) path, BIN_PATH_STANDARD);
    strcat((char *) path, QUESTIONS_NAME_STANDARD);
}

void HEART_get_path_personnage(char ** path) {
    strcpy((char *) path, BIN_PATH_STANDARD);
    strcat((char *) path, POPULATION_NAME_STANDARD);
}

int index_of_max(int *tab, int size) {
    int i;
    int res = 0;
    for (i = 0; i < size; i++) {
        if (tab[res] < tab[i])
            res = i;
    }
    return res;
}

char intToChar(int a){
    return (char) a+48;
}
int charToInt(char a) {
    return (int) a - 48;
}

char * HEART_best_personnage(Personnages  personnages) {
    char * nom = NULL;
    int max = -1000;
    while(personnages != NULL){
        if(max < personnages->note){
            max = personnages->note;
            nom = personnages->nom;
        }
         personnages = personnages->next;  
    }
    return nom;
}
char ** HEART_get_bests_personnages(Personnages  personnages){
    return NULL;
}