#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

struct dictionary {
	char *first_f;
	char *second_f;
	char *third_f;
	char *rus;
};

int count_string(FILE *input);

struct dictionary *dictionary_init(int max_words_in_dictionary);

struct dictionary *dictionary_reading(struct dictionary *tab, int max_words_in_dictionary);

void dictionary_clean(struct dictionary *tab, int max_words_in_dictionary);

#endif