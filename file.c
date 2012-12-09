#include "include/file.h"

File * nouvelleFile()
{
	return NULL;
}

File * enfiler(int i, int j, File * f)
{
	StrFile * s = (StrFile*)malloc(sizeof(StrFile));
	s->i = i;
	s->j = j;
	s->suiv = NULL;
	
	if(fileEstVide(f))
	{
		f = s;
	}
	else
	{
		File * q = f;
		while(q->suiv != NULL)
			q = q->suiv;
			
		q->suiv = s;
	}
	return f;
}

File * defiler(File * f)
{
	if(fileEstVide(f) || f->suiv == NULL)
		return NULL;
	else
	{
		StrFile * save = f;
		f = f->suiv;
		free(save);
	}
	return f;
}

int fileEstVide(File * f)
{
	if(f == NULL)
		return 1;
	else
		return 0;
}
