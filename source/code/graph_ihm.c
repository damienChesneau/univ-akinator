#include "../headers/ihm.h"
#include <MLV/MLV_all.h>
#include <string.h>
/**
 * Se fichier permet de gerer l'interface utilisateur ici nous sommes dans l'implémentaion graphique
 * @author Damien Chesneau <contact@damienchesneau.fr>
 */
#define GLOBAL_WINDOW_WIDTH 350
#define GLOBAL_WINDOW_HEIGHT 450

void init();
void printNewText(char * reponse);
void printTowText(char * reponseOne, char * reponseTow);
int printQueryWithButtons(char * question);
int recurTrueFalseRep(int btYesX, int btYesY, int btNoX, int btNoY);
void affichage(int message);

void IHM_demander_penser_personage() {
    init();
    printTowText("Pensez a une personne.", "Cliquez quand vous êtes pret.");
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
}

/** retourne la reponse de l'utilisateur.'*/
int IHM_poser_question_utilisateur(char * question) {
    init();
    MLV_clear_window(MLV_COLOR_BLACK);
    int ret = printQueryWithButtons(question);
    MLV_actualise_window();
    return ret;
}
/**
 * MLV_draw_adapted_text_box(
                positionBoxX, positionBoxY,
                text_box,
                size_interligne,
                MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
                MLV_TEXT_CENTER
        );
 * @param reponse
 * @param img
 * @return 
 */

/** retourne si le'utilisateurs est d'accord avec cela.'<br>
 return 1 if yes <br>
 * return 2 if no
 */
