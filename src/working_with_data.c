#include "string.h"
#include "working_with_data.h"
#include "const_for_scan_and_out.h"

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
		dictionary *tabl;
		tabl = (dictionary*)malloc(max_words_in_dictionary*sizeof(dictionary));
		for (int i = 0; i < max_words_in_dictionary; i++) {
			tabl[i].first_f = (char*)malloc(50*sizeof(char));
			tabl[i].second_f = (char*)malloc(50*sizeof(char));
			tabl[i].third_f = (char*)malloc(50*sizeof(char));
			tabl[i].rus = (char*)malloc(50*sizeof(char));
			for (int j = 0; j < 50; j++) {
				tabl[i].first_f[j] = 0;
			}
			for (int j = 0; j < 50; j++) {
				tabl[i].second_f[j] = 0;
			}
			for (int j = 0; j < 50; j++) {
				tabl[i].third_f[j] = 0;
			}
			for (int j = 0; j < 50; j++) {
				tabl[i].rus[j] = 0;
			}
		}
		if(tabl == NULL) {
			return NULL;
		}
		return tabl;
	} else {
		return NULL;
	}
}		

dictionary *dictionary_reading(dictionary *tabl, int max_words_in_dictionary)
{
	FILE *dictionary;
	dictionary = fopen("dictionary.txt", "r");
	if(dictionary == NULL) {
		printf("Ошибка в считывании словаря\n");
		return NULL;
	}
	char *buffer = (char*)malloc(50*sizeof(char));
	char  *p[10];

	for (int i = 0; i < max_words_in_dictionary; i++) {
		fscanf(dictionary, "%s", buffer);
		s_tok(buffer, ';', p);
		scopy(p[0], tabl[i].first_f);
		scopy(p[1], tabl[i].second_f);
		scopy(p[2], tabl[i].third_f);
		scopy(p[3], tabl[i].rus);
	}
	fclose(dictionary);
	free(buffer);

	return tabl;
}

int random_generator(int max_words_in_dictionary, int value[], int bucket[], int amount)
{
	if(max_words_in_dictionary >= amount) { 
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
		return flag_0;
	} else {
		return 0;
	}
}

