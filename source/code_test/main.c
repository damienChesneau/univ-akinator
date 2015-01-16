/* 
 * File:   main.c
 * Author: sivanantham
 *
 * Created on 3 janvier 2015, 00:09
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/bdd.h"
/*
 * 
 */
int main(int argc, char** argv) {
    Questions questions = new_questions("chemin");
    Personnages personnages = new_personnage("chemin",questions->index+1);
    
    return (EXIT_SUCCESS);
}

