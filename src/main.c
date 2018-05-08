#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main(void)
{
	FILE *input = fopen("dictionary.txt", "r");
	int max_words_in_dictionary = count_string(input), n;

	if(input == NULL) {
		printf("Ошибка в считывании словаря\n");
		return 0;
	}

	dictionary *tab = dictionary_init(max_words_in_dictionary);

	dictionary_reading(tab, max_words_in_dictionary);

	printf("Какое кол-ва слов вы хотите увидеть ?\n Enter: ");
	scanf("%d", &n);
	int *value = (int*)malloc(sizeof(int)*max_words_in_dictionary);
	random_generator(max_words_in_dictionary, value, n);
	random_check(max_words_in_dictionary, value, n);

	enter_words(tab, value, n);

	dictionary_clean(tab, value);
	return 0;
}