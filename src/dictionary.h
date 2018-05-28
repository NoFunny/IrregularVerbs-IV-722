#ifndef DICTIONARY
#define DICTIONARY

#include <time.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct dictionary {
	char *first_f;
	char *second_f;
	char *third_f;
	char *rus;
} dictionary;

unsigned int invalid_flag, flag_0;
int invalid_input[100];

// Вычисление кол-ва слов.
int count_string(FILE *input);
// Инициализация словаря.
dictionary *dictionary_init(int max_words_in_dictionary);
// Считывание словаря.
dictionary *dictionary_reading(dictionary *tab, int max_words_in_dictionary);
// Получение рандомных слов в массив value[].
void random_generator(int max_words_in_dictionary, int value[], int bucket[], int amount);
// Ввод слов.
int scan_and_out(dictionary *tab, int value[], int amount);
// Очистка всех элементов.
void dictionary_clean(dictionary *tab, int value[]);

#endif