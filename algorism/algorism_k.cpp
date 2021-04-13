#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class board {
private:
	int status;
	int root_num;
	vector<char> root;
public:
	int a;
	int b;
	board();
	board(int x);
	int set_root_num(int x);
	vector<char> get_root();
	int get_root_num();
	bool compare_root_num(int n);
	board& operator = (const board & ref);
	void push_root_R(vector<char> ref);
	void push_root_L(vector<char> ref);
	void push_root_U(vector<char> ref);
	void push_root_D(vector<char> ref);
	void print_root();
	int get_status();
};

class algorism_k {
private:
	vector<vector<board>> board_;
public:
	algorism_k(int x);
	int set_board(int x, int y,int status);
	int trace(int x, int y);
	void print_board(int x, int y);
	void print_root(int x, int y);
	void print_(int x);
};

int main() {
	algorism_k test(9);
	for (int n = 0; n < 9; n++)
		for (int m = 0; m < 9; m++)
			test.set_board(n, m, 0);
	for (int n = 0; n < 9; n++)
		test.set_board(0, n, 1);
	for (int n = 0; n < 9; n++)
		test.set_board(8, n, 1);
	for (int n = 0; n < 9; n++)
		test.set_board(n, 0, 1);
	for (int n = 0; n < 9; n++)
		test.set_board(n, 8, 1);
	for (int n = 2; n < 7; n++)
		test.set_board(6, n, 1);
	for (int n = 3; n < 7; n++)
		test.set_board(n, 6, 1);
	test.set_board(3, 3, 2);
	test.set_board(7, 7, 3);
	test.trace(3, 3);
	test.print_(9);
	test.print_board(7, 7);
	test.print_root(7, 7);
	return 0;
}

board::board() {
	status = 0;
	root_num = -1;
}

board::board(int x) {
	if (x == 0) {
		status = 0;
		root_num = 1000;
	}
	else if (x == 1) {
		status = 1;
		root_num = -1;
	}
	else if (x == 2) {
		status = 2;
		root_num = 0;
	}
	else if (x == 3) {
		status = 3;
		root_num = 1000;

	}
	else {
		status = 0;
		root_num = -1;
	}
}

int board::set_root_num(int x) {
	root_num = x;
	return 0;
}

vector<char> board::get_root() {
	return root;
}

int board::get_root_num() {
	return root_num;
}

bool board::compare_root_num(int n) {
	if (n < root_num)
		return 1;
	else
		return 0;
}

board& board::operator =(const board &ref) {
	status = ref.status;
	root_num = ref.root_num;
	root = ref.root;
	a = ref.a;
	b = ref.b;
	return *this;
}

void board::push_root_R(vector<char> ref) {
	root = ref;
	root.push_back('R');
	return;
}
void board::push_root_L(vector<char> ref) {
	root = ref;
	root.push_back('L');
	return;
}
void board::push_root_U(vector<char> ref) {
	root = ref;
	root.push_back('U');
	return;
}
void board::push_root_D(vector<char> ref) {
	root = ref;
	root.push_back('D');
	return;
}

void board::print_root() {
	for (int i = 0; i < root.size(); i++)
		cout << root[i] <<"->";
	return;
}

int board::get_status() {
	return status;
}

algorism_k::algorism_k(int x) {

	for (int i = 0; i < x; i++) {
		vector<board> temp;
		for (int j = 0; j < x; j++) {
			board temp_board;
			temp_board.a = i;
			temp_board.b = j;
			temp.push_back(temp_board);
		}
		board_.push_back(temp);
	}
}

int algorism_k::set_board(int x, int y, int status) {
	board temp(status);
	temp.a = x;
	temp.b = y;
	board_[x][y] = temp;
	return 0;
}

int algorism_k::trace(int x, int y) {
	board temp;
	queue<board> board_q;
	board_q.push(board_[x][y]);
	for (int n = 0;board_q.size()>0; n++) {
		while (1) {
			temp = board_q.front();
			if (temp.get_root_num() == n) {
				int i = temp.a;
				int j = temp.b;
				board ref;
				ref = board_[i][j + 1];//R(오른쪽)
				if (ref.compare_root_num(n)) {
					board_[i][j + 1].set_root_num(n + 1);
					board_[i][j + 1].push_root_R(board_[i][j].get_root());
					board_q.push(board_[i][j + 1]);
				}

				ref = board_[i][j - 1];//L(왼쪽)
				if (ref.compare_root_num(n)) {
					board_[i][j - 1].set_root_num(n + 1);
					board_[i][j - 1].push_root_L(board_[i][j].get_root());
					board_q.push(board_[i][j - 1]);
				}

				ref = board_[i + 1][j];//D(아래쪽)
				if (ref.compare_root_num(n)) {
					board_[i + 1][j].set_root_num(n + 1);
					board_[i+1][j ].push_root_D(board_[i][j].get_root());
					board_q.push(board_[i + 1][j]);
				}

				ref = board_[i - 1][j];//U(위쪽)
				if (ref.compare_root_num(n)) {
					board_[i - 1][j].set_root_num(n + 1);
					board_[i-1][j].push_root_U(board_[i][j].get_root());
					board_q.push(board_[i - 1][j]);
				}
				board_q.pop();
			}
			else
				break;
			if (board_q.size() == 0)
				break;
		}
	}
	return 0;
}

void algorism_k::print_board(int x, int y) {
	cout << board_[x][y].get_root_num() << endl;
	return;
}

void algorism_k::print_root(int x, int y) {
	board_[x][y].print_root();
	return;
}

void algorism_k::print_(int x) {
	for(int i=0;i<x;i++){
			for (int j = 0; j < x; j++)
			{
				if (board_[i][j].get_status() == 0)
					cout << "○";
				else if (board_[i][j].get_status() == 1)
					cout << "●";
				else if (board_[i][j].get_status() == 2)
					cout << "☆";
				else if (board_[i][j].get_status() == 3)
					cout << "★";
				else
					return;
			}
			cout << endl;
		}
}