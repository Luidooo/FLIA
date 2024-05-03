#include <stdio.h>
#include <stdlib.h>

char matrix[40][40];
int main(void){
	int p=0;
	while(scanf(" %s", matrix[p++]) == 1);
	FILE *domain = fopen("domain.pddl", "w");
	FILE *problem = fopen("problem.pddl", "w");
	fprintf(problem, "(define (problem fisrt)\n\t(:domain lightsOut)\n\t(:objects\n\t");	
	for (int i=0;i<p-1;i++)
		fprintf(problem, " l%d ", i);
	fprintf(problem, " - line\n\t");
	int aux=-1;
	for (int i=0;i<p-1;i++){
		int j=0;
		while(matrix[i][j++] != '\0');
		aux = aux > j ? aux : j;}
	for(int i=0;i<aux/2;i++){
		fprintf(problem, " c%d ", i);}
	fprintf(problem, " - column)\n\t (:init\n\t");
	for(int i=0;i<p;i++){
		int h=0;
		int k=1;
		for(int j=0;j<aux;j++){
			if(matrix[i][k] == 'W'){
				fprintf(problem, "(button c%d l%d)\n\t",j,i);
				fprintf(problem, "(white c%d l%d)\n\t",j,i);}
			if(matrix[i][k] == 'R'){
				fprintf(problem, "(button c%d l%d)\n\t",j,i);
				fprintf(problem, "(red c%d l%d)\n\t",j,i);}
			if(matrix[i][k] == 'B'){
				fprintf(problem, "(button c%d l%d)\n\t",j,i);
				fprintf(problem, "(blue c%d l%d)\n\t",j,i);}
			if(matrix[i][k] == 'G'){
				fprintf(problem, "(button c%d l%d)\n\t",j,i);
				fprintf(problem, "(green c%d l%d)\n\t",j,i);}

			if(matrix[i][h] == '-')
				fprintf(problem, "(normal c%d l%d)\n\t",j,i);
			if(matrix[i][h] == '*')
				fprintf(problem, "(broken1 c%d l%d)\n\t",j,i);
			if(matrix[i][h] == '_')
				fprintf(problem, "(broken2 c%d l%d)\n\t",j,i);
			if(matrix[i][h] == '|')
				fprintf(problem, "(broken3 c%d l%d)\n\t",j,i);
			if(matrix[i][h] == '#')
				fprintf(problem, "(broken4 c%d l%d)\n\t",j,i);
			h+=2; k+=2; 
		}
	}
	fprintf(problem, ")\n\t(:goal (and\n\t");
	for(int i=0;i<p;i++){
		int h=0;
		int k=1;
		for(int j=0;j<aux;j++){
			if(matrix[i][k] == 'W')
				fprintf(problem, "(white c%d l%d)\n\t",j,i);
			if(matrix[i][k] == 'R')
				fprintf(problem, "(white c%d l%d)\n\t",j,i);
			if(matrix[i][k] == 'B')
				fprintf(problem, "(white c%d l%d)\n\t",j,i);
			if(matrix[i][k] == 'G')
				fprintf(problem, "(white c%d l%d)\n\t",j,i);

			h+=2; k+=2; 
		}
	}
	fprintf(problem, ")))\n");

	fprintf(domain," (define (domain lightsOut) (:types line column - object) (:predicates (red ?x - column ?y - line) (green ?x - column ?y - line) (blue ?x - column ?y - line) (white ?x - column ?y - line) (button ?x ?y - object) (normal ?x - column ?y - line) (broken1 ?x - column ?y - line) (broken2 ?x - column ?y - line) (broken3 ?x - column ?y - line) (broken4 ?x - column ?y - line)) (:action click :parameters ( ?x - column ?y - line) :precondition ( and) :effect (and (when (and (not (broken1 ?x ?y)) (red ?x ?y)) (and (not (red ?x ?y)) (green ?x ?y))) (when (and (not (broken1 ?x ?y)) (green ?x ?y)) (and (not (green ?x ?y)) (blue ?x ?y))) (when (and (not (broken1 ?x ?y)) (blue ?x ?y)) (and (not (blue ?x ?y)) (white ?x ?y))) (when (and (not (broken1 ?x ?y)) (white ?x ?y)) (and (not (white ?x ?y)) (red ?x ?y))) (forall (?w - column)(and (when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (red ?w ?y)) (and (not (red ?w ?y)) (green ?w ?y)))) (when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (red ?w ?y)) (and (not (red ?w ?y)) (green ?w ?y)))) (when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (green ?w ?y)) (and (not (green ?w ?y)) (blue ?w ?y)))) (when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (green ?w ?y)) (and (not (green ?w ?y)) (blue ?w ?y)))) (when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (blue ?w ?y)) (and (not (blue ?w ?y)) (white ?w ?y)))) (when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (blue ?w ?y)) (and (not (blue ?w ?y)) (white ?w ?y)))) (when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (white ?w ?y)) (and (not (white ?w ?y)) (red ?w ?y)))) (when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (white ?w ?y)) (and (not (white ?w ?y)) (red ?w ?y)))))) (forall (?w - line)(and (when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (red ?x ?w)) (and (not (red ?x ?w)) (green ?x ?w)))) (when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (red ?x ?w)) (and (not (red ?x ?w)) (green ?x ?w)))) (when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (green ?x ?w)) (and (not (green ?x ?w)) (blue ?x ?w)))) (when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (green ?x ?w)) (and (not (green ?x ?w)) (blue ?x ?w)))) (when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (blue ?x ?w)) (and (not (blue ?x ?w)) (white ?x ?w)))) (when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (blue ?x ?w)) (and (not (blue ?x ?w)) (white ?x ?w)))) (when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (white ?x ?w)) (and (not (white ?x ?w)) (red ?x ?w)))) (when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (white ?x ?w)) (and (not (white ?x ?w)) (red ?x ?w)))))))))");
	fclose(domain);
	fclose(problem);

    //to submit
	system("/tmp/dir/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
    //to run on chococino
	//system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
	system("grep -Eo \"(click [a-zA-Z][0-9] [a-zA-Z][0-9])\" < out > out2");
	system("sed 's/\\(click \\)c\\([0-9]\\) l\\([0-9]\\)/\\(\\1\\2 \\3\\);/g' out2 > out3");
	system("sed '$s/;$//' out3 > out");
	system("cat out");

	return 0;
}

