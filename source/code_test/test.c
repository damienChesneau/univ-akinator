#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>


/*******************STRUCTURE***********************/
typedef struct question{
	int index;
  char* q;
  struct question *next;
}question;

typedef question* Questions;


typedef struct personnage{
  char* nom;
  int* reponses;
  int note;
  struct personnage *next;
}personnage;

typedef personnage* Personnage;
/****************************************************/


void load_questions(Questions* question, char* path);
void add_question(Questions* questions, char* q, int index);
void print_question(Questions question);

/****************************************************/
int main(int argc, char* argv[]){
	/****TEST****/
	
	/**LOAD**/
	Questions question = NULL;
	load_questions(&question, "./bin/questions.txt");
	print_question(question);
	/*******/
	
	/***********/
	return 0;
}
/**************************************************/


void load_questions(Questions* question, char* path){
	FILE *f;
	char buffer[255];
	char *line = NULL;
	int index = 0;
	int i = 0;
	int last_read = i;
	
	
	buffer[last_read]='a';
	
	if ((f = fopen(path,"r")) == NULL)
		fprintf(stderr,"Erreur d'ouverture de la base de données de questions!");
		
	while (buffer[last_read] != EOF){
		
		while  ((buffer[i] = getc(f)) != '\n' && buffer[i] != EOF ){
			i++;   
		}	
	
		last_read = i;
		if (buffer[last_read] != EOF){
			if ((line = (char*)malloc((i+1)*sizeof(char))) == NULL)
				fprintf(stderr,"Erreur d'allocation");
		
			line[i] = '\0';
			
			while (i>0){
				i--;
				line[i] = buffer[i];
			}
		
			add_question(question, line, index);
			index++;		
		}
  }
  
  fclose(f);
}

void add_question(Questions* questions, char* q, int index){
  
  Questions temp = *questions;
	
	if ((*questions = (Questions)malloc(sizeof(question))) == NULL)
		fprintf(stderr,"Erreur d'allocation!");
  
  (*questions)->q = q;
  (*questions)->index = index;
  (*questions)->next = temp;
}

void print_question(Questions question){
  if(question == NULL)
    return;
  printf("%d. %s\n",question->index, question->q);
  print_question(question->next);
}
