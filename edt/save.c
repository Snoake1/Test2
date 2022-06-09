#include <stdio.h>
#include "text/text.h"
#include "text/_text.h"
#include "common.h"

void save(text txt, char *filename)
{
    FILE *f;
    
    if(txt == NULL || txt->length == 0)
    {
	fprintf(stderr, "The text doesn`t exist\n");
	return;
    }
    
    if ((f = fopen(filename, "w")) == NULL)
    {
    fprintf(stderr, "The file %s cannot be written\n", filename);
	return;
    }

    node * current = txt->begin; 

    do
    {
    fprintf(f, "%s\n", current->contents);
    current = current->next;
    } while(current);
    fclose(f);
}
