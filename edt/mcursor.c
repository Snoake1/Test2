#include <stdio.h>
#include "text/text.h"
#include "text/_text.h"
#include "common.h"

void mcursor(text txt, int str, int pos){
    node *current = txt->begin;
    if (pos >= 0){
	txt->cursor->position = pos;
    }
    
    else{
	txt->cursor->position = 0;
    }
    
    int p = 1;
    
    if (str > 0){
	int ln = txt->length;
	    if (str > ln){
		str = ln;
	    }
	    
	while(current)
	{
	    if(p == str){
		txt->cursor->line = current;
		break;
	    }
	    current = current->next;
	    p++;
	}
    }
    
    else
    {
	txt->cursor->line = current;
    }
}
