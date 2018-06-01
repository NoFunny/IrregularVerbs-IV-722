#ifndef WORKING_WITH_DATA
#define WORKING_WITH_DATA

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

typedef struct dictionary {
	char *first_f;
	char *second_f;
	char *third_f;
	char *rus;
} dictionary;

typedef struct data {
	char *in_first_f;
	char *in_second_f;
	char *in_third_f;
	unsigned int hitting[3];
} data;

unsigned int max_words_in_dictionary;
unsigned int invalid_flag, flag_0;
unsigned int invalid_input[100];

bool detailed_result;

// Вычисление кол-ва слов.
int count_string(FILE *input);
// Инициализация словаря.
dictionary *dictionary_init(int max_words_in_dictionary);
// Считывание словаря.
dictionary *dictionary_reading(dictionary *tabl, int max_words_in_dictionary);
// Получение рандомных слов в массив value[].
int random_generator(int max_words_in_dictionary, int value[], int bucket[], int amount);
// Ввод слов.
int scan_and_out(dictionary *tabl, data *data, int value[], int amount);
// Очистка всех элементов.
int dictionary_clean(dictionary *tabl, int value[]);

#endif