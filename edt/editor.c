/**
 * editor.c -- строковый текстовый редактор
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text/text.h"
#include "common.h"

#define MAXLINE 255

int main()
{
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;
    char *arg1;
    
    /* Создаем объект для представления текста */
    text txt = create_text();

    /* Цикл обработки команд */
    while (1) {
        printf("ed > ");
        
        /* Получаем команду */
        fgets(cmdline, MAXLINE, stdin);

        /* Извлекаем имя команды */
        if ((cmd = strtok(cmdline, " \n")) == NULL) {
            continue;
        }

        /* Распознаем поддерживаемую команду */
        
        /* Завершаем работу редактора */
        if (strcmp(cmd, "quit") == 0) {
            fprintf(stderr, "Bye!\n");
            break;
        }

        /* Загружаем содержимое файла, заданного параметром */
        if (strcmp(cmd, "load") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {
                load(txt, arg);
            }
            continue;
        }
	
        /* Выводим текст */
        if (strcmp(cmd, "show") == 0) {
            show(txt);
            continue;
        }

	if (strcmp(cmd, "snempty") == 0){
	    shownonempty(txt);
	    continue;
	}

	if (strcmp(cmd, "mwbb") == 0){
	    txt = mwbb(txt);
	    continue;
	}

	if (strcmp(cmd, "rc") == 0){
	    txt = rc(txt);
	    show(txt);
	    continue;
	}

	if (strcmp(cmd, "save") == 0) {
           if ((arg = strtok(NULL, " \n")) == NULL) {
               fprintf(stderr, "Usage: save filename\n");
           } else {
               save(txt, arg);
           }
            continue;
	}

	if (strcmp(cmd, "pos") == 0){
	    if (((arg = strtok(NULL, " \n")) == NULL) || ((arg1 = strtok(NULL, " \n")) == NULL )){
		fprintf(stderr, "No arguments\n");
	    }
	    else{
		int str = atoi(arg);
		int pos = atoi(arg1);
		mcursor(txt, str, pos);
		show(txt);
	    }
	    continue;
	}
	
        /* Если команда не известна */
        fprintf(stderr, "Unknown command: %s\n", cmd);
    }

    return 0;
}
