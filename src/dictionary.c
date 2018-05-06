#include "dictionary.h"
#include "string.h"

int count_string(FILE * input)
{
	int lines_count = 0;

	while( !feof(input)) {
		if(fgetc(input) == '\n') {
			lines_count++;
		}
	}
	fclose(input);
	return lines_count+1;

}

struct dictionary *dictionary_init(int max_words_in_dictionary)
{
	printf("Функция dictionary_init\n");
	struct dictionary *tab;
	tab = (struct dictionary*)malloc(max_words_in_dictionary*sizeof(struct dictionary));
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

struct dictionary *dictionary_reading(struct dictionary *tab, int max_words_in_dictionary)
{
	printf("Функция dictionary_reading\n");
	FILE *dictionary;
	dictionary = fopen("dictionary.txt", "r");
	if(dictionary == NULL) {
		printf("Ошибка в считывании словаря");
		return 0;
	}
	char *buffer = (char*)malloc(50*sizeof(char));
	char **p;

	printf("max_words_in_dictionary = %d\n", max_words_in_dictionary);

	for (int i = 0; i < max_words_in_dictionary; i++) {
		fscanf(dictionary, "%s", buffer);
		printf("buffer(%d) = %s\n", i, buffer);
		p = stok(buffer, ';');
		scopy(p[0], tab[i].first_f);
		scopy(p[1], tab[i].second_f);
		scopy(p[2], tab[i].third_f);
		scopy(p[3], tab[i].rus);
		printf("1 form(%d) = %s\n2 form(%d) = %s\n3 form(%d) = %s\nrus(%d) = %s\n", i, tab[i].first_f, i, tab[i].second_f, i, tab[i].third_f, i, tab[i].rus);
	}
	stok_free(p);
	fclose(dictionary);
	free(buffer);

	return tab;
}


void dictionary_clean(struct dictionary *tab, int max_words_in_dictionary)
{
	for (int i = 0; i < max_words_in_dictionary; i++) {

		free(tab[i].first_f);
		free(tab[i].second_f);
		free(tab[i].third_f);
		free(tab[i].rus);
	}
	free(tab);
}

