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

