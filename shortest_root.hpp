#ifndef __SHORTEST_ROOT__
#define __SHORTEST_ROOT__

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <queue>
#include "kac_man.hpp"

namespace ims {
	
	/*
	클래스 space
	(x,y)좌표의 status값을 가지고 있다.
	board 클래스와 비슷하나 root_num(최단거리)과 root(최단 루트) 변수 추가.
	*/
	class space {
	private:
		int x;	//보드 x 좌표
		int y;	//보드 y 좌표
		int status; //현재 보드의 상태 1:EMPTY 2:WALL 3:GHOST 4:KAC_MAN
		int root_num;	//KAC_MAN부터 현재 지점까지의 최단거리
		std::vector<char> root;	//KAC_MAN부터 현재 지점까지의 최단 루트 RLUD를 이용하여 배열
		const int INFINITE=10000;	//무한
	public:
		space();
		space(int new_x, int new_y, int new_status);	//생성자 (X,Y)값의 status값을 받아서 설정.
		void set_x(int new_x) { x = new_x; }
		void set_y(int new_y) { y = new_y; }
		void set_status(int new_status) { status = new_status; }
		void set_root_num(int new_root_num) { root_num = new_root_num; }
		void set_space(int new_x, int new_y, int status);
		void push_root_R(std::vector<char> ref) { root = ref; root.push_back('R'); }	//root 에 R 대입
		void push_root_L(std::vector<char> ref) { root = ref; root.push_back('L'); }	//root 에 L 대입
		void push_root_U(std::vector<char> ref) { root = ref; root.push_back('U'); }	//root 에 U 대입
		void push_root_D(std::vector<char> ref) { root = ref; root.push_back('D'); }	//root 에 D 대입
		const int get_x() { return x; }
		const int get_y() { return y; }
		const int get_status() { return status; }
		const int get_root_num() { return root_num; }
		const std::vector<char> get_root(){ return root; }
		space& operator=(const space &ref) { x = ref.x; y = ref.y; status = ref.status; root_num = ref.root_num; root = ref.root; return *this; }
		bool compare_root_num(int n){return n<root_num;}	//현재의 root_num과 n 값을 비교하여 n이 작으면 TRUE n이 크면 FALSE 리턴
	};

	/*
	클래스 shortest_root
	최단거리 알고리즘 정의한 클래스
	Map 클래스를 받아와 2차원 배열 board를 정의한다.
	trace 함수를 통해서 모든 칸의 최단경로를 업데이트 한다.(WALL제외)
	*/
	class shortest_root {
	private:
		std::vector<std::vector<space>> board;
	public:
		shortest_root(kac_man::Map map );	//map 클래스 받아와서 2차원 배열 각각의 칸에 space를 정의한다.
		void trace(kac_man::Map map);	//최단거리 알고리즘
	};
}

#endif