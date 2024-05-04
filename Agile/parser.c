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
	for(int i=0;i<p-1;i++){
		int h=0;
		int k=1;
		for(int j=0;j<aux;j++){
			if(matrix[i][k] == 'W'){
				fprintf(problem, "(button l%d c%d)\n\t",i,j);
				fprintf(problem, "(white l%d c%d)\n\t",i,j);}
			if(matrix[i][k] == 'R'){
				fprintf(problem, "(button l%d c%d)\n\t",i,j);
				fprintf(problem, "(red l%d c%d)\n\t",i,j);}
			if(matrix[i][k] == 'B'){
				fprintf(problem, "(button l%d c%d)\n\t",i,j);
				fprintf(problem, "(blue l%d c%d)\n\t",i,j);}
			if(matrix[i][k] == 'G'){
				fprintf(problem, "(button l%d c%d)\n\t",i,j);
				fprintf(problem, "(green l%d c%d)\n\t",i,j);}

			if(matrix[i][h] == '-')
				fprintf(problem, "(normal l%d c%d)\n\t",i,j);
			if(matrix[i][h] == '*')
				fprintf(problem, "(broken1 l%d c%d)\n\t",i,j);
			if(matrix[i][h] == '_')
				fprintf(problem, "(broken2 l%d c%d)\n\t",i,j);
			if(matrix[i][h] == '|')
				fprintf(problem, "(broken3 l%d c%d)\n\t",i,j);
			if(matrix[i][h] == '#')
				fprintf(problem, "(broken4 l%d c%d)\n\t",i,j);
			h+=2; k+=2; 
		}
	}
	fprintf(problem, ")\n\t(:goal (and\n\t");
	for(int i=0;i<p;i++){
		int h=0;
		int k=1;
		for(int j=0;j<aux;j++){
			if(matrix[i][k] == 'W')
				fprintf(problem, "(white l%d c%d)\n\t",i,j);
			if(matrix[i][k] == 'R')
				fprintf(problem, "(white l%d c%d)\n\t",i,j);
			if(matrix[i][k] == 'B')
				fprintf(problem, "(white l%d c%d)\n\t",i,j);
			if(matrix[i][k] == 'G')
				fprintf(problem, "(white l%d c%d)\n\t",i,j);

			h+=2; k+=2; 
		}
	}
	fprintf(problem, ")))\n");

	fprintf(domain,"(define (domain lightsOut) (:types line column - object) (:predicates (red ?y - line ?x - column) (green ?y - line ?x - column) (blue ?y - line ?x - column) (white ?y - line ?x - column) (button ?x ?y - object) (normal ?y - line ?x - column) (broken1 ?y - line ?x - column) (broken2 ?y - line ?x - column) (broken3 ?y - line ?x - column) (broken4 ?y - line ?x - column)) (:action click :parameters( ?y - line ?x - column) :precondition ( and) :effect (and (when (button ?y ?x) (when (and (not (broken1 ?x ?y)) (red ?x ?y)) (and (not (red ?x ?y)) (green ?x ?y)))) (when (button ?y ?x) (when (and (not (broken1 ?x ?y)) (green ?x ?y)) (and (not (green ?x ?y)) (blue ?x ?y)))) (when (button ?y ?x) (when (and (not (broken1 ?x ?y)) (blue ?x ?y)) (and (not (blue ?x ?y)) (white ?x ?y)))) (when (button ?y ?X) (when (and (not (broken1 ?x ?y)) (white ?x ?y)) (and (not (white ?x ?y)) (red ?x ?y)))) (forall (?w - column)(and (when (button ?y ?w) (when (and (not (broken2 ?y ?w)) (red ?y ?w)) (and (not (red ?y ?w)) (green ?y ?w)))) (when (button ?y ?w) (when (and (not (broken4 ?y ?w)) (red ?y ?w)) (and (not (red ?y ?w)) (green ?y ?w)))) (when (button ?y ?w) (when (and (not (broken2 ?y ?w)) (green ?y ?w)) (and (not (green ?y ?w)) (blue ?y ?w)))) (when (button ?y ?w) (when (and (not (broken4 ?y ?w)) (green ?y ?w)) (and (not (green ?y ?w)) (blue ?y ?w)))) (when (button ?y ?w) (when (and (not (broken2 ?y ?w)) (blue ?y ?w)) (and (not (blue ?y ?w)) (white ?y ?w)))) (when (button ?y ?w) (when (and (not (broken4 ?y ?w)) (blue ?y ?w)) (and (not (blue ?y ?w)) (white ?y ?w)))) (when (button ?y ?w) (when (and (not (broken2 ?y ?w)) (white ?y ?w)) (and (not (white ?y ?w)) (red ?y ?w)))) (when (button ?y ?w) (when (and (not (broken4 ?y ?w)) (white ?y ?w)) (and (not (white ?y ?w)) (red ?y ?w)))))) (forall (?w - line)(and (when (button ?w ?x) (when (and (not (broken3 ?w ?x)) (red ?w ?x)) (and (not (red ?w ?x)) (green ?w ?x)))) (when (button ?w ?x) (when (and (not (broken4 ?w ?x)) (red ?w ?x)) (and (not (red ?w ?x)) (green ?w ?x)))) (when (button ?w ?x) (when (and (not (broken3 ?w ?x)) (green ?w ?x)) (and (not (green ?w ?x)) (blue ?w ?x)))) (when (button ?w ?x) (when (and (not (broken4 ?w ?x)) (green ?w ?x)) (and (not (green ?w ?x)) (blue ?w ?x)))) (when (button ?w ?x) (when (and (not (broken3 ?w ?x)) (blue ?w ?x)) (and (not (blue ?w ?x)) (white ?w ?x)))) (when (button ?w ?x) (when (and (not (broken4 ?w ?x)) (blue ?w ?x)) (and (not (blue ?w ?x)) (white ?w ?x)))) (when (button ?w ?x) (when (and (not (broken3 ?w ?x)) (white ?w ?x)) (and (not (white ?w ?x)) (red ?w ?x)))) (when (button ?w ?x) (when (and (not (broken4 ?w ?x)) (white ?w ?x)) (and (not (white ?w ?x)) (red ?w ?x)))))))))");
	fclose(domain);
	fclose(problem);

	//to submit
	system("/tmp/dir/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
	//to run on chococino
	//system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
	system("grep -Eo '(click [a-zA-Z][0-9] c[0-9])' < out > out2");
	




	FILE *inputFile = fopen("out2", "r");
	FILE *outFile = fopen("outFile", "w");
	char line[100];
	int l_num,c_num;
	 while (fgets(line, sizeof(line), inputFile) != NULL){
		if (sscanf(line, "click l%d c%d", &l_num, &c_num) == 2){
		    fprintf(outFile, "(click %d %d);", l_num, c_num);}
		 else { fprintf(outFile, "%s", line);}}
	 fclose(inputFile);
	 fclose(outFile);

	 system("sed '$ s/.$//' outFile > outFile2");
	 system("cat outFile2");

	return 0;
}

