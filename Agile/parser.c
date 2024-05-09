#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char matrix[100][100];
int main(void){
	int p=0;
	while(scanf(" %s", matrix[p++]) == 1);
	FILE *domain = fopen("domain.pddl", "w");
	FILE *problem = fopen("problem.pddl", "w");
	fprintf(problem, "(define (problem fisrt)\n\t(:domain lightsOut)\n\t(:objects\n\t");	

	int maxColumns=-1;
	for (int i=0;i<p-1;i++){
		int j=0;
		while(matrix[i][j++] != '\0');
		maxColumns = maxColumns > j ? maxColumns : j;}

  int lenColumns[p-1];
  for(int i=0;i<p-1;i++) lenColumns[i] = strlen(matrix[i]);

	for(int i=0;i<p-1;i++)
		for(int j=0;j<lenColumns[i]/2;j++)
			fprintf( problem, "loc%d-%d ", i,j);
	fprintf( problem, " - location)\n\t (:init\n\t");

	for(int i=0;i<p-1;i++){
		int h=0;
		int k=1;
    fprintf(problem, "\n");
		for(int j=0;j<lenColumns[i];j++){
			if(matrix[i][k] == 'W'){
				fprintf(problem, "(white loc%d-%d) ",i,j);}
			if(matrix[i][k] == 'R'){
				fprintf(problem, "(red loc%d-%d) ",i,j);}
			if(matrix[i][k] == 'B'){
				fprintf(problem, "(blue loc%d-%d) ",i,j);}
			if(matrix[i][k] == 'G'){
				fprintf(problem, "(green loc%d-%d) ",i,j);}

			if(matrix[i][h] == '*')
				fprintf(problem, "(broken1 loc%d-%d) ",i,j);
			if(matrix[i][h] == '_')
				fprintf(problem, "(broken2 loc%d-%d) ",i,j);
			if(matrix[i][h] == '|')
				fprintf(problem, "(broken3 loc%d-%d) ",i,j);
			if(matrix[i][h] == '#')
				fprintf(problem, "(broken4 loc%d-%d) ",i,j);
			h+=2; k+=2; 
		}
	}
fprintf(problem, "\n");
for(int i=0;i<p-1;i++){
  fprintf(problem, "\n");
  for(int ii=0;ii<lenColumns[i]/2;ii++){
    fprintf(problem, "\n");
    for(int j=0;j < lenColumns[i]/2;j++){
      if(ii != j) fprintf(problem, "(line loc%d-%d loc%d-%d) ", i,ii,i,j);
    }
  }
}
fprintf(problem, "\n");
for(int i=0;i<maxColumns/2;i++){
  fprintf(problem, "\n");
  for(int ii=0;ii<p-1;ii++){
  fprintf(problem, "\n");
    for(int j=0;j<p-1;j++){
        if(j != ii) {
          if(i <= lenColumns[ii]/2-1 && i <= lenColumns[j]/2-1) fprintf(problem, "(column loc%d-%d loc%d-%d) ",ii,i,j,i); 
        }
    }
    }
  }
fprintf(problem, ")\n\t(:goal (and\n\t");
  for(int i=0;i<p-1;i++){
    fprintf(problem, "\n");
    for(int j=0;j<lenColumns[i]/2;j++)
      fprintf(problem, "(white loc%d-%d) ",i,j); }
	fprintf(problem, ")))\n");
	fprintf(domain," (define (domain lightsOut) (:requirements :strips :typing :equality) (:types location - object) (:predicates (red  ?y-x - location) (green  ?y-x - location) (blue  ?y-x - location) (white  ?y-x - location) (line ?y-x ?w-z - location) (column ?y-x ?w-z - location) (broken1  ?y-x - location) (broken2  ?y-x - location) (broken3  ?y-x - location) (broken4  ?y-x - location)) (:action click :parameters( ?y-x - location) :precondition ( and) :effect (and (when (not (broken1 ?y-x)) (and (when (red ?y-x) (and (not (red ?y-x)) (green ?y-x))) (when (green ?y-x) (and (not (green ?y-x)) (blue ?y-x))) (when (blue ?y-x) (and (not (blue ?y-x)) (white ?y-x))) (when (white ?y-x) (and (not (white ?y-x)) (red ?y-x))))) (forall (?w-z - location) (and (when (and (line ?y-x ?w-z) (not (= ?y-x ?w-z)) (not (broken3 ?w-z)) (not (broken4 ?w-z))) (and (when (red ?w-z) (and (not (red ?w-z)) (green ?w-z))) (when (green ?w-z) (and (not (green ?w-z)) (blue ?w-z))) (when (blue ?w-z) (and (not (blue ?w-z)) (white ?w-z))) (when (white ?w-z) (and (not (white ?w-z)) (red ?w-z))))) (when (and (column ?y-x ?w-z) (not (= ?y-x ?w-z)) (not (broken2 ?w-z)) (not (broken4 ?w-z))) (and (when (red ?w-z) (and (not (red ?w-z)) (green ?w-z))) (when (green ?w-z) (and (not (green ?w-z)) (blue ?w-z))) (when (blue ?w-z) (and (not (blue ?w-z)) (white ?w-z))) (when (white ?w-z) (and (not (white ?w-z)) (red ?w-z))))))))))");
	fclose(domain);
	fclose(problem);

	//to submit
	system("/tmp/dir/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
	//to run on chococino
	//system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
	//system("/home/software/planners/downward/fast-downward.py --alias lama-first domain9.pddl problem.pddl | grep -i click > out");
	system("grep -Eo '(click [a-zA-Z][a-zA-Z][a-zA-Z][0-9]+[0-9]+)' < out > out2");
	system("sed 's/^[0-9]* : (click loc\\([0-9]*\\)-\\([0-9]*\\))/\\(click \\1 \\2\\);/' out > outFile");
	system("sed '$ s/.$//' outFile > outFile2");
    system("cat outFile2");

	return 0;
}

