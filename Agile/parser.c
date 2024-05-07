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

	for(int i=0;i<p-1;i++)
		for(int j=0;j<maxColumns/2;j++)
			fprintf( problem, "loc%d%d ", i,j);
	fprintf( problem, " - location)\n\t (:init\n\t");

	for(int i=0;i<p-1;i++){
		int h=0;
		int k=1;
		for(int j=0;j<maxColumns;j++){
			if(matrix[i][k] == 'W'){
				//fprintf(problem, "(button l%d c%d)\n\t",i,j);
				fprintf(problem, "(white loc%d%d) ",i,j);}
			if(matrix[i][k] == 'R'){
				//fprintf(problem, "(button l%d c%d)\n\t",i,j);
				fprintf(problem, "(red loc%d%d) ",i,j);}
			if(matrix[i][k] == 'B'){
				//fprintf(problem, "(button l%d c%d)\n\t",i,j);
				fprintf(problem, "(blue loc%d%d) ",i,j);}
			if(matrix[i][k] == 'G'){
				//fprintf(problem, "(button lox%dc%d)\n\t",i,j);
				fprintf(problem, "(green loc%d%d) ",i,j);}

			//if(matrix[i][h] == '-')
				//fprintf(problem, "(normal loc%d%d)\n\t",i,j);
			if(matrix[i][h] == '*')
				fprintf(problem, "(broken1 loc%d%d) ",i,j);
			if(matrix[i][h] == '_')
				fprintf(problem, "(broken2 loc%d%d) ",i,j);
			if(matrix[i][h] == '|')
				fprintf(problem, "(broken3 loc%d%d) ",i,j);
			if(matrix[i][h] == '#')
				fprintf(problem, "(broken4 loc%d%d) ",i,j);
			h+=2; k+=2; 
		}
	}
    fprintf(problem, "\n");
    fprintf(problem, "\n");

  int lenColumns[p-1];
  for(int i=0;i<p-1;i++) lenColumns[i] = strlen(matrix[i]);

for(int i=0;i<p-1;i++){
  fprintf(problem, "\n");
  for(int ii=0;ii<lenColumns[i]/2;ii++){
    fprintf(problem, "\n");
    for(int j=0;j < lenColumns[i]/2;j++){
      if(ii != j) fprintf(problem, "(line loc%d%d loc%d%d) ", i,ii,i,j);
    }
  }
}
  fprintf(problem, "\n");
  fprintf(problem, "\n");

for(int i=0;i<maxColumns/2;i++){
  fprintf(problem, "\n");
  for(int ii=0;ii<p-1;ii++){
  fprintf(problem, "\n");
    for(int j=0;j<p-1;j++){
      //if(matrix[j][i] != 0){
        if(j != ii) fprintf(problem, "(column loc%d%d loc%d%d) ",ii,i,j,i); 
      //}
    }
  }
}

fprintf(problem, ")\n\t(:goal (and\n\t");
	for(int i=0;i<p;i++){
		int h=0;
		int k=1;
		for(int j=0;j<maxColumns;j++){
			if(matrix[i][k] == 'W')
				fprintf(problem, "(white loc%d%d) ",i,j);
			if(matrix[i][k] == 'R')
				fprintf(problem, "(white loc%d%d) ",i,j);
			if(matrix[i][k] == 'B')
				fprintf(problem, "(white loc%d%d) ",i,j);
			if(matrix[i][k] == 'G')
				fprintf(problem, "(white loc%d%d) ",i,j);

			h+=2; k+=2; 
		}
	}
	fprintf(problem, ")))\n");
	fprintf(domain," (define (domain lightsOut) (:requirements :strips :typing :equality) (:types location - object) (:predicates (red  ?yx - location) (green  ?yx - location) (blue  ?yx - location) (white  ?yx - location) (line ?yx ?wz - location) (column ?yx ?wz - location) (broken1  ?yx - location) (broken2  ?yx - location) (broken3  ?yx - location) (broken4  ?yx - location)) (:action click :parameters( ?yx - location) :precondition ( and) :effect (and (when (not (broken1 ?yx)) (and (when (red ?yx) (and (not (red ?yx)) (green ?yx))) (when (green ?yx) (and (not (green ?yx)) (blue ?yx))) (when (blue ?yx) (and (not (blue ?yx)) (white ?yx))) (when (white ?yx) (and (not (white ?yx)) (red ?yx))))) (forall (?wz - location) (and (when (and (line ?yx ?wz) (not (= ?yx ?wz)) (not (broken3 ?wz)) (not (broken4 ?wz))) (and (when (red ?wz) (and (not (red ?wz)) (green ?wz))) (when (green ?wz) (and (not (green ?wz)) (blue ?wz))) (when (blue ?wz) (and (not (blue ?wz)) (white ?wz))) (when (white ?wz) (and (not (white ?wz)) (red ?wz))))) (when (and (column ?yx ?wz) (not (= ?yx ?wz)) (not (broken2 ?wz)) (not (broken4 ?wz))) (and (when (red ?wz) (and (not (red ?wz)) (green ?wz))) (when (green ?wz) (and (not (green ?wz)) (blue ?wz))) (when (blue ?wz) (and (not (blue ?wz)) (white ?wz))) (when (white ?wz) (and (not (white ?wz)) (red ?wz))))))))))");
	fclose(domain);
	fclose(problem);

	//to submit
	system("/tmp/dir/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
	//to run on chococino
	//system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl | grep -i click > out");
	system("grep -Eo '(click [a-zA-Z][[a-zA-Z][a-zA-Z]0-9][0-9])' < out > out2");
        system("sed 's/^[0-9]* : (click loc\\([0-9]\\)\\([0-9]\\))/\\(click \\1 \\2\\);/g' out > outFile");

	


	/*

	FILE *inputFile = fopen("out2", "r");
	FILE *outFile = fopen("outFile", "w");
	char line[100];
	int l_num,c_num;
	 while (fgets(line, sizeof(line), inputFile) != NULL){
		if (sscanf(line, "click loc%d%d", &l_num, &c_num) == 2){
		    fprintf(outFile, "(click %d%d);", l_num, c_num);}
		 else { fprintf(outFile, "%s", line);}}
	 fclose(inputFile);
	 fclose(outFile);
	 */
	

	system("sed '$ s/.$//' outFile > outFile2");
	//int lines = system("wc -l < outFile2 > lines");

    	FILE *pipe; char buffer[200]; int line;

    	pipe = popen("sed -n '$=' outFile2", "r");

   	if (fgets(buffer, 200, pipe) != NULL) line = atoi(buffer);
	pclose(pipe);

	if(line < 30) system("cat outFile2");
	else while(1);

	return 0;
}

