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
	FILE *dictionary = fopen("dictionary.txt", "r");
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

void dictionary_clean(dictionary *tab, int value[])
{
	free(tab);
	free(value);
}