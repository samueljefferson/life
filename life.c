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
	curs_set(0);

	int width = 80;
	int height = 24;
	int buffer [height][width];

	int i = 0;
	int j = 0;

	// screen with random life
	srand(time(NULL));
	for (i = 0; i < height-1; i++) {
		for (j = 0; j < width-1; j++) {

			int number = rand() % 10;
			if (number < 5) {
				mvaddch(i,j, '*');
			}
		}
	}
	refresh();

	while (1) {
		// count is initially the number of neighbors
		// then it is 1 if the cell will be alive next turn
		// and 0 if the cell will be dead
		int count = 0;

		for (i = 0; i < height; i++) {
			for (j=0; j < width; j++) {
				count = 0;

				// top row
				if (i == 0) {
					// top left
					if (j == 0) {
						if (mvinch(0,1) == '*') {
							count++;
						}
						if (mvinch(1,0) == '*') {
							count++;
						}
					} else if (j == width - 1) {
						// top right
						if (mvinch(0,width-2) == '*') {
							count++;
						}
						if (mvinch(1,width-1) == '*') {
							count++;
						}
					} else {
						// top middle
						// left
						if (mvinch(i,j-1) == '*') {
							count++;
						}
						// right
						if (mvinch(i,j+1) == '*') {
							count++;
						}
						// bottom
						if (mvinch(i+1,j) == '*') {
							count++;
						}
					}
				} else if (i == height - 1) {
					// bottom row

					// bottom left
					if (j == 0) {
						if (mvinch(height-1,width-2) == '*') {
							count++;
						}
						if (mvinch(height-2,width-1) == '*') {
							count++;
						}
					} else if (j == width - 1) {
						// bottom right
						if (mvinch(height-1,1) == '*') {
							count++;
						}
						if (mvinch(height-2,0) == '*') {
							count++;
						}
					} else {
						// bottom middle
						// left
						if (mvinch(i,j-1) == '*') {
							count++;
						}
						// right
						if (mvinch(i,j+1) == '*') {
							count++;
						}
						// top
						if (mvinch(i-1,j) == '*') {
							count++;
						}
					}
				} else if (j == 0) {
					// left column

					// top
					if (mvinch(i-1,j) == '*') {
						count++;
					}
					// right
					if (mvinch(i,j+1) == '*') {
						count++;
					}
					// bottom
					if (mvinch(i+1,j) == '*') {
						count++;
					}
				} else if (j == width - 1) {
					// right column
					// top
					if (mvinch(i-1,j) == '*') {
						count++;
					}
					// left
					if (mvinch(i,j-1) == '*') {
						count++;
					}
					// bottom
					if (mvinch(i+1,j) == '*') {
						count++;
					}
				} else {
					// middle

					// UL
					if (mvinch(i-1,j-1) == '*'){
						count++;
					}
					// U
					if (mvinch(i-1,j) == '*'){
						count++;
					}
					// UR
					if (mvinch(i-1,j+1) == '*'){
						count++;
					}
					// L
					if (mvinch(i,j-1) == '*'){
						count++;
					}
					// R
					if (mvinch(i,j+1) == '*'){
						count++;
					}
					// BL
					if (mvinch(i+1,j-1) == '*'){
						count++;
					}
					// B
					if (mvinch(i+1,j) == '*'){
						count++;
					}
					// BR
					if (mvinch(i+1,j+1) == '*'){
						count++;
					}
				}
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
