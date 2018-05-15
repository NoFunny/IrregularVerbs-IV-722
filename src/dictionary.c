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
		tab[i].first_f = (char*)malloc(20*sizeof(char));
		tab[i].second_f = (char*)malloc(20*sizeof(char));
		tab[i].third_f = (char*)malloc(20*sizeof(char));
		tab[i].rus = (char*)malloc(20*sizeof(char));
		for (int j = 0; j < 20; j++) {
			tab[i].first_f[j] = 0;
		}
		for (int j = 0; j < 20; j++) {
			tab[i].second_f[j] = 0;
		}
		for (int j = 0; j < 20; j++) {
			tab[i].third_f[j] = 0;
		}
		for (int j = 0; j < 20; j++) {
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
		printf("Ошибка в считывании словаря");
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

void random_generator(int max_words_in_dictionary, int value[], int amount)
{
	int i;

	srand(time(NULL));
	for (i = 0; i < amount; i++) {
		value[i] = rand() % max_words_in_dictionary;
		if (i >= amount-flag) {
			value[i] = invalid_input[i-(amount-flag)];
		}
	}
}

void random_check(int max_words_in_dictionary, int value[], int amount)
{
	int i, j;

	for (i = 0; i < amount; i++) {
		for (j = 0; j < amount; j++) {
			if ((value[i] == value[j]) && (i != j)) {
				do {
					value[i] = rand() % max_words_in_dictionary;
				} while (value[i] == value[j]);
				return random_check(max_words_in_dictionary, value, amount);
			}
		}
	}
}

int enter_words(dictionary *tab, int value[], int amount)
{
	int i, j, result[100][3], count = 0, input;
	char buffer[100], delim[6] = "/|\\,.;", *part[3];

	for (i = 0; i < amount; i++) {
		printf("Введите 3 формы слова [%s] через любой из разделителей - [%s].\nЕсли вы не знаете слово, просто введите '-'.\n Enter: ", tab[value[i]].rus, delim);
		scanf("%s", buffer);
		printf("\n");

		if (str_tok(buffer, delim, part) != 3) {
			while (str_tok(buffer, delim, part) != 3) {
				printf("При вводе значений была обнаружена ошибка. Попробуйте снова.\n Enter: ");
				scanf("%s", buffer);
				printf("\n");
			}
		}
		
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
			}
		}

		if (count != 3) {
			invalid_input[flag] = value[i];
			flag++;
		}
	}
	printf("Ваш результат: %d правильных из %d .\n1.Cписок ошибок\n2.Выход из функции(пока что)\n->", count, amount*3);
	scanf("%d", &input);

	switch(input) {
		case 1:
		for (i = 0; i < amount; i++) {
			if(count < 3) {
				printf("Найдены ошибки в формах слова - %s\n", tab[value[i]].rus);
				if(result[i][0] == 1) {
					printf("Вы ввели - %s\tПервая форма слова - %s\n", part[0], tab[value[i]].first_f);
				}
				if(result[i][1] == 1) {
					printf("Вы ввели - %s\tВторая форма слова - %s\n", part[1], tab[value[i]].second_f);
				}
				if(result[i][2] == 1) {
					printf("Вы ввели - %s\tТретья форма слова - %s\n", part[2], tab[value[i]].third_f);
				}
			}
			printf("\n");
		}
		break;
		case 2:
			return 0;
			break;
		default:
			return 0;
			break;
	}
	
	return 0;
}				

void dictionary_clean(dictionary *tab, int value[])
{
	free(tab);
	free(value);
}