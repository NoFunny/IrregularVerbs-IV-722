#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct dictionary {
	char *first_f;
	char *second_f;
	char *third_f;
	char *rus;
} dictionary;

// Вычисление кол-ва слов.
int count_string(FILE *input);
// Инициализация словаря.
dictionary *dictionary_init(int max_words_in_dictionary);
// Считывание словаря.
dictionary *dictionary_reading(dictionary *tab, int max_words_in_dictionary);
// Получение рандомных слов в массив value[]. // Проверка каждого слова на уникальность.
int random_generator(int max_words_in_dictionary, int value[], int amount);
int random_check(int max_words_in_dictionary, int value[], int amount);
// Ввод слов.
int enter_words(dictionary *tab, int value[], int amount);
// Очистка всех элементов.
void dictionary_clean(dictionary *tab, int value[]);

#endif