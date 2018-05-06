#include <stdio.h>
#include "string.h"
#include "dictionary.h"

int main()
{
	FILE *input;
	input = fopen("dictionary.txt", "r");

	if(input == NULL) {
		printf("Ошибка в считывании словаря\n");
		return 0;
	}

	int max_words_in_dictionary = count_string(input);

	printf("%d\n", max_words_in_dictionary);

	struct dictionary *tab = dictionary_init(max_words_in_dictionary);

	dictionary_reading(tab, max_words_in_dictionary);

	return 0;
}