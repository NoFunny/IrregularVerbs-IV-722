#include "interface.h"
#include "dictionary.h"

int main(void)
{
	invalid_flag = 0, flag_0 = 0;
	FILE *input = fopen("dictionary.txt", "r");
	int n, intput, game = 0;

	setlocale( 0, "" );
	initscr();

	if(input == NULL) {
		printw("Ошибка в считывании словаря\n");
		return 0;
	}

	int max_words_in_dictionary = count_string(input);
	dictionary *tab = dictionary_init(max_words_in_dictionary);
	data *in_data = (data*)malloc(sizeof(data)*max_words_in_dictionary);

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
	for (int i = 0; i < max_words_in_dictionary; i++) {
		bucket[i] = i+1;
	}

	random_generator(max_words_in_dictionary, value, bucket, n);

	scan_and_out(tab, in_data, value, n);

	while( game == 0) {
		printw("Вы хотите продолжить тест?\n1.Да\n2.Нет\n->");
		scanw("%d", &intput);
		switch(intput) {
			case 1:
				random_generator(max_words_in_dictionary, value, bucket, n+invalid_flag);
				scan_and_out(tab, in_data, value, n+invalid_flag);
				break;
			case 2:
				game = 1;
				break;
		}

	}
	dictionary_clean(tab, value);
	endwin();

	return 0;
}