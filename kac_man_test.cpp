#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <ncurses.h>
#include <time.h>

#define scr_max_y 33
#define main_max_x 42
#define game_max_x 30
#define game_score_max_x 12
#define map_view_max_x 30
#define map_select_max_x 12

enum ObjectStatus {EMPTY = 0, WALL = 1, KAC_MAN = 2, GHOST = 3, KAC_DOT = 4, POW_DOT = 5};

WINDOW *main_scr;
WINDOW *game_scr;
WINDOW *game_score_scr;
WINDOW *map_view_scr;
WINDOW *map_select_scr;
WINDOW *option_scr;

int kac_x = 1;
int kac_y = 1;
int kac_x_dir = 0;
int kac_y_dir = 0;
int kac_speed = 1;

int temp_board[31][28] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,3,3,3,3,3,0,0,1,1,0,0,4,4,4,4,4,5,5,5,5,5,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
	{1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
	{1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
	{1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void init_ncurses();
void frame_timer();
void print_main_scr();
void print_game_scr();
void print_option_scr();

void init_ncurses(){
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(1, 7, 0);
	init_pair(2, 3, 0);
	init_pair(3, 1, 0);
	init_pair(4, 3, 0);
	init_pair(5, 3, 0);
}

void frame_timer(){
	time_t start, now;
	start = clock();
	while(1){
		now = clock();
		if((double)(now - start) / (double)(CLOCKS_PER_SEC) >= 0.0166){
			break;
		}
	}
}

void print_main_scr(){
	int end = 1, cursor = 1;
	init_ncurses();
	main_scr = newwin(scr_max_y, main_max_x, 0, 0);
	while(end == 1){
	frame_timer();
	wborder(main_scr, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(main_scr, 6 , 2, "|  /  |\\      /|      /\\      |\\     |");
	mvwprintw(main_scr, 7 , 2, "| /   | \\    / |     /  \\     | \\    |");
	mvwprintw(main_scr, 8 , 2, "|/  ==|  \\  /  |    /    \\    |  \\   |");
	mvwprintw(main_scr, 9 , 2, "|\\  ==|   \\/   |   /\\/\\/\\/\\   |   \\  |");
	mvwprintw(main_scr, 10, 2, "| \\   |        |  /        \\  |    \\ |");
	mvwprintw(main_scr, 11, 2, "|  \\  |        | /          \\ |      |");
	mvwprintw(main_scr, 16, 16, "GAME START");
	mvwprintw(main_scr, 20, 16, "FIX OPTION");
	mvwprintw(main_scr, 24, 16, "LOAD  MAPS");
	mvwprintw(main_scr, 27, 8, "PRESS 'space bar' to select");
	mvwprintw(main_scr, 12 + 4 * cursor, 1, "===============");
	mvwprintw(main_scr, 12 + 4 * cursor, 26, "===============");
	wrefresh(main_scr);
	int input = getch();
	switch(input){
		case KEY_UP:
			if(cursor > 1){
				mvwprintw(main_scr, 12 + 4 * cursor, 1, "               ");
				mvwprintw(main_scr, 12 + 4 * cursor, 26, "               ");
				cursor--;
			}
			continue;
		case KEY_DOWN:
			if(cursor < 3){
				mvwprintw(main_scr, 12 + 4 * cursor, 1, "               ");
				mvwprintw(main_scr, 12 + 4 * cursor, 26, "               ");
				cursor++;
			}
			continue;
		case ' ':
			clear();
			if(cursor == 1){
				print_game_scr();
			}
			if(cursor == 2){
				print_option_scr();
			}
		case 'q':
			endwin();
			end++;
			break;
	}
	}
}

void print_game_scr(){
	int end = 1, timer = 0;
	while(end == 1){
	frame_timer();
	timer++;
	game_scr = newwin(scr_max_y, game_max_x, 0, 0);
	game_score_scr = newwin(scr_max_y, game_score_max_x, 0, game_max_x);
	wborder(game_scr, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(game_score_scr, '|', '|', '-', '-', '+', '+', '+', '+');
	for(int y = 0; y < 31; y++){
		for(int x = 0; x < 28; x++){
			if(temp_board[y][x] == EMPTY){
				attron(COLOR_PAIR(1));
				mvwprintw(game_scr, y + 1, x + 1, " ");
			}
			else if(temp_board[y][x] == WALL){
				attron(COLOR_PAIR(1));
				mvwprintw(game_scr, y + 1, x + 1, "W");
			}
			else if(temp_board[y][x] == KAC_MAN){
				attron(COLOR_PAIR(2));
				mvwprintw(game_scr, y + 1, x + 1, "K");
			}
			else if(temp_board[y][x] == GHOST){
				attron(COLOR_PAIR(3));
				mvwprintw(game_scr, y + 1, x + 1, "G");
			}
			else if(temp_board[y][x] == KAC_DOT){
				attron(COLOR_PAIR(4));
				mvwprintw(game_scr, y + 1, x + 1, "d");
			}
			else if(temp_board[y][x] == POW_DOT){
				attron(COLOR_PAIR(5));
				mvwprintw(game_scr, y + 1, x + 1, "D");
			}
		}
	}
	wrefresh(game_scr);
	wrefresh(game_score_scr);
	if((timer%(15 - kac_speed)) == 0 && (temp_board[kac_y+kac_y_dir][kac_x+kac_x_dir] != WALL)){
		temp_board[kac_y][kac_x] = EMPTY;
		kac_x = kac_x + kac_x_dir;
		kac_y = kac_y + kac_y_dir;
		temp_board[kac_y][kac_x] = KAC_MAN;
	}
	int input = getch();
	switch(input){
		case 'q':
			clear();
			end++;
			print_main_scr();
			break;
		case KEY_UP:
			kac_y_dir = -1;
			kac_x_dir = 0;
			continue;
		case KEY_RIGHT:
			kac_y_dir = 0;
			kac_x_dir = 1;
			continue;
		case KEY_DOWN:
			kac_y_dir = 1;
			kac_x_dir = 0;
			continue;
		case KEY_LEFT:
			kac_y_dir = 0;
			kac_x_dir = -1;
			continue;
	}
	}
	
}

void print_option_scr(){
	int end = 1, cursor = 1;
	option_scr = newwin(scr_max_y, main_max_x, 0, 0);
	while(end == 1){
		wborder(option_scr, '|', '|', '-', '-', '+', '+', '+', '+');
		mvwprintw(option_scr, 2, 1, "PRESS 'space bar' to select & PRESS 'q' for main screen");
		mvwprintw(option_scr, 4, 3, "KAC_MAN  & ");
		mvwprintw(option_scr, 5, 3, "GHOST SPEED");
		for(int x = 1; x < 11; x++){
			mvwprintw(option_scr, 5 + 2 * x, 8, "%d", x);
		}
		mvwprintw(option_scr, 5 + 2 * cursor, 3, "====");
		mvwprintw(option_scr, 5 + 2 * cursor, 10, "====");
		wrefresh(option_scr);
		int input = getch();
		switch(input){
		case KEY_UP:
			if(cursor > 1){
			mvwprintw(option_scr, 5 + 2 * cursor, 3, "    ");
			mvwprintw(option_scr, 5 + 2 * cursor, 10, "    ");
			cursor--;
			}
			continue;
		case KEY_DOWN:
			if(cursor < 10){
			mvwprintw(option_scr, 5 + 2 * cursor, 3, "    ");
			mvwprintw(option_scr, 5 + 2 * cursor, 10, "    ");
			cursor++;
			}
			continue;
		case ' ':
			kac_speed = cursor;
			continue;
		case 'q':
			clear();
			end++;
			print_main_scr();
		}
	}
}

int main(){
	print_main_scr();
	return 0;
}
