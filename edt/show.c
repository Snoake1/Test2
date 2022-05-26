/**
 * show.c -- реализует команду вывода хранимого текста на экран
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "text/text.h"
#include "text/_text.h"

static void show_line(int index, char *contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt)
{
    /* Применяем функцию show_line к каждой строке текста */
    process_forward(txt, show_line, NULL);
}


void shownonempty(text txt)
{   
    if (txt == NULL || txt->length == 0)
    {
	fprintf(stderr, "There are already no any lines the text!\n");
	return;
    }

    int cursor_position = -1;

    assert(txt->begin != NULL && txt->end != NULL);

    node *current = txt->begin;
    int index = 0;
    int stind = 0;
	
    while(current){
    if (strcmp(current->contents, "") != 0)
        {
	    if (txt->cursor->line == current)
		cursor_position = txt->cursor->position;
	    else
		cursor_position = -1;
	show_line(index, current->contents, cursor_position, NULL);
	
	current = current->next;
	index++;
	stind++;
        }
    else
        {
	current = current->next;
	index++;
	}
    }

}

/**
 * Выводит содержимое указанного файла на экран
 */
static void show_line(int index, char *contents, int cursor, void *data)
{
    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);
    
    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(data);
    int baseln = strlen(contents) - 1;
    int ln = baseln > cursor ? baseln: cursor;

    if (cursor != -1)
    {
	int i = 0;
        while (i <= ln)
	{
		if (i == cursor){
		    printf("|");
		}
	        if (i <= baseln){
		    printf("%c", contents[i]);
		}
	i++;
	}
    }
    else{
    /* Выводим строку на экран */
    printf("%s", contents);
    }
    printf("\n");
}
