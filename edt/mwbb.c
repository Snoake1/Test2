#include <stdio.h>
#include "common.h"
#include "text/_text.h"
#include "text/text.h"


text mwbb(text txt) {
    int pos = txt->cursor->position;
    node *current = txt->begin;
    int i;
    int count = pos;
    int flag = 0;

    while(current) {
	if (txt->cursor->line == current) {
	    flag = 1;
	    break;
	}
	current = current->next;
    }
    if (flag == 0) {
	printf("No cursor in the text");
	return txt;
    }
    char *contents = current->contents;
    for (i=pos; i > 0; i--) {
	if (((contents[i] == ' ') || contents[i] == '\0') && (count >= 0))
	    break;
	if (contents[i-1] == ' ') break;
	
	/* Проверка на букву */
	if ((contents[i] >= 'A') && (contents[i] <= 'z')) {
	    count--;
	}
    }
    txt->cursor->position = count;

    return txt;
}
