#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "archivos.h"

int openFile(FILE **fp, char *mode, char* filename) {

	*fp = fopen(filename, mode);

	if(*fp == NULL) {
		return 1;		
	}

	return 0;
}

int closeFile(FILE *fp) {
	
	if(fp != NULL) {
		fclose(fp);
	}

	return 0;
}

char* readFile(FILE *fp) {
	
	char *string = (char *)malloc(100 * sizeof(char));
	memset(string, 0x00, sizeof(string));

	if(fscanf(fp, "%s\n", string) != 1) { /* Lee hasta 99 char + \0 */
		printf("Failed to read file\n");
		free(string);
		return NULL;
	}

	/*
	printf("%s\n", string);
	free(string);*/

	return string;
}

int writeFile(FILE *fp, char *string) {
	
	if(fp == NULL) {
		return 1; 	
	}

	fprintf(fp, "%s\n", string);

	return 0;
}

