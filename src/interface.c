#include "const_for_main.h"
#include "interface.h"

int for_main(void)
{
	initscr();
	bool enter = false; // Переход в curses-режим.
	unsigned i, lines, columns, choice = 0;

	getmaxyx(stdscr, lines, columns); // Записываем максимальное кол-во строк и столбцов в переменные.
	mvwprintw(stdscr, (lines/2)-2, (columns-strlen(message_0_0))/2, "%s", message_0_0); // Вывод message_0_0.
	mvwprintw(stdscr, (lines/2)-1, (columns-strlen(message_0_2))/2, "%s", message_0_2);	// Вывод message_0_2.
	mvwprintw(stdscr, (lines/2)-0, (columns-strlen(message_0_4))/2, "%s", message_0_4);	// Вывод message_0_4.
	getch(); // Ожидание нажатия какой-либо клавиши пользователем.

	curs_set(0); // Выключение курсора.
	keypad(stdscr, true); // Подключение функциональных клавишь.
	while (enter == false) {
		clear();
		for (i = 0; i < 4; i++) {
			mvwprintw(stdscr, (lines/2)-2, (columns-strlen(message_1_0))/2, "%s", message_1_0);
			if(i == choice) {
				mvwaddch(stdscr, (lines/2)+i, (columns-strlen(menu[i]))/2-1, '>');
			} else {
				mvwaddch(stdscr, (lines/2)+i, (columns-strlen(menu[i]))/2-1, ' '); // Пробел для равновесия.
			}
			mvwprintw(stdscr, (lines/2)+i, (columns-strlen(menu[i]))/2, "%s", menu[i]);
		}
		// Получение пользовательского нажатия.
		switch (getch()) {
			case KEY_UP:
				if (choice) { // Если возиожно, переводим указатель вверх.
					choice--;
			}
			break;
			case KEY_DOWN:
				if (choice != 4) { // Если возможно, переводим узакатель вниз.
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

/*int for_enter_words(int amount)
{
	initscr();

	raw(); // Получили полный контроль над клавиатурой.
	keypad(stdscr, true); // Подключение функциональных клавишь.



	refresh();

	endwin();
	return 0;
}*/