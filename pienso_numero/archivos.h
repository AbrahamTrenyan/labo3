#ifndef _ARCHIVOS_H
#define _ARCHIVOS_H

int openFile(FILE **fp, char *mode, char* filename);

int closeFile(FILE *fp);

char* readFile(FILE *fp);

int writeFile(FILE *fp, char *string);

#endif
