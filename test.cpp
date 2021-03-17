#include <iostream>
#include <vector>

using namespace std;

class test {
private:
  vector<vector<int>> board;
  vector<vector<int>> graph;

public:
  test();
  test(int n);
  vector<vector<int>> get_board() const { return board; }
  vector<vector<int>> get_graph() const { return graph; }

  void display(void) const;
};

int main() {
  test a(5);
  a.display();
  return 0;
}

test::test() {
  vector<vector<int>> result;
  vector<int> temp = {0};
  result.push_back(temp);
}

test::test(int n) {
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

  vector<vector<int>> result_graph;
  for (int i = 0; i < n * n; i++) {
    vector<int> temp;
    for (int j = 0; j < n * n; j++) {
      temp.push_back(0);
    }
    result_graph.push_back(temp);
  }

  graph = result_graph;
}

void test::display(void) const {
  cout << "board" << endl;
  for (auto i : board) {
    for (auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }
  cout << "graph" << endl;
  for (auto i : graph) {
    for (auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }
}
