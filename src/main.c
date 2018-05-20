#include "interface.h"
#include "dictionary.h"

int main(void)
{
	flag = 0, flag_0 = 0;
	FILE *input = fopen("dictionary.txt", "r");
	int i, n, intput, game = 0;

	if(input == NULL) {
		printf("Ошибка в считывании словаря\n");
		return 0;
	}

	int max_words_in_dictionary = count_string(input);
	dictionary *tab = dictionary_init(max_words_in_dictionary);

	dictionary_reading(tab, max_words_in_dictionary);

	if ((n = for_main()) == 0) {
		n = 1;
	} else if (n == 1) {
		n = 10;
	} else if (n == 2) {
		n = 15;
	} else if (n == 3) {
		n = 25;
	}

	int *value = (int*)malloc(sizeof(int)*max_words_in_dictionary);
	int *bucket = (int*)malloc(sizeof(int)*max_words_in_dictionary);
	for (i = 0; i < max_words_in_dictionary; i++) {
		bucket[i] = i+1;
	}

	random_generator(max_words_in_dictionary, value, bucket, n);

	enter_words(tab, value, n);

	while( game == 0) {
		printf("Вы хотите продолжить тест?\n1.Да\n2.Нет\n->");
		scanf("%d", &intput);
		switch(intput) {
			case 1:
				random_generator(max_words_in_dictionary, value, bucket, n+flag);
				enter_words(tab, value, n+flag);
				break;
			case 2:
				game = 1;
				break;
		}

	}
	dictionary_clean(tab, value);
	return 0;
}