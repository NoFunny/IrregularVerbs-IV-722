#include "string.h"
#include "dictionary.h"
#include "in_out_words.h"

int enter_words(dictionary *tab, int value[], int amount)
{
	int i, j, result[100][3], count = 0, score = 0;
	char buffer[100], numbers[10] = "0123456789", delim[7] = "/|\\,. ;", *part[3];
	
	for (i = 0; i < amount; i++) {
		int flag_du = flag;

		initscr(); // IN curses-mode.
		clear(); // Clean window.

		printw("Enter 3 word forms [%s] through any of the separator - [%s].\nIf you do not know the word, just type '-'.\n Enter: ", tab[value[i]].rus, delim);
		refresh(); // Input buffer.
		getstr(buffer); // Input str.
		printw("\n");

		if ((str_tok(buffer, delim, part) != 3) || (str_chr(buffer, numbers) != -1)) {
			while ((str_tok(buffer, delim, part) != 3) || (str_chr(buffer, numbers) != -1)) {
				printw("An error was encountered while entering values. Try it again.\n Enter: ");
				getstr(buffer); // Input str.
				printw("\n");
			}
		}

		count = 0;
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
				score++;
			}
		}

		if (i < (amount-flag_du)) {
			if (count != 3) {
				invalid_input[flag_du] = value[i];
				flag++;
			}
		}
		if (i >= (amount-flag_du)) {
			if (count == 3) {
				invalid_input[amount-flag_du] = invalid_input[flag-1];
				flag--;
			}
		}
	}
	printw("You result: %d correct of %d .", score, amount+1);
	endwin(); // EXIT curses-mode.
	return 0;
}

/*int result(dictionary *tab, int value[], int amount)
{
	int input, i;
	
	printw("Do you want to see a list of errors?\n1.Yes\n2.No\n->");
	scanw("%d", &input);

	switch(input) {
		case 1:
		clear(); // Clean win.
		for (i = 0; i < amount; i++) {
			if (score != amount*3) {
				printw("Найдены ошибки в формах слова - [%s]\n", tab[value[i]].rus);
				if(result[i][0] == 1) {
					printw("You enter - %s\tThe first form of a word - %s\n", part[0], tab[value[i]].first_f);
				}
				if(result[i][1] == 1) {
					printw("You enter - %s\tThe second form of a word - %s\n", part[1], tab[value[i]].second_f);
				}
				if(result[i][2] == 1) {
					printw("You enter - %s\tThe third form of a word - %s\n", part[2], tab[value[i]].third_f);
				}
			} else {
				printw("You do not have errors!\n");
			}
			printw("\n");
		}
		break;
		case 2:
			return 0;
		default:
			return 0;
	}
	endwin(); // EXIT curses-mode.
	return 0;
}		*/