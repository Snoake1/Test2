#include <stdio.h>
#include "text/_text.h"
#include "text/text.h"
#include "common.h"

text rc(text txt){

    unsigned long pos = 1; 
    node *current = txt->begin;
    int flag = 0;

    node *prevstr;
    node *nextstr;


    while (current){
	if (txt->cursor->line == current){
	    flag = 1;
	    break;
	}
	current = current->next;
	prevstr = current->previous;
	nextstr = current->next;
	pos++;
    }
    if (flag == 0){
	fprintf(stderr, "No cursor in string\n");
	return txt;
    }
    
    if (pos == 1){
	free(current);
	txt->begin = current->next;
	txt->length--;
        mcursor(txt, 0, 0);
	return txt;
    }
    
    if (pos == txt->length){
	free(current);
	current=current->previous;
	current->next = NULL;
	txt->length--;
	mcursor(txt, 0, 0);
	return txt;
    }
    
    free(current);
    current = current->next;
    current->previous = prevstr;
    current = current->previous;
    current->next = nextstr;
    txt->length--;
    mcursor(txt, 0, 0);
    return txt;
}
