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
	return lines_count + 1;
}

dictionary *dictionary_init(int max_words_in_dictionary)
{	
	if(max_words_in_dictionary > 0) {
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
	} else {
		return NULL;
	}
}		

dictionary *dictionary_reading(dictionary *tab, int max_words_in_dictionary)
{
	FILE *dictionary;
	dictionary = fopen("dictionary.txt", "r");
	if(dictionary == NULL) {
		printf("Ошибка в считывании словаря\n");
		return NULL;
	}
	char *buffer = (char*)malloc(50*sizeof(char));
	//char *russian = (char*)malloc(50*sizeof(char));
	char  *p[10];
	//size_t size = 50;

	for (int i = 0; i < max_words_in_dictionary; i++) {
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
	srand(time(NULL));
	for (int i = 0; i < amount; i++, flag_0++) {
		int x = rand() % (max_words_in_dictionary-flag_0);
		value[i] = bucket[x];
		bucket[x] = bucket[max_words_in_dictionary-flag_0];
		if (i >= amount-invalid_flag) {
			value[i] = invalid_input[i-(amount-invalid_flag)];
			flag_0--;
		}
	}
}

int scan_and_out(dictionary *tab, int value[], int amount)
{
	char buffer[100], *part[3], delim[7] = "/\\|,.; ", numbers[10] = "0123456789";
	
	int result[100][3], result_count, score = 0;

	int input = 0;

	for (int i = 0; i < amount; i++) {
		int flag_du = invalid_flag;

		initscr(); // IN curses-mode.
		clear(); // Clean window.


		printw("Введите 3 формы слова [%s]\nЧерез любой из разделителей [%s]\nЕсли не знаете слово ставьте [-]\n->", tab[value[i]].rus, delim);
		refresh(); // Input buffer.
		getstr(buffer); // Input str.
		printw("\n");

		if ((str_tok(buffer, delim, part) != 3) || (str_chr(buffer, numbers) != -1)) {
			while ((str_tok(buffer, delim, part) != 3) || (str_chr(buffer, numbers) != -1)) {
				printw("Ошибка при вводе значений. Попытайся снова.\n Enter: ");
				getstr(buffer); // Input str.
				printw("\n");
			}
		}
		
		result_count = 0;
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
		for (int j = 0; j < 3; j++) {
			if (result[i][j] == 0) {
				result_count++;
				score++;
			}
		}

		if (i < (amount-flag_du)) {
			if (result_count != 3) {
				invalid_input[flag_du] = value[i];
				invalid_flag++;
			}
		}
		if (i >= (amount-flag_du)) {
			if (result_count == 3) {
				invalid_input[amount-flag_du] = invalid_input[invalid_flag-1];
				invalid_flag--;
			}
		}
	}
	printw("Ваш результат: %d правильных из %d .\nВы хотите увидеть отчет об ошибках?\n1.Да\n2.Нет\n->", score, amount*3);
	scanw("%d", &input);

	switch(input) {
		case 1:
		clear(); // Clean win.
		for (int i = 0; i < amount; i++) {
			if (score != amount*3) {
				printw("Были найдены ошибки в формах слова - [%s]\n", tab[value[i]].rus);
				if(result[i][0] == 1) {
					printw("Вы ввели - %s\tПервая форма слова - %s\n", part[0], tab[value[i]].first_f);
				}
				if(result[i][1] == 1) {
					printw("Вы ввели - %s\tВторая форма слова - %s\n", part[1], tab[value[i]].second_f);
				}
				if(result[i][2] == 1) {
					printw("Вы ввели - %s\tТретья форма слова - %s\n", part[2], tab[value[i]].third_f);
				}
			} else {
				printw("Вы не сделали ошибок!\n");
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