#include <iostream>
#include <stack>
#include <vector>
#include <time.h>
#include <ncurses.h>

using namespace std;

class test {
private:
  int size;
  vector<vector<int>> board;
  stack<int> shortcut_x;
  stack<int> shortcut_y;

public:
  test();
  test(int n);
  vector<vector<int>> get_board() const { return board; }

  void display_init_board(void) const;
  void display(void) const;
  /*
  [1][1] to [n-1][n-1]
  */
  void find_path(void);
  void find_path(int now_x, int now_y, vector<vector<int>> footprint,
                 stack<int> way_x, stack<int> way_y);
};

int main() {
    initscr();
    test a(50);
    a.display_init_board();
    time_t start = clock();
    a.find_path();
    time_t end = clock();
    //a.display();
    endwin();
    cout << "time : " << (double)(end - start) / CLOCKS_PER_SEC << " sec "
         << endl;
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

  for (int i = 0; i < size * size; i++) {
    shortcut_x.push(0);
    shortcut_y.push(0);
  }
}

//목적지가 D, 벽이 @
void test::display_init_board(void) const {
  for (int row=0; row < size;row++){
      for (int col=0; col < size;col++){
        if(board[row][col]==1){
            mvprintw(row, col, "@");
        }
      }
  }
  mvprintw(size - 1, size - 1, "D");
  refresh();
}

void test::display(void) const {
  stack<int> temp_x = shortcut_x;
  stack<int> temp_y = shortcut_y;
  cout << "size : " << shortcut_x.size() << endl;
  while (temp_x.size() != 0) {
    cout << "x : " << temp_x.top() << " y : " << temp_y.top() << endl;
    temp_x.pop();
    temp_y.pop();
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
  //민준이 아이디어
  if (shortcut_x.size()+shortcut_y.size() < way_x.size()+way_y.size()+(size-now_x)+(size-now_y)) {
    mvprintw(way_y.top(), way_x.top(), " ");
    //    cout << "terminated" << endl;
    refresh();
    return;
  }
  mvprintw(now_y, now_x, "O");
  refresh();
  footprint[now_y][now_x] = 1;
  way_x.push(now_x);
  way_y.push(now_y);

  if (now_x == size - 1 && now_y == size - 1) {
    //cout << "finished : " << way_x.size() << endl;
    mvprintw(way_y.top(), way_x.top(), " ");
    if (shortcut_x.size() > way_x.size()) {
      shortcut_x = way_x;
      shortcut_y = way_y;
    }
      refresh();
    return;
  }

  if (now_x != size - 1 && (footprint[now_y][now_x + 1] == 0)) {
    find_path(now_x + 1, now_y, footprint, way_x, way_y);
  }

  if (now_y != size - 1 && (footprint[now_y + 1][now_x] == 0)) {
    find_path(now_x, now_y + 1, footprint, way_x, way_y);
  }

  if (now_x != 0 && (footprint[now_y][now_x - 1] == 0)) {
    find_path(now_x - 1, now_y, footprint, way_x, way_y);
  }

  if (now_y != 0 && (footprint[now_y - 1][now_x] == 0)) {
    find_path(now_x, now_y - 1, footprint, way_x, way_y);
  }
  mvprintw(now_y, now_x, " ");
  refresh();
}
