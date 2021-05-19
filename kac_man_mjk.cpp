#include "kac_man.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <ncurses.h>
#include <time.h>

using namespace kac_man;

#define scr_max_y 33
#define main_max_x 42
#define game_max_x 30
#define game_score_max_x 12
#define map_view_max_x 30
#define map_select_max_x 12

void GameManager::init_ncurses(){
	initscr();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	start_color();
	init_pair(WALL, COLOR_WHITE, COLOR_BLACK);
	init_pair(KAC_MAN, COLOR_YELLOW, COLOR_BLACK);
	init_pair(GHOST, COLOR_RED, COLOR_BLACK);
	init_pair(KAC_DOT, COLOR_GREEN, COLOR_BLACK);
	init_pair(POW_DOT, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_BLUE, COLOR_BLACK);
}

WINDOW *GameManager::make_scr(int max_y, int max_x, int start_y, int start_x){
	return newwin(max_y, max_x, start_y, start_x);
}

void GameManager::print_main_scr(){
	int end = 1, cursor = 1;
	init_ncurses();
	set_main_scr(make_scr(scr_max_y, main_max_x, 0, 0));
	while(end == 1){
		frame_timer();
		print_main_obj(cursor);
		int input = getch();
		switch(input){
			case KEY_UP:
				if(cursor > 1){
				mvwprintw(get_main_scr(), 12 + 4 * cursor, 1 , "               ");
				mvwprintw(get_main_scr(), 12 + 4 * cursor, 26, "               ");
				cursor--;
				}
				continue;
			case KEY_DOWN:
				if(cursor < 3){
				mvwprintw(get_main_scr(), 12 + 4 * cursor, 1 , "               ");
				mvwprintw(get_main_scr(), 12 + 4 * cursor, 26, "               ");
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
				end++;
				break;
		}
	}
}

void GameManager::print_main_obj(int cursor){
	wborder(get_main_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(get_main_scr(), 6 , 2, "|  /  |\\      /|      /\\      |\\     |");
	mvwprintw(get_main_scr(), 7 , 2, "| /   | \\    / |     /  \\     | \\    |");
	mvwprintw(get_main_scr(), 8 , 2, "|/  ==|  \\  /  |    /    \\    |  \\   |");
	mvwprintw(get_main_scr(), 9 , 2, "|\\  ==|   \\/   |   /\\/\\/\\/\\   |   \\  |");
	mvwprintw(get_main_scr(), 10, 2, "| \\   |        |  /        \\  |    \\ |");
	mvwprintw(get_main_scr(), 11, 2, "|  \\  |        | /          \\ |     \\|");
	mvwprintw(get_main_scr(), 16, 2, "");
	mvwprintw(get_main_scr(), 20, 2, "");
	mvwprintw(get_main_scr(), 24, 2, "");
	mvwprintw(get_main_scr(), 27, 2, "");
	mvwprintw(get_main_scr(), 12 + 4 * cursor, 1 , "===============");
	mvwprintw(get_main_scr(), 12 + 4 * cursor, 26, "===============");
	wrefresh(get_main_scr());
}

void GameManager::print_game_scr(ObjecManager board){
	int end = 1, timer = 0, strong_timer = 0;
	double strong_point = 1.0;
	KacMan temp_man = board.get_kac_man();
	std::vector<std::vector<int>> t_board = board.get_board();
	while(end == 1){
		frame_timer();
		timer++;
		if(temp_man.get_is_strong){
			strong_timer++;
		}
		if(strong_timer >= 300){
			temp_man.set_is_strong(FALSE);
			strong_timer = 0;
		}
		set_game_scr(make_scr(scr_max_y, game_max_x, 0, 0));
		set_game_score_scr(make_scr(scr_max_y, game_score_max_x, 0, game_max_x));
		print_game_obj(board);
		print_gmae_score_obj(board);
		MovingObject::move();
		if(t_board[temp_man.get_y()][temp_man.get_x()] == GHOST){
			ObjectManager::man_ghost_crush(temp_man.get_is_strong);
		}
		/*if(t_board[temp_man.get_y()][temp_man.get_x()] == GHOST && temp_man.get_is_strong){
			
		}*/
		if(t_board[temp_man.get_y()][temp_man.get_x()] == KAC_DOT){
			ObjectManager::man_kdot_crush();
		}
		if(t_board[temp_man.get_y()][temp_man.get_x()] == POW_DOT){
			ObjectManager::man_pdot_crush();
		}
		int input = getch();
		switch(input){
		case 'q':
			clear();
			end++;
			print_main_scr();
			break;
		case KEY_UP:
			temp_man.set_dir_x(UNDIRECT);
			temp_man.set_dir_y(UP);
			continue;
		case KEY_DOWN:
			temp_man.set_dir_x(UNDIRECT);
			temp_man.set_dir_y(DOWN);
			continue;
		case KEY_RIGHT:
			temp_man.set_dir_x(RIGHT);
			temp_man.set_dir_y(UNDIRECT);
			continue;
		case KEY_LEFT:
			temp_man.set_dir_x(LEFT);
			temp_man.set_dir_y(UNDIRECT);
			continue;
		}
	}
}

void GameManager::print_game_obj(ObjectManager board){
	std::vector<std::vector<int>> temp_board = board.get_board();
	KacMan temp_man = board.get_kac_man();
	wborder(get_game_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(get_game_score_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	for(int y = 0; y < temp_board.size(); y++){
		for(int x = 0; x < temp_board[0].size(); x++){
			if(temp_board[y][x] == EMPTY){
				wattron(get_game_scr(), COLOR_PAIR(WALL));
				mvwprintw(get_game_scr(), y + 1, x + 1, " ");
			}
			else if(temp_board[y][x] == WALL){
				wattron(get_game_scr(), COLOR_PAIR(WALL));
				mvwprintw(get_game_scr(), y + 1, x + 1, "W");
			}
			else if(temp_board[y][x] == KAC_MAN){
				wattron(get_game_scr(), COLOR_PAIR(KAC_MAN));
				mvwprintw(get_game_scr(), y + 1, x + 1, "K");
			}
			else if(temp_board[y][x] == GHOST){
				if(temp_man.get_is_strong){
					wattron(get_game_scr(), COLOR_PAIR(10));
				}
				else{
					wattron(game_scr, COLOR_PAIR(GHOST));
				}
				mvwprintw(get_game_scr(), y + 1, x + 1, "G");
			}
			else if(temp_board[y][x] == KAC_DOT){
				wattron(get_game_scr(), COLOR_PAIR(KAC_DOT));
				mvwprintw(get_game_scr(), y + 1, x + 1, "+");
			}
			else if(temp_board[y][x] == POW_DOT){
				wattron(get_game_scr(), COLOR_PAIR(POW_DOT));
				mvwprintw(get_game_scr(), y + 1, x + 1, "P");
			}
		}
	}
	wrefresh(get_game_scr());
}

void GameManager::print_game_score_obj(){
	Variables var;
	mvwprintw(get_game_score_scr(), 9 , 1, " LIFE : %d", var.get_life());
	mvwprintw(get_game_score_scr(), 12, 1, " SCORE");
	mvwprintw(get_game_score_scr(), 13, 1, " : %d", game_score);
	wrefresh(get_game_score_scr());
}

void GameManager::print_option_scr(){
	int end = 1, cursor = 1;
	set_option_scr(make_scr(scr_max_y, main_max_x, 0, 0));
	while(end == 1){
		wborder(get_option_scr(), '|','|','-','-','+','+','+','+');
		mvwprintw(get_option_scr(), 2, 1, "PRESS 'space bar' to select &");
		mvwprintw(get_option_scr(), 3, 1, "PRESS 'q' for main screen");
		mvwprintw(get_option_scr(), 4, 3, "KAC_MAN  &");
		mvwprintw(get_option_scr(), 5, 3, "GHOST SPEED");
		for(int x = 1; x < 11; x++){
			mvwprintw(get_option_scr(), 5 + 2 * x, 8, "%d", x);
		}
		mvwprintw(get_option_scr(), 5 + 2 * cursor, 3 , "====");
		mvwprintw(get_option_scr(), 5 + 2 * cursor, 10, "====");
		wrefresh(get_option_scr());
		int input = getch();
		switch(input){
		case KEY_UP:
			if(cursor > 1){
			mvwprintw(option_scr, 5 + 2 * cursor, 3 , "    ");
			mvwprintw(option_scr, 5 + 2 * cursor, 10, "    ");
			cursor--;
			}
			continue;
		case KEY_DOWN:
			if(cursor < 10){
			mvwprintw(option_scr, 5 + 2 * cursor, 3 , "    ");
			mvwprintw(option_scr, 5 + 2 * cursor, 10, "    ");
			cursor++;
			}
			continue;
		case ' ':
			//speed
			continue;
		case 'q':
			clear();
			end++;
			print_main_scr();
		}
	}
}

void GameManager::frame_timer(){
	time_t start, now;
	start = clock();
	while(1){
		now = clock();
		if((double)(now - start) / (double)(CLOCKS_PER_SEC) >= 0.0166){
			break;
		}
	}
}

void GameManager::start_scr(){
	print_main_scr();
	endwin();
}
 
