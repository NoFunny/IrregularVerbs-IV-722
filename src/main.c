#include "dictionary.h"

#include "const_for_main_menu.h"

int main(void);
int main_menu(void);


int main(void)
{
	invalid_flag = 0, flag_0 = 0;
	FILE *input = fopen("dictionary.txt", "r");
	int n, intput, game = 0, lines, columns;

	setlocale( 0, "" );
	initscr();
	getmaxyx(stdscr, lines, columns);

	if(input == NULL) {
		printw("Ошибка в считывании словаря\n");
		return 0;
	}

	int max_words_in_dictionary = count_string(input);
	dictionary *tab = dictionary_init(max_words_in_dictionary);
	data *in_data = (data*)malloc(sizeof(data)*max_words_in_dictionary);

	dictionary_reading(tab, max_words_in_dictionary);

	if ((n = main_menu()) == 0) {
		n = 1;
	} else if (n == 1) {
		n = 10;
	} else if (n == 2) {
		n = 15;
	} else if (n == 3) {
		n = 25;
	}

	int *value = (int*)malloc(sizeof(int)*max_words_in_dictionary);
	int *bucket = (int*)malloc(sizeof(int)*max_words_in_dictionary);
	for (int i = 0; i < max_words_in_dictionary; i++) {
		bucket[i] = i+1;
	}

	random_generator(max_words_in_dictionary, value, bucket, n);

	scan_and_out(tab, in_data, value, n);

	while( game == 0) {

		mvwprintw(stdscr, (lines/2)+4, (columns-strlen(message_0_6)/2)/2, message_0_6);
		mvwprintw(stdscr, (lines/2)+6, ((columns/2)-strlen(message_0_7)), message_0_7);
		mvwprintw(stdscr, (lines/2)+6, ((columns/2)+3), message_0_8);
		mvwprintw(stdscr, (lines/2)+8, (columns-strlen(message_0_6)/2)/2, message_enter_0);
		scanw("%d", &intput);

		switch(intput) {
			case 1:
				random_generator(max_words_in_dictionary, value, bucket, n+invalid_flag);
				scan_and_out(tab, in_data, value, n+invalid_flag);
				break;
			case 2:
				game = 1;
				break;
		}

	}
	dictionary_clean(tab, value);
	endwin();

	return 0;
}

int main_menu(void)
{
	initscr();
	bool enter = false; // Переход в curses-режим.
	unsigned i, lines, columns, choice = 0;

	getmaxyx(stdscr, lines, columns); // Записываем максимальное кол-во строк и столбцов в переменные.
	mvwprintw(stdscr, (lines/2)-2, (columns-strlen(message_0_0)/2)/2, "%s", message_0_0); // Вывод message_0_0.
	mvwprintw(stdscr, (lines/2)-1, (columns-strlen(message_0_2)/2)/2, "%s", message_0_2);	// Вывод message_0_2.
	mvwprintw(stdscr, (lines/2)-0, (columns-strlen(message_0_4)/2)/2, "%s", message_0_4);	// Вывод message_0_4.
	getch(); // Ожидание нажатия какой-либо клавиши пользователем.

	curs_set(0); // Выключение курсора.
	keypad(stdscr, true); // Подключение функциональных клавишь.
	while (enter == false) {
		clear();
		for (i = 0; i < 4; i++) {
			mvwprintw(stdscr, (lines/2)-2, (columns-strlen(message_0_5)/2)/2, "%s", message_0_5);
			if(i == choice) {
				mvwaddch(stdscr, (lines/2)+i, (columns-strlen(menu[i])/2)/2-1, '>');
			} else {
				mvwaddch(stdscr, (lines/2)+i, (columns-strlen(menu[i])/2)/2-1, ' '); // Пробел для равновесия.
			}
			mvwprintw(stdscr, (lines/2)+i, (columns-strlen(menu[i])/2)/2, "%s", menu[i]);
		}
		// Получение пользовательского нажатия.
		switch (getch()) {
			case KEY_UP:
				if (choice) { // Если возиожно, переводим указатель вверх.
					choice--;
			}
			break;
			case KEY_DOWN:
				if (choice != 3) { // Если возможно, переводим узакатель вниз.
					choice++;
			}
			break;
			case 10:
				enter = true;;
		}
	}
	endwin(); // Выход из curses-режима. Обязательная команда.
	return choice;
}