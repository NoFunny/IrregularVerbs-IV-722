#ifndef DICTIONARY
#define DICTIONARY

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct dictionary {
	char *first_f;
	char *second_f;
	char *third_f;
	char *rus;
} dictionary;

unsigned int flag, flag_0;
//int array_of_visit[100];
int invalid_input[100];

// Вычисление кол-ва слов.
int count_string(FILE *input);
// Инициализация словаря.
dictionary *dictionary_init(int max_words_in_dictionary);
// Считывание словаря.
dictionary *dictionary_reading(dictionary *tab, int max_words_in_dictionary);
// Получение рандомных слов в массив value[]. // Проверка каждого слова на уникальность.
void random_generator(int max_words_in_dictionary, int value[], int bucket[], int amount);
//void random_check(int max_words_in_dictionary, int value[], int amount);
// Ввод слов.
int enter_words(dictionary *tab, int value[], int amount);
// Очистка всех элементов.
void dictionary_clean(dictionary *tab, int value[]);

#endif