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
	set_main_scr(make_scr(scr_max_y, main_max_x, 0, 0));
	set_game_scr(make_scr(scr_max_y, game_max_x, 0, 0));
	set_game_score_scr(make_scr(scr_max_y, game_score_max_x, 0, game_max_x));
	set_map_view_scr(make_scr(scr_max_y, map_view_max_x, 0, 0));
	set_map_select_scr(make_scr(scr_max_y, map_select_max_x, 0, map_view_max_x));
}

WINDOW *GameManager::make_scr(int max_y, int max_x, int start_y, int start_x){
	return newwin(max_y, max_x, start_y, start_x);
}

void GameManager::print_game_init_objs(kac_man::Map map){
	std::vector<std::vector<kac_man::ObjectStatus>> temp_board = map.get_board();
	wborder(get_game_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(get_game_score_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	for(int y = 0; y < temp_board.size(); y++){
		for(int x = 0; x < temp_board[0].size; x++){
			if(temp_board[y][x] == WALL){
				mvwprintw(get_game_scr(), y + 1, x + 1, "W");
			}
			else if(temp_board[y][x] == POW_DOT){
				mvwprintw(get_game_scr(), y + 1, x + 1, "P");
			}
			else if(temp_board[y][x] == KAC_DOT){
				mvwprintw(get_game_scr(), y + 1, x + 1, "+");
			}
			else{
				mvwprintw(get_game_scr(), y + 1, x + 1, " ");
			}
		}
	}
	wrefresh(get_game_scr());
	wrefresh(get_game_score_scr());
}

void GameManager::print_game_repeat_objs(kac_man::Map map){
	std::vector<Ghost> temp_ghost = map.get_ghosts();
	KacMan temp_man = map.get_kac_man();
	mvwprintw(get_game_scr(), temp_man.get_y(), temp_man.get_x(), "K");
	for(int x = 0; x < temp_ghost.size(); x++){
		mvwprintw(get_game_scr(), temp_ghost[x].get_y(), temp_ghost[x].get_x(), "G");
	}
	wrefresh(get_game_scr());
	mvwprintw(get_game_scr(), temp_man.get_y(), temp_man.get_x(), " ");
	for(int x = 0; x < temp_ghost.size(); x++){
        	mvwprintw(get_game_scr(), temp_ghost[x].get_y(), temp_ghost[x].get_x(), " ");
	}
}
/*
void GameManager::load_map(){
	std::ifstream fd;
	fd.open("map_test.txt");
	char temp;
	int y = 0, x = 0;
	if(fd.good()){
		while(!fd.eof()){
			fd.get(temp);
			if(temp == 'W'){
				wall_test_array[y][x] = 4;
				x++
			}
			if(temp == '\n'){
				y++;
				x = 0;
			}
		}

	}
	fd.close();
}
*/
void GameManager::game_manage(kac_man::Map map){
	KacMan temp_man = map.get_kac_man();
	while(1){
		int input = getch();
	switch(input){
		case KEY_UP:
			temp_man.set_dir_x(UP);
			temp_man.set_dir_y(0);
			continue;
		case KEY_RIGHT:
			temp_man.set_dir_x(0);
                        temp_man.set_dir_y(RIGHT);
			continue;
		case KEY_DOWN:
			temp_man.set_dir_x(DOWN);
                        temp_man.set_dir_y(0);
			continue;
		case KEY_LEFT:
			temp_man.set_dir_x(0);
			temp_man.set_dir_y(LEFT);
			continue;
		case 'q':
			break;

	}
	}
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

void GameManager::print_main_scr(){
	wborder(get_main_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(get_main_scr(), 10, 17, "KAC--MAN");
	mvwprintw(get_main_scr(), 16, 16, "GAME START");
	mvwprintw(get_main_scr(), 20, 16, "FIX OPTION");
	mvwprintw(get_main_scr(), 24, 16, "LOAD  MAPS");
	mvwprintw(get_main_scr(), 27, 8, "PRESS 'spacebar' to select");
	int input = getch();
	switch(input){
		case ' ':
			clear();
			print_game_scr();
	}
}

void GameManager::print_game_scr(){
	init_ncurses();
	print_game_init_objs();
	while(1){
		print_game_repeat_objs();
		frame_timer();
		game_manage();
	}
}
