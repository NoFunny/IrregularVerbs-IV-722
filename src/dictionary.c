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
		tab[i].1form = (char*)malloc(20*sizeof(char));
		tab[i].2form = (char*)malloc(20*sizeof(char));
		tab[i].3form = (char*)malloc(20*sizeof(char));
		tab[i].rus = (char*)malloc(20*sizeof(char));
		for (int j = 0; j < 20; j++) {
			tab[i].1form[j] = 0;
		}
		for (int j = 0; j < 20; j++) {
			tab[i].2form[j] = 0;
		}
		for (int j = 0; j < 20; j++) {
			tab[i].3form[j] = 0;
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

