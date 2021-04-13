#include<iostream>
#include<ctime>
#include<vector>
#include<queue>

using namespace std;

class board {
private:
	int status;//���°� 0: �����, 1:��, 2:kac_man,3:ghost 4���� ���� ������
	int root_num;//kac_man���� �����ؼ� ���� ĭ������ �ִܰŸ� ����. �ʱ� ���� 10000.
	vector<char> root;//kac_man���� �����ؼ� ����ĭ ������ �ִܰŸ� ���� ��� R, L, U, D �� ����
	
public:
	int x;
	int y;// ���� ������ x�� y �� ����
	board();
	board(int r_status);
	board(int r_status, int x, int y);//���� ���¿� x, y �� ���� �ʱ�ȭ
	int get_status();
	int get_root_num();
	vector<char> get_root();
	int set_root_num(int n);
	board& operator=(const board &ref);
	bool compare_root_num(int n);//�˰����򿡼� ���Ǵ� �Լ�. �񱳰�(������ n)�� �Է� �޾� �ڽź��� Ŭ ��� true ����.
	void push_root_R(vector<char> ref);
	void push_root_L(vector<char> ref);
	void push_root_U(vector<char> ref);
	void push_root_D(vector<char> ref);
	void print_root();
};

class kalgorism {
private:
	vector<vector<board>> board_;//����Ŭ������ �����ϴ� 2���� �迭
public:
	kalgorism();
	kalgorism(int n);// n X nũ���� ���� �����.
	int set_board(int r_x, int r_y, int r_status);// (r_x, r_y)�� ���带 ���°��� �°� �����Ѵ�.
	int trace(int x, int y);// ���� �˰����� ������ ���Ŀ�
	void print_root_num(int x, int y);//�ִܰŸ� �� ���
	void print_root(int x, int y);//�ִܰŸ� ��� ���
	void print_(int x);//���带 �ð������� ǥ���ϴ� �Լ�
};

int main() {
	kalgorism test(50);//50ĭ ¥�� ���� ����
	time_t start, finish;
	double result;//�ð� ��͵�

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
	// ������ �׵θ� ������ ���º�ȯ
	test.set_board(2, 3, 3);//(3,3)�� ���� 2 :kac_man���� ��ȯ
	test.set_board(3, 40, 42);//(40,42)�� ���� 3:ghost�� ��ȯ

	test.print_(50);//50ĭ ¥�� ���� ����ȭ

	start = time(NULL);
	test.trace(3, 3);//(3,3)�������� ��� ĭ �ִܰŸ� ���� ����
	finish = time(NULL);

	test.print_root_num(40, 42);//(40,42)�� �ִܰŸ� ���
	test.print_root(40, 42);//(40,42)�� �ִܰŸ� ��� ���
	result = (double)(finish - start);
	cout << endl<<"�ð� ���� : " << result << "��"<<endl;
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
				cout << "��";
			else if (board_[i][j].get_status() == 1)
				cout << "��";
			else if (board_[i][j].get_status() == 2)
				cout << "��";
			else if (board_[i][j].get_status() == 3)
				cout << "��";
			else
				return;
		}
		cout << endl;
	}
}