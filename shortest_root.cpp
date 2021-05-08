#include <iostream>
#include "kac_man.hpp"

using namespace kac_man;

space::space()
{
	int x = 0;
	int y = 0;
	int status = 0;
	int root_num = 0;
}

space::space(int new_x, int new_y, int new_status)
{
	x = new_x;
	y = new_y;
	status = new_status;
	if (new_status == kac_man::EMPTY) //0
		root_num = INFINITE;
	else if (new_status == kac_man::WALL) //1
		root_num = -1;
	else if (new_status == kac_man::KAC_MAN) //2
		root_num = 0;
	else if (new_status == kac_man::GHOST) //3
		root_num = INFINITE;
	else
		root_num = INFINITE;
}

void space::set_space(int new_x, int new_y, int new_status)
{
	x = new_x;
	y = new_y;
	status = new_status;
	if (new_status == kac_man::EMPTY) //0
		root_num = INFINITE;
	else if (new_status == kac_man::WALL) //1
		root_num = -1;
	else if (new_status == kac_man::KAC_MAN) //2
		root_num = 0;
	else if (new_status == kac_man::GHOST) //3
		root_num = INFINITE;
	else
		root_num = INFINITE;
}

shortest_root::shortest_root(kac_man::Map map)
{
	std::vector<std::vector<int>> temp_board = map.get_board();
	for (int i = 0; i < map.get_row_num(); i++)
	{
		std::vector<space> temp;
		for (int j = 0; j < map.get_col_num(); j++)
		{
			space temp_space(i, j, temp_board[i][j]);
			temp.push_back(temp_space);
		}
		board.push_back(temp);
	}
	trace(map);
}

void shortest_root::trace(kac_man::Map map)
{
	kac_man::KacMan temp_kac_man = map.get_kac_man();
	int x = temp_kac_man.get_x();
	int y = temp_kac_man.get_y();
	std::queue<space> board_q;
	space temp;
	space ref;

	board_q.push(board[x][y]);
	for (int n = 0; board_q.size() > 0; n++)
	{
		while (1)
		{
			temp = board_q.front();

			if (temp.get_root_num() == n)
			{
				int i = temp.get_x();
				int j = temp.get_y();
				ref = board[i][j + 1];
				if (board[i][j + 1].compare_root_num(n + 1))
				{
					board[i][j + 1].set_root_num(n + 1);
					board[i][j + 1].push_root_R(temp.get_root());
					board_q.push(board[i][j + 1]);
				}

				ref = board[i + 1][j];
				if (board[i + 1][j].compare_root_num(n + 1))
				{
					board[i + 1][j].set_root_num(n + 1);
					board[i + 1][j].push_root_D(temp.get_root());
					board_q.push(board[i + 1][j]);
				}

				ref = board[i][j - 1];
				if (board[i][j - 1].compare_root_num(n + 1))
				{
					board[i][j - 1].set_root_num(n + 1);
					board[i][j - 1].push_root_L(temp.get_root());
					board_q.push(board[i][j - 1]);
				}

				ref = board[i - 1][j];
				if (board[i - 1][j].compare_root_num(n + 1))
				{
					board[i - 1][j].set_root_num(n + 1);
					board[i - 1][j].push_root_U(temp.get_root());
					board_q.push(board[i - 1][j]);
				}
				board_q.pop();
			}
			else
				break;
			if (board_q.size() == 0)
				break;
		}
	}
}

void shortest_root::set_board(kac_man::Map map)
{
	std::vector<std::vector<int>> temp_board = map.get_board();
	for (int i = 0; i < map.get_row_num(); i++)
	{
		for (int j = 0; j < map.get_col_num(); j++)
		{
			space temp_space(i, j, temp_board[i][j]);
			board[i][j] = temp_space;
		}
	}
	trace(map);
}