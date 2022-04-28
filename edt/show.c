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
/*
void shownonempty(text txt)
{
    if (txt == NULL || txt->length == 0)
    {
	fprintf(stderr, "There are already no ant lines the text!\n");
	return;
    }
    assert(txt->begin != NULL && txt->end != NULL);
    
    
}*/

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
