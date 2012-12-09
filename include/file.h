#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef struct strfile{
	int i;
	int j;
	struct strfile * suiv;
} StrFile;

typedef StrFile File;

File * nouvelleFile();
File * enfiler(int, int, File *);
File * defiler(File *);
int fileEstVide(File *);

#endif
