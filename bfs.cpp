#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

class board {
    private:
      int x;
      int y;
      bool is_wall;

    public:
      board(int new_x, int new_y, int new_status) :
                     x(new_x), y(new_y), is_wall(new_status){}
      int get_x() const { return x; }
      int get_y() const { return y; }
      bool get_status() const { return is_wall; }
      void set_status(bool new_status) { is_wall = new_status; }
      board operator=(const board &source) {
          x = source.get_x();
          y = source.get_y();
          is_wall = source.get_status();
          return *this;
      }
};

class test {
    private:
      vector<vector<board>> target;
      int target_size;

    public:
      test();
      test(int target_size);
      vector<vector<board>> get_target(void) const { return target; }
      int get_target_size() const { return target_size; }
      void search(void) const;
      bool check_destination(board source) const;
      void display_target(void) const;
};

class prev_board {
    private:
      board prev;
    public:
      prev_board(board new_board) : prev(new_board) {}
      board get_prev_board() const { return prev; }
};

int main() {
    test a(50);
    time_t start = clock();
    a.search();
    a.display_target();
    time_t end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC << "sec" << endl;
    return 0;
}

test::test(int target_size) : target_size(target_size){
    vector<vector<board>> result;
    for (int i = 0; i < target_size;i++)
    {
        vector<board> row;
        for (int j = 0; j < target_size; j++) {
            if(i==target_size-2 || j==target_size-2){
                row.push_back(board(j, i, true));
            } else {
                row.push_back(board(j,i,false));
            }
        }
        result.push_back(row);
    }
    result[0][target_size - 2].set_status(false);
    result[target_size-2][0].set_status(false);
    result[target_size - 1][target_size - 2].set_status(false);
    result[target_size - 2][target_size - 1].set_status(false);
    target = result;
}

/*
(1,1) 에서 (size-1,size-1) 까지 가는 경우
prev_array에 처음에는 자기 자신을 담고 있음.
*/
void test::search(void) const {
    //Initialize
    queue<board> open_list;
    vector<vector<int>> is_close;
    vector<vector<prev_board>> prev_array;
    for (int i = 0; i < get_target_size(); i++) {
        vector<int> o_row;
        vector<int> d_row;
        vector<prev_board> p_row;
        for (int j = 0; j < get_target_size(); j++) {
            o_row.push_back(0);
            p_row.push_back(prev_board(get_target()[j][i]));
        }
        is_close.push_back(o_row);
        prev_array.push_back(p_row);
    }

    open_list.push(get_target()[1][1]);
    while (1) {
        // cursor_x,y는 queue의 맨 앞에 있는 board의 x,y 좌표
        int cursor_x = open_list.front().get_x();
        int cursor_y = open_list.front().get_y();
        if (cursor_y!=0 && !is_close[cursor_y - 1][cursor_x] && !get_target()[cursor_y - 1][cursor_x].get_status()){
            open_list.push(get_target()[cursor_y - 1][cursor_x]);
            is_close[cursor_y - 1][cursor_x] = 1;
            prev_array[cursor_y - 1][cursor_x] = open_list.front();
            if(check_destination(get_target()[cursor_y - 1][cursor_x])){
                break;
            }
        }
        if(cursor_x!=get_target_size()-1 && !is_close[cursor_y][cursor_x + 1] && !get_target()[cursor_y][cursor_x + 1].get_status()){
            open_list.push(get_target()[cursor_y][cursor_x + 1]);
            is_close[cursor_y][cursor_x + 1] = 1;
            prev_array[cursor_y][cursor_x + 1] = open_list.front();
            if(check_destination(get_target()[cursor_y][cursor_x + 1])){
                break;
            }
        }
        if(cursor_y!=get_target_size()-1 && !is_close[cursor_y + 1][cursor_x] && !get_target()[cursor_y + 1][cursor_x].get_status()){
            open_list.push(get_target()[cursor_y + 1][cursor_x]);
            is_close[cursor_y + 1][cursor_x] = 1;
            prev_array[cursor_y + 1][cursor_x] = open_list.front();
            if(check_destination(get_target()[cursor_y + 1][cursor_x])){
                break;
            }
        }
        if(cursor_x!=0 && !is_close[cursor_y][cursor_x - 1] && !get_target()[cursor_y][cursor_x - 1].get_status()){
            open_list.push(get_target()[cursor_y][cursor_x - 1]);
            is_close[cursor_y][cursor_x - 1] = 1;
            prev_array[cursor_y][cursor_x - 1] = open_list.front();
            if(check_destination(get_target()[cursor_y][cursor_x - 1])){
                break;
            }
        }
        open_list.pop();
    }

    board temp = get_target()[get_target_size() - 1][get_target_size() - 1];
    while (temp.get_x() != 1 || temp.get_y() != 1) {
        cout << temp.get_x() << " " << temp.get_y() << endl;
        temp = prev_array[temp.get_y()][temp.get_x()].get_prev_board();
    }
}

bool test::check_destination(board source) const {
    return source.get_x() == get_target_size() - 1 &&
           source.get_y() == get_target_size() - 1;
}

void test::display_target(void) const {
    for(auto row : get_target()){
        for(auto col : row){
            if(col.get_status()){
                cout << "x ";
            } else {
                cout << "o ";
            }
        }
        cout << endl;
    }
}