int IHM_proposer_reponse(char * reponse, char * img) { // Heu pour l'image on va attendre un peut.
    init();
    printTowText("Nous pensons que votre personnage est :", reponse);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 320, GLOBAL_WINDOW_HEIGHT - 300, "Cette réponse est elle correcte ?", 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    int btYesX = GLOBAL_WINDOW_WIDTH - 320, btYesY = GLOBAL_WINDOW_HEIGHT - 250;
    MLV_draw_adapted_text_box(btYesX, btYesY, "Oui", 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    int btNoX = GLOBAL_WINDOW_WIDTH - 120, btNoY = GLOBAL_WINDOW_HEIGHT - 250;
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 120, GLOBAL_WINDOW_HEIGHT - 250, "Non", 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_actualise_window();
    return recurTrueFalseRep(btYesX, btYesY, btNoX, btNoY);
}

/** Demande le nom du nouvel utilisateur et le retourne. */
char * IHM_ajouter_personnage() {
    init();
    MLV_Keyboard_button sym = MLV_KEYBOARD_NONE;
    MLV_Keyboard_modifier mod = MLV_KEYBOARD_KMOD_NONE;
    MLV_Button_state state;
    char* texte = NULL;
    char *texte1;
    MLV_Input_box *input_box = NULL, *input_box_1;
    MLV_Event event = MLV_NONE; //Évènenemt
    int quit = 0;
    input_box_1 = MLV_create_input_box(
            60, 100,
            230, 30,
            MLV_COLOR_WHITE, MLV_COLOR_WHITE,
            MLV_COLOR_BLACK, " Nom : "
            );
    texte1 = (char*) malloc(sizeof (char));
    *texte1 = '\0';
    affichage(0);
    do {
        event = MLV_get_event(
                &sym, &mod, NULL,
                &texte, &input_box,
                0, 0, NULL,
                &state
                );
        switch (event) {
            case MLV_NONE:
                break;
            case MLV_KEY:
                break;
            case MLV_INPUT_BOX:
                if (input_box == input_box_1) {
                    free(texte1);
                    texte1 = texte;
                    return texte1;
                }
                break;
            case MLV_MOUSE_BUTTON: // L'utilisateur a utilisé un 
                if (state == MLV_PRESSED) {
                    int x, y;
                    MLV_get_mouse_position(&x, &y);
                    if ((140 - 50 < x && GLOBAL_WINDOW_HEIGHT - 300 - 50 < y && 140 + 50 > x && GLOBAL_WINDOW_HEIGHT - 300 + 50 > y)) {
                        return texte1;
                    }
                }
                break;
            default:
                fprintf(
                        stderr,
                        "Erreur : la valeur de l'évènement récupéré est impossible."
                        );
                quit = 1;
        }
        affichage(0);
    } while (!quit);
    return NULL;
}

int IHM_afficher_liste_personages(char * personnages[], int nb_personnages) {
    int i = 0, marge = 20, saut = 30, x, y;

    init();
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_adapted_text_box(20, 40, "Choisisez le personnage auquel vous pensiez.", 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    for (i = 1; i < nb_personnages + 1; i++) {
        MLV_draw_adapted_text_box(20, 40 + (saut * i), personnages[i - 1], 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
        
    }
    MLV_draw_adapted_text_box(20, 40 + (saut * (nb_personnages+1)), "Il n'est pas ici :(", 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
    MLV_get_mouse_position(&x, &y);
    for (i = 1; i < nb_personnages + 1; i++) {
        if ((40 + (saut * i) - marge < y && 40 + (saut * i) + marge > y)) {
            return i;
        }
    }
    return -1;
}
char * IHM_ajouter_question(){
    
    init();
    MLV_Keyboard_button sym = MLV_KEYBOARD_NONE;
    MLV_Keyboard_modifier mod = MLV_KEYBOARD_KMOD_NONE;
    MLV_Button_state state;
    char* texte = NULL;
    char *texte1;
    MLV_Input_box *input_box = NULL, *input_box_1;
    MLV_Event event = MLV_NONE; //Évènenemt
    int quit = 0;
    input_box_1 = MLV_create_input_box(
            60, 100,
            230, 30,
            MLV_COLOR_WHITE, MLV_COLOR_WHITE,
            MLV_COLOR_BLACK, ">"
            );
    texte1 = (char*) malloc(sizeof (char));
    *texte1 = '\0';
    affichage(1);
    do {
        event = MLV_get_event(
                &sym, &mod, NULL,
                &texte, &input_box,
                0, 0, NULL,
                &state
                );
        switch (event) {
            case MLV_NONE:
                break;
            case MLV_KEY:
                break;
            case MLV_INPUT_BOX:
                if (input_box == input_box_1) {
                    free(texte1);
                    texte1 = texte;
                    return texte1;
                }
                break;
            case MLV_MOUSE_BUTTON: // L'utilisateur a utilisé un 
                if (state == MLV_PRESSED) {
                    int x, y;
                    MLV_get_mouse_position(&x, &y);
                    if ((140 - 50 < x && GLOBAL_WINDOW_HEIGHT - 300 - 50 < y && 140 + 50 > x && GLOBAL_WINDOW_HEIGHT - 300 + 50 > y)) {
                        return texte1;
                    }
                }
                break;
            default:
                fprintf(
                        stderr,
                        "Erreur : la valeur de l'évènement récupéré est impossible."
                        );
                quit = 1;
        }
        affichage(1);
    } while (!quit);
    return NULL;
}

void IHM_close(void) {
    MLV_free_window();
}

void affichage(int message) {
    char * messages[2] = {"Entrez le nom du personnage ici :","Entrez votre question ici :"};
    int taille_interlinge = 5;
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_all_input_boxes();
    MLV_draw_adapted_text_box(140, GLOBAL_WINDOW_HEIGHT - 300, "Press entrer...", 5, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_draw_text(
            60, 40,messages[message],
            MLV_COLOR_WHITE, 0
            );
    MLV_actualise_window();
}

int recurTrueFalseRep(int btYesX, int btYesY, int btNoX, int btNoY) {
    MLV_Keyboard_button* button;
    if ((button = (MLV_Keyboard_button*) malloc(sizeof (MLV_Keyboard_button))) == NULL) {
        printf("erreur d'allocation");
        exit(1); /*On ne peut plus jouer si on ne peut plus utiliser les touches :/ */
    }
    int x, y;
    MLV_wait_keyboard_or_mouse(button, NULL, NULL, NULL, NULL);
    MLV_get_mouse_position(&x, &y);
    int toRet = -1;
    if (*button == MLV_KEYBOARD_KP1 || (btYesX - 50 < x && btYesY - 50 < y && btYesX + 50 > x && btYesY + 50 > y)) {
        toRet = 1;
    } else if ((btNoX - 50 < x && btNoY - 50 < y && btNoX + 50 > x && btNoY + 50 > y)) {
        toRet = 2;
    }
    return toRet;
}

void printNewText(char * reponse) {
    MLV_draw_filled_rectangle(GLOBAL_WINDOW_WIDTH - 270, GLOBAL_WINDOW_HEIGHT - 200, GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT, MLV_COLOR_BLACK);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 270, GLOBAL_WINDOW_HEIGHT - 200, reponse, 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
}

void printTowText(char * reponseOne, char * reponseTow) {
    MLV_draw_filled_rectangle(0, 0, GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT, MLV_COLOR_BLACK);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 320, GLOBAL_WINDOW_HEIGHT - 400, reponseOne, 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 290, GLOBAL_WINDOW_HEIGHT - 350, reponseTow, 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
}

int printQueryWithButtons(char * question) {
    //    MLV_draw_filled_rectangle(0, 0, GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT, MLV_COLOR_BLACK);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 330, GLOBAL_WINDOW_HEIGHT - 400, question, 1, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);

    int btOneX = GLOBAL_WINDOW_WIDTH - 300, btOneY = GLOBAL_WINDOW_HEIGHT - 350, btDiag = 20;
    MLV_draw_filled_circle(GLOBAL_WINDOW_WIDTH - 300, GLOBAL_WINDOW_HEIGHT - 350, btDiag, MLV_COLOR_YELLOW);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 307, GLOBAL_WINDOW_HEIGHT - 359, "1", 5, MLV_COLOR_YELLOW, MLV_COLOR_BLACK, MLV_COLOR_YELLOW, MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 260, GLOBAL_WINDOW_HEIGHT - 359, "Sûrement", 5, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);

    int btTowX = GLOBAL_WINDOW_WIDTH - 300, btTowY = GLOBAL_WINDOW_HEIGHT - 300;
    MLV_draw_filled_circle(GLOBAL_WINDOW_WIDTH - 300, GLOBAL_WINDOW_HEIGHT - 300, btDiag, MLV_COLOR_BLUE);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 307, GLOBAL_WINDOW_HEIGHT - 309, "2", 5, MLV_COLOR_BLUE, MLV_COLOR_BLACK, MLV_COLOR_BLUE, MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 260, GLOBAL_WINDOW_HEIGHT - 309, "Probablement oui", 5, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);

    int btThreeX = GLOBAL_WINDOW_WIDTH - 300, btThreeY = GLOBAL_WINDOW_HEIGHT - 250;
    MLV_draw_filled_circle(GLOBAL_WINDOW_WIDTH - 300, GLOBAL_WINDOW_HEIGHT - 250, btDiag, MLV_COLOR_PALEGREEN1);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 307, GLOBAL_WINDOW_HEIGHT - 259, "3", 5, MLV_COLOR_PALEGREEN1, MLV_COLOR_BLACK, MLV_COLOR_PALEGREEN1, MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 260, GLOBAL_WINDOW_HEIGHT - 259, "Je ne sais pas", 5, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);

    int btFourX = GLOBAL_WINDOW_WIDTH - 300, btFourY = GLOBAL_WINDOW_HEIGHT - 200;
    MLV_draw_filled_circle(GLOBAL_WINDOW_WIDTH - 300, GLOBAL_WINDOW_HEIGHT - 200, btDiag, MLV_COLOR_SPRINGGREEN4);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 307, GLOBAL_WINDOW_HEIGHT - 209, "4", 5, MLV_COLOR_SPRINGGREEN4, MLV_COLOR_BLACK, MLV_COLOR_SPRINGGREEN4, MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 260, GLOBAL_WINDOW_HEIGHT - 209, "Probablement non", 5, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);

    int btFiveX = GLOBAL_WINDOW_WIDTH - 300, btFiveY = GLOBAL_WINDOW_HEIGHT - 150;
    MLV_draw_filled_circle(GLOBAL_WINDOW_WIDTH - 300, GLOBAL_WINDOW_HEIGHT - 150, btDiag, MLV_COLOR_RED);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 307, GLOBAL_WINDOW_HEIGHT - 159, "5", 5, MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box(GLOBAL_WINDOW_WIDTH - 260, GLOBAL_WINDOW_HEIGHT - 159, "Sûrement pas", 5, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_actualise_window();
    MLV_Keyboard_button* button;
    if ((button = (MLV_Keyboard_button*) malloc(sizeof (MLV_Keyboard_button))) == NULL) {
        printf("erreur d'allocation");
        exit(1); /*On ne peut plus jouer si on ne peut plus utiliser les touches :/ */
    }
    int x, y;
    MLV_wait_keyboard_or_mouse(button, NULL, NULL, NULL, NULL);
    MLV_get_mouse_position(&x, &y);
    int toRet = -1;
    if (*button == MLV_KEYBOARD_KP1 || (btOneX - btDiag < x && btOneY - btDiag < y && btOneX + btDiag > x && btOneY + btDiag > y)) {
        toRet = 1;
    }
    if (*button == MLV_KEYBOARD_KP2 || (btTowX - btDiag < x && btTowY - btDiag < y && btTowX + btDiag > x && btTowY + btDiag > y)) {
        toRet = 2;
    }
    if (*button == MLV_KEYBOARD_KP3 || (btThreeX - btDiag < x && btThreeY - btDiag < y && btThreeX + btDiag > x && btThreeY + btDiag > y)) {
        toRet = 3;
    }
    if (*button == MLV_KEYBOARD_KP4 || (btFourX - btDiag < x && btFourY - btDiag < y && btFourX + btDiag > x && btFourY + btDiag > y)) {
        toRet = 4;
    }
    if (*button == MLV_KEYBOARD_KP5 || (btFiveX - btDiag < x && btFiveY - btDiag < y && btFiveX + btDiag > x && btFiveY + btDiag > y)) {
        toRet = 5;
    }
    if (toRet == -1) {
        return printQueryWithButtons(question);
    }
    return toRet;
}

void init() {
    static init = 0;
    if (init == 0) {
        MLV_create_window("Akinator", "./profile.bmp", GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT);
        init++;
    }
}