#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class test {
private:
  int size;
  vector<vector<int>> board;

public:
  test();
  test(int n);
  vector<vector<int>> get_board() const { return board; }

  void display(void) const;
  /*
  [1][1] to [n-1][n-1]
  */
  void find_path(void);
  void find_path(int now_x, int now_y, vector<vector<int>> footprint,
                 stack<int> x, stack<int> y);
};

int main() {
  test a(5);
  a.display();
  a.find_path();
  return 0;
}

test::test() {
  size = 1;
  vector<vector<int>> result;
  vector<int> temp = {0};
  result.push_back(temp);
}

test::test(int n) {
  size = n;
  //먼저 보드판 만듦
  vector<vector<int>> result_board;
  for (int i = 0; i < n; i++) {
    vector<int> temp;
    for (int j = 0; j < n; j++) {
      if (i == n - 2 || j == n - 2) {
        temp.push_back(1);
      } else {
        temp.push_back(0);
      }
    }
    result_board.push_back(temp);
  }
  result_board[0][n - 2] = 0;
  result_board[n - 2][0] = 0;
  result_board[n - 2][n - 1] = 0;
  result_board[n - 1][n - 2] = 0;
  board = result_board;
}

void test::display(void) const {
  cout << "board" << endl;
  for (auto i : board) {
    for (auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }
}

void test::find_path(void) {
  vector<vector<int>> footprint = board;
  stack<int> way_x;
  stack<int> way_y;
  find_path(1, 1, footprint, way_x, way_y);
}

void test::find_path(int now_x, int now_y, vector<vector<int>> footprint,
                     stack<int> way_x, stack<int> way_y) {
  footprint[now_y][now_x] = 1;
  way_x.push(now_x);
  way_y.push(now_y);
  if (now_x == size - 1 && now_y == size - 1) {
    cout << "finished : " << way_x.size() << endl;
    while (way_x.size() != 0) {
      cout << "x : " << way_x.top() << " y : " << way_y.top() << endl;
      way_x.pop();
      way_y.pop();
    }
    return;
  }

  if (now_y != 0 && (footprint[now_y - 1][now_x] == 0)) {
    find_path(now_x, now_y - 1, footprint, way_x, way_y);
  }
  if (now_y != size - 1 && (footprint[now_y + 1][now_x] == 0)) {
    find_path(now_x, now_y + 1, footprint, way_x, way_y);
  }
  if (now_x != 0 && (footprint[now_y][now_x - 1] == 0)) {
    find_path(now_x - 1, now_y, footprint, way_x, way_y);
  }
  if (now_x != size - 1 && (footprint[now_y][now_x + 1] == 0)) {
    find_path(now_x + 1, now_y, footprint, way_x, way_y);
  }
}
