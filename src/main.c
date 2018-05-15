#include "interface.h"
#include "dictionary.h"

int main(void)
{
	flag = 0;
	FILE *input = fopen("dictionary.txt", "r");
	int n;

	if(input == NULL) {
		printf("Ошибка в считывании словаря\n");
		return 0;
	}

	unsigned int max_words_in_dictionary = count_string(input);
	dictionary *tab = dictionary_init(max_words_in_dictionary);

	dictionary_reading(tab, max_words_in_dictionary);

	if ((n = hallway()) == 0) {
		n = 1;
	} else if (n == 1) {
		n = 10;
	} else if (n == 2) {
		n = 15;
	} else if (n == 3) {
		n = 25;
	}

	int *value = (int*)malloc(sizeof(int)*max_words_in_dictionary);

	random_generator(max_words_in_dictionary, value, n);
	random_check(max_words_in_dictionary, value, n);

	enter_words(tab, value, n);

	dictionary_clean(tab, value);
	return 0;
}