int scan_and_out(dictionary *tabl, data *data, int value[], int amount)
{
	char buffer[1000], *session_tok[3], delim[7] = "/\\|,.; ", numbers[10] = "0123456789";
	
	int hitting_of_session, score = 0, lines, columns;

	for (int i = 0; i < amount; i++) {
		int flag_du = invalid_flag;

		initscr(); // IN curses-mode.
		getmaxyx(stdscr, lines, columns);
		clear(); // Clean window.

		mvwprintw(stdscr, (lines/2)-12, (columns - (strlen(message_1_0)+strlen(tabl[value[i]].rus))/2)/2, "Введите 3 формы слова [%s]", tabl[value[i]].rus);
		mvwprintw(stdscr, (lines/2)-10, (columns - (strlen(message_1_1)+sizeof(delim))/2)/2, "Через любой из разделителей [%s]", delim);
		mvwprintw(stdscr, (lines/2)-9, (columns - strlen(message_1_2)/2)/2, "Если вы не знаете слово, то просто поставьте [-]");
		mvwprintw(stdscr, (lines/2)-7, (columns - strlen(message_1_2)/2)/2, message_enter_1);

		refresh(); // Input buffer.
		getstr(buffer); // Input str.
		printw("\n");

		if ((str_tok(buffer, delim, session_tok) != 3) || (str_chr(buffer, numbers) != -1)) {
			while ((str_tok(buffer, delim, session_tok) != 3) || (str_chr(buffer, numbers) != -1)) {

				mvwprintw(stdscr, (lines/2)-7, (columns - strlen(message_1_3)/2)/2, " "); // Перемещение каретки.
				deleteln();
				deleteln();
				mvwprintw(stdscr, (lines/2)-7, (columns - strlen(message_1_3)/2)/2, message_1_3);
				mvwprintw(stdscr, (lines/2)-6, (columns - strlen(message_1_2)/2)/2, message_enter_1);

				refresh();

				getstr(buffer); // Input str.
				printw("\n");
			}
		}

		hitting_of_session = 0;
		if ((s_cmp(tabl[value[i]].first_f, session_tok[0]) == 0)) {
			data[i].hitting[0] = 0;
		} else {
			data[i].hitting[0] = 1;
			data[i].in_first_f = session_tok[0];
		}
		if ((s_cmp(tabl[value[i]].second_f, session_tok[1]) == 0)) {
			data[i].hitting[1] = 0;
		} else {
			data[i].hitting[1] = 1;
			data[i].in_second_f = session_tok[1];
		}
		if ((s_cmp(tabl[value[i]].third_f, session_tok[2]) == 0)) {
			data[i].hitting[2] = 0;
		} else {
			data[i].hitting[2] = 1;
			data[i].in_third_f = session_tok[2];
		}
		for (int j = 0; j < 3; j++) {
			if (data[i].hitting[j] == 0) {
				hitting_of_session++;
				score++;
			}
		}

		if (i < (amount-flag_du)) {
			if (hitting_of_session != 3) {
				invalid_input[flag_du] = value[i];
				invalid_flag++;
			}
		}
		if (i >= (amount-flag_du)) {
			if (hitting_of_session == 3) {
				invalid_input[amount-flag_du] = invalid_input[invalid_flag-1];
				invalid_flag--;
			}
		}
	}
	mvwprintw(stdscr, (lines/2)-4, (columns-strlen(message_1_4)/2)/2, "Ваш результат: %d правильных из %d.", score, amount*3);
	mvwprintw(stdscr, (lines/2)-2, (columns-strlen(message_1_5)/2)/2, message_1_5);
	mvwprintw(stdscr, (lines/2), ((columns/2)-strlen(message_1_6)-4), message_1_6);
	mvwprintw(stdscr, (lines/2), ((columns/2)+strlen(message_1_6)-1), message_1_7);
	mvwprintw(stdscr, (lines/2)+2, (columns - strlen(message_1_5)/2)/2, message_enter_1);
	refresh();

	if (score == max_words_in_dictionary*3) {
		mvwprintw(stdscr, (lines/2)-12, (columns - strlen(message_1_12)/2)/2, message_1_12);
		return 0;
	}

	int input;
	scanw("%d", &input);

	switch(input) {
		case 1:
			detailed_result = true;
			clear(); // Clean win.
			if (score == (amount*3)) {
				mvwprintw(stdscr, (lines/2)-12, (columns - strlen(message_1_8)/2)/2, message_1_8);
			} else {
				
				mvwprintw(stdscr, 1, (columns-10)/4*1, message_1_9);
				mvwprintw(stdscr, 1, (columns-10)/4*2, message_1_10);
				mvwprintw(stdscr, 1, (columns-10)/4*3, message_1_11);

				for (int i = 0; i < amount; i++) {
					mvwprintw(stdscr, i+3, 5, "#[%d] = [%s]", i+1, tabl[value[i]].rus);
					if(data[i].hitting[0] == 1) {
						mvwprintw(stdscr, i+3, (columns-10)/4*1, "[%s -/- %s]", data[i].in_first_f, tabl[value[i]].first_f);
					}
					if(data[i].hitting[1] == 1) {
						mvwprintw(stdscr, i+3, (columns-10)/4*2, "[%s -/- %s]", data[i].in_second_f, tabl[value[i]].second_f);
					}
					if(data[i].hitting[2] == 1) {
						mvwprintw(stdscr, i+3, (columns-10)/4*3, "[%s -/- %s]", data[i].in_third_f, tabl[value[i]].third_f);
					}
					refresh();
				}
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

int dictionary_clean(dictionary *tabl, int value[])
{
	free(tabl);
	free(value);
	value = NULL;
	tabl = NULL;
	if((value == NULL) && (tabl == NULL)) {
		return 1;
	} else {
		return 0;
	} 
}