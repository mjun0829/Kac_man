#include "kac_man.hpp"
#include <iostream>
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

//임시 변수들 
int wall_test_array[31][28] = {0,};
int dir[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int test_man_x = 2;
int test_man_y = 2;
int test_dir[2] = {0, 0};

void GameManager::init_ncurses(){
	initscr();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	set_main_scr(make_scr(scr_max_y, main_max_x, 0, 0));
	set_game_scr(make_scr(scr_max_y, game_max_x, 0, 0));
	set_game_score_scr(make_scr(scr_max_y, game_score_max_x, 0, game_max_x));
	set_map_view_max_x(make_scr(scr_max_y, map_view_max_x, 0, 0));
	set_map_select_max_x(make_scr(scr_max_y, map_select_max_x, 0, map_view_max_x));
}

WINDOW *GameManager::make_scr(int max_y, int max_x, int start_y, int start_x){
	return newwin(max_y, max_x, start_y, start_x);
}

void GameManager::print_game_init_objs(){
	wborder(get_game_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(get_game_score_scr(), '|', '|', '-', '-', '+', '+', '+', '+');
	for(int y = 0; y < 31; y++){
		for(int x = 0; x < 28; x++){
			if(wall_test_array[y][x] == WALL){
				mvwprintw(get_game_scr(), y + 1, x + 1, "W");
			}
			/*
			if( == POW_DOT){
				mvwprintw(get_game_scr(), y + 1, x + 1, "");
			}
			if( == KAC_DOT){
				mvwprintw(get_game_scr(), y + 1, x + 1, "");
			}
			*/
		}
	}
	mvwprintw(get_game_scr(), test_man_y, test_man_x, "K");
	wrefresh(get_game_scr());
	wrefresh(get_game_score_scr());
}

void GameManager::print_game_repeat_objs(){
	/*
	KacMan temp_man = get_kac_man();
	Ghost temp_ghost = get_ghost();
	mvwprintw(get_game_scr(), temp_man.get_y, temp_man.get_x, "");
	mvwprintw(get_game_scr(), temp_ghost.get_y, temp_ghost.get_x, "");
	wrefresh(get_game_scr());
	mvwprintw(get_game_scr(), temp_man.get_y, temp_man.get_x, " ");
        mvwprintw(get_game_scr(), temp_ghost.get_y, temp_ghost.get_x, " ");
	*/
}

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

void GameManager::keypad_manage(){
	int input = getch();
	/*
	switch(input){
		case KEY_UP:
			test_dir[0] = dir[0][0];
			test_dir[1] = dir[0][1];
			continue;
		case KEY_RIGHT:
			test_dir[0] = dir[1][0];
			test_dir[1] = dir[1][1];
			continue;
		case KEY_DOWN:
			test_dir[0] = dir[2][0];
			test_dir[1] = dir[2][1];
			continue;
		case KEY_LEFT:
			test_dir[0] = dir[3][0];
			test_dir[1] = dir[3][1];
			continue;

	}
	*/
}
