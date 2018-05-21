#include "string.h"
#include "dictionary.h"

int count_string(FILE * input)
{
	int lines_count = 0;

	while(!feof(input)) {
		if(fgetc(input) == '\n') {
			lines_count++;
		}
	}
	fclose(input);
	return lines_count+1;

}

dictionary *dictionary_init(int max_words_in_dictionary)
{
	dictionary *tab;
	tab = (dictionary*)malloc(max_words_in_dictionary*sizeof(dictionary));
	for (int i = 0; i < max_words_in_dictionary; i++) {
		tab[i].first_f = (char*)malloc(50*sizeof(char));
		tab[i].second_f = (char*)malloc(50*sizeof(char));
		tab[i].third_f = (char*)malloc(50*sizeof(char));
		tab[i].rus = (char*)malloc(50*sizeof(char));
		for (int j = 0; j < 50; j++) {
			tab[i].first_f[j] = 0;
		}
		for (int j = 0; j < 50; j++) {
			tab[i].second_f[j] = 0;
		}
		for (int j = 0; j < 50; j++) {
			tab[i].third_f[j] = 0;
		}
		for (int j = 0; j < 50; j++) {
			tab[i].rus[j] = 0;
		}
	}
	if(tab == NULL) {
		return NULL;
	}
	return tab;
}

dictionary *dictionary_reading(dictionary *tab, int max_words_in_dictionary)
{
	int i;
	FILE *dictionary;
	dictionary = fopen("dictionary.txt", "r");
	if(dictionary == NULL) {
		printf("There was an error reading the dictionary.");
		return NULL;
	}
	char *buffer = (char*)malloc(50*sizeof(char));
	char  *p[10];

	for (i = 0; i < max_words_in_dictionary; i++) {
		fscanf(dictionary, "%s", buffer);
		s_tok(buffer, ';', p);
		scopy(p[0], tab[i].first_f);
		scopy(p[1], tab[i].second_f);
		scopy(p[2], tab[i].third_f);
		scopy(p[3], tab[i].rus);
	}
	fclose(dictionary);
	free(buffer);

	return tab;
}

void random_generator(int max_words_in_dictionary, int value[], int bucket[], int amount)
{
	int i, x;

	srand(time(NULL));
	for (i = 0; i < amount; i++, flag_0++) {
		x = rand() % (max_words_in_dictionary-flag_0);
		value[i] = bucket[x];
		bucket[x] = bucket[max_words_in_dictionary-flag_0];
		if (i >= amount-flag) {
			value[i] = invalid_input[i-(amount-flag)];
			flag_0--;
		}
	}
}

int enter_words(dictionary *tab, int value[], int amount)
{
	int i, j, result[100][3], count = 0, input, score = 0;
	char buffer[100], numbers[10] = "0123456789", delim[7] = "/|\\,. ;", *part[3];
	
	for (i = 0; i < amount; i++) {
		int flag_du = flag;

		initscr(); // IN curses-mode.
		clear(); // Clean window.

		printw("Enter 3 word forms [%s] through any of the separator - [%s].\nIf you do not know the word, just type '-'.\n Enter: ", tab[value[i]].rus, delim);
		refresh(); // Input buffer.
		getstr(buffer); // Input str.
		//scanw("%s", buffer);
		printw("\n");

		if ((str_tok(buffer, delim, part) != 3) || (str_chr(buffer, numbers) != -1)) {
			while ((str_tok(buffer, delim, part) != 3) || (str_chr(buffer, numbers) != -1)) {
				printw("An error was encountered while entering values. Try it again.\n Enter: ");
				getstr(buffer); // Input str.
				printw("\n");
			}
		}
		
		count = 0;
		if ((s_cmp(tab[value[i]].first_f, part[0]) == 0)) {
			result[i][0] = 0;
		} else {
			result[i][0] = 1;
		}
		if ((s_cmp(tab[value[i]].second_f, part[1]) == 0)) {
			result[i][1] = 0;
		} else {
			result[i][1] = 1;
		}
		if ((s_cmp(tab[value[i]].third_f, part[2]) == 0)) {
			result[i][2] = 0;
		} else {
			result[i][2] = 1;
		}
		for (j = 0; j < 3; j++) {
			if (result[i][j] == 0) {
				count++;
				score++;
			}
		}

		if (i < (amount-flag_du)) {
			if (count != 3) {
				invalid_input[flag_du] = value[i];
				flag++;
			}
		}
		if (i >= (amount-flag_du)) {
			if (count == 3) {
				invalid_input[amount-flag_du] = invalid_input[flag-1];
				flag--;
			}
		}
	}
	printw("Yoy result: %d correct of %d .\nDo you want to see a list of errors?\n1.Yes\n2.No\n->", score, amount*3);
	scanw("%d", &input);

	switch(input) {
		case 1:
		clear(); // Clean win.
		for (i = 0; i < amount; i++) {
			if (score != amount*3) {
				printw("Найдены ошибки в формах слова - [%s]\n", tab[value[i]].rus);
				if(result[i][0] == 1) {
					printw("You enter - %s\tThe first form of a word - %s\n", part[0], tab[value[i]].first_f);
				}
				if(result[i][1] == 1) {
					printw("You enter - %s\tThe second form of a word - %s\n", part[1], tab[value[i]].second_f);
				}
				if(result[i][2] == 1) {
					printw("You enter - %s\tThe third form of a word - %s\n", part[2], tab[value[i]].third_f);
				}
			} else {
				printw("You do not have errors!\n");
			}
			printw("\n");
		}
		break;
		case 2:
			return 0;
		default:
			return 0;
	}
	endwin(); // EXIT curses-mode.
	return 0;
}				

void dictionary_clean(dictionary *tab, int value[])
{
	free(tab);
	free(value);
}