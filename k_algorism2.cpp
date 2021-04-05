#include<iostream>
#include<ctime>
#include<vector>
#include<queue>

using namespace std;

class board {
private:
	int status;//상태값 0: 빈공간, 1:벽, 2:kac_man,3:ghost 4가지 상태 정의함
	int root_num;//kac_man에서 시작해서 현재 칸까지의 최단거리 저장. 초기 값은 10000.
	vector<char> root;//kac_man에서 시작해서 현재칸 까지의 최단거리 가는 방법 R, L, U, D 로 저장
	
public:
	int x;
	int y;// 현재 보드의 x값 y 값 저장
	board();
	board(int r_status);
	board(int r_status, int x, int y);//현재 상태와 x, y 값 저장 초기화
	int get_status();
	int get_root_num();
	vector<char> get_root();
	int set_root_num(int n);
	board& operator=(const board &ref);
	bool compare_root_num(int n);//알고리즘에서 사용되는 함수. 비교값(현재의 n)을 입력 받아 자신보다 클 경우 true 리턴.
	void push_root_R(vector<char> ref);
	void push_root_L(vector<char> ref);
	void push_root_U(vector<char> ref);
	void push_root_D(vector<char> ref);
	void print_root();
};

class kalgorism {
private:
	vector<vector<board>> board_;//보드클래스를 저장하는 2차원 배열
public:
	kalgorism();
	kalgorism(int n);// n X n크기의 판을 만든다.
	int set_board(int r_x, int r_y, int r_status);// (r_x, r_y)의 보드를 상태값에 맞게 변경한다.
	int trace(int x, int y);// 메인 알고리즘 설명은 추후에
	void print_root_num(int x, int y);//최단거리 값 출력
	void print_root(int x, int y);//최단거리 경로 출력
	void print_(int x);//보드를 시각적으로 표현하는 함수
};

int main() {
	kalgorism test(50);//50칸 짜리 보드 만듬
	time_t start, finish;
	double result;//시간 잴것들

	for (int n = 0; n < 50; n++)
		for (int m = 0; m < 50; m++)
			test.set_board(0,n, m);
	for (int n = 0; n < 50; n++)
		test.set_board(1,0, n);
	for (int n = 0; n < 50; n++)
		test.set_board(1,49, n);
	for (int n = 0; n < 50; n++)
		test.set_board(1,n, 0);
	for (int n = 0; n < 50; n++)
		test.set_board(1,n, 49);
	// 주위에 테두리 벽으로 상태변환
	test.set_board(2, 3, 3);//(3,3)을 상태 2 :kac_man으로 변환
	test.set_board(3, 40, 42);//(40,42)를 상태 3:ghost로 변환

	test.print_(50);//50칸 짜리 보드 가시화

	start = time(NULL);
	test.trace(3, 3);//(3,3)기준으로 모든 칸 최단거리 추적 시작
	finish = time(NULL);

	test.print_root_num(40, 42);//(40,42)의 최단거리 출력
	test.print_root(40, 42);//(40,42)의 최단거리 경로 출력
	result = (double)(finish - start);
	cout << endl<<"시간 측정 : " << result << "초"<<endl;
	return 0;
}

board::board() {
	status = 0;
	root_num = 10000;
	x = 0;
	y = 0;
}

board::board(int r_status) {
	if (r_status == 0) {
		status = 0;
		root_num = 10000;
		x = 0;
		y = 0;
	}
	else if (r_status == 1) {
		status = 1;
		root_num = -1;
		x = 0;
		y = 0;
	}
	else if (r_status == 2) {
		status = 2;
		root_num = 0;
		x = 0;
		y = 0;
	}
	else if (r_status == 3) {
		status = 3;
		root_num = 10000;
		x = 0;
		y = 0;
	}
	else {
		status = 0;
		root_num = 10000;
		x = 0;
		y = 0;
	}
}

board::board(int r_status, int r_x, int r_y) {
	if (r_status == 0) {
		status = 0;
		root_num = 10000;
		x = r_x;
		y = r_y;
	}
	else if (r_status == 1) {
		status = 1;
		root_num = -1;
		x = r_x;
		y = r_y;
	}
	else if (r_status == 2) {
		status = 2;
		root_num = 0;
		x = r_x;
		y = r_y;
	}
	else if (r_status == 3) {
		status = 3;
		root_num = 10000;
		x = r_x;
		y = r_y;
	}
	else {
		status = 0;
		root_num = 10000;
		x = r_x;
		y = r_y;
	}
}

int board::get_status() {
	return status;
}

int board::get_root_num() {
	return root_num;
}

vector<char> board::get_root() {
	return root;
}

int board::set_root_num(int n) {
	root_num = n;
	return 0;
}

board& board::operator=(const board &ref) {
	status = ref.status;
	root_num = ref.root_num;
	root = ref.root;
	x = ref.x;
	y = ref.y;
	return *this;
}

bool board::compare_root_num(int n) {
	if (n < root_num)
		return 1;
	else
		return 0;
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
		cout << root[i] << "->";
	return;
}

kalgorism::kalgorism() {
	for (int i = 0; i < 10; i++) {
		vector<board> temp;
		for (int j = 0; j < 10; j++) {
			board temp_board;
			temp_board.x = i;
			temp_board.y = j;
			temp.push_back(temp_board);
		}
		board_.push_back(temp);
	}
}

kalgorism::kalgorism(int n) {
	for (int i = 0; i < n; i++) {
		vector<board> temp;
		for (int j = 0; j < n; j++) {
			board temp_board;
			temp_board.x = i;
			temp_board.y = j;
			temp.push_back(temp_board);
		}
		board_.push_back(temp);
	}
}

int kalgorism::set_board(int status, int x, int y) {
	board temp(status, x, y);
	board_[x][y] = temp;
	return 0;
}

int kalgorism::trace(int x, int y) {
	queue<board> board_q;
	board temp;
	board ref;

	board_q.push(board_[x][y]);
	for (int n = 0; board_q.size() > 0; n++) {
		while (1) {
			temp = board_q.front();
			
			if (temp.get_root_num() == n) {
				int i = temp.x;
				int j = temp.y;
				ref = board_[i][j + 1];
				if (board_[i][j + 1].compare_root_num(n+1)) {
					board_[i][j+1].set_root_num(n + 1);
					board_[i][j + 1].push_root_R(temp.get_root());
					board_q.push(board_[i][j + 1]);
				}

				ref = board_[i + 1][j];
				if (board_[i + 1][j].compare_root_num(n+1)) {
					board_[i + 1][j].set_root_num(n + 1);
					board_[i + 1][j].push_root_D(temp.get_root());
					board_q.push(board_[i + 1][j]);
				}

				ref = board_[i][j - 1];
				if (board_[i][j - 1].compare_root_num(n+1)) {
					board_[i][j - 1].set_root_num(n + 1);
					board_[i][j - 1].push_root_L(temp.get_root());
					board_q.push(board_[i][j - 1]);
				}

				ref = board_[i - 1][j];
				if (board_[i - 1][j].compare_root_num(n+1)) {
					board_[i - 1][j].set_root_num(n + 1);
					board_[i - 1][j].push_root_U(temp.get_root());
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

void kalgorism::print_root_num(int x, int y) {
	cout << board_[x][y].get_root_num() << endl;
	return;
}

void kalgorism::print_root(int x, int y) {
	board_[x][y].print_root();
	return;
}

void kalgorism::print_(int x) {
	for (int i = 0; i < x; i++) {
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