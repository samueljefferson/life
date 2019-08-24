// Conway's Game of Life

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <ncurses.h>
#include <time.h>

int main() {
	initscr();
	cbreak();
	curs_set(0);

	int width = 80;
	int height = 24;
	int buffer [height][width];

	int i = 0;
	int j = 0;
	int k = -1;
	int l = -1;
	int x = -1;
	int y = -1;

	// screen with random life
	srand(time(NULL));
	for (i = 0; i < height-1; i++) {
		for (j = 0; j < width-1; j++) {

			int number = rand() % 10;
			if (number < 3) {
				mvaddch(i,j, '*');
			}
		}
	}

	refresh();
	sleep(1);

	while (1) {
		// count is initially the number of neighbors
		// then it is 1 if the cell will be alive next turn
		// and 0 if the cell will be dead
		int count = 0;

		for (i = 0; i < height; i++) {
			for (j=0; j < width; j++) {
				count = 0;

				// check adjacent cells for life
				for (k = -1; k < 2; k++) {
					for (l = -1; l < 2; l++) {
						y = i + k;
						x = j + l;
						// make sure the cell being checked is within bounds
						if (y >= 0 && y < (height - 1) && x >= 0 && x < (width - 1)) {
							// ignore current cell
							if (k == l && l == 0) {}
							 else {
								 if (mvinch(y,x) == '*'){
								 	count++;
								 }
							}

						}
					}
				}
				buffer[i][j] = count;

				// have buffer show if cell will be alive or dead
				if (mvinch(i,j) == '*') {
					if (count == 2 || count == 3) {
						count = 1;
					} else {
						count = 0;
					}
				} else {
					if (count == 3) {
						count = 1;
					} else {
						count = 0;
					}
				}
				buffer[i][j] = count;
			}
		}

		// show contents of buffer
		for (i = 0; i < height; i++) {
			for (j=0; j < width; j++) {
				count = buffer[i][j];
				if (count == 1) {
					mvaddch(i,j, '*');
				} else {
					mvaddch(i,j, ' ');
				}
			}
		}
		refresh();
		sleep(1);
	}
	return 0;
}
