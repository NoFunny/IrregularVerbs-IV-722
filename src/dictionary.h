#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

struct dictionary {
	char *1form;
	char *2form;
	char *3form;
	char *rus;
};

int count_string(FILE *input);

struct dictionary *dictionary_init(int max_words_in_dictionary);

#endif