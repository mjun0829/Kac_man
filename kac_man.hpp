
#ifndef __KAC_MAN_HPP__
#define __KAC_MAN_HPP__

#include <ncurses.h>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <random>
#include <cstdlib>
#include <functional>
#include <pthread.h>

namespace kac_man
{

  //다음은 board의 원소 및 status에 들어갈 변수 목록이다.
  enum ObjectStatus
  {
    EMPTY,
    WALL,
    KAC_MAN,
    GHOST,
    KAC_DOT,
    POW_DOT
  };

  // dir_x에 RIGHT,LEFT, dir_y에 UP,DOWN 만이 들어갈 수 있다.
  enum Direction
  {
    UNDIRECT = 0,
    UP = -1,
    DOWN = 1,
    RIGHT = 1,
    LEFT = -1
  };

  /* 다음 클래스는 게임의 맵이 바뀌더라도 옵션에서 게임 옵션에서 설정할 수 있는
요소들을 모아둔 클래스이다. 유령이 느려질 때의 속도를 weak_speed,
유령/플레이어의 기본 속도를 normal_speed 라고 한다. life는 유저의 목숨 수이다.
[초기값]
weak_speed :
normal_speed :
life : 3
*/
  class Variables
  {
  private:
    double weak_speed;
    double normal_speed;
    int life;

  public:
    Variables();
    double get_w_speed(void) const { return weak_speed; }
    double get_n_speed(void) const { return normal_speed; }
    int get_life(void) const { return life; }

    void set_w_speed(double new_speed) { weak_speed = new_speed; }
    void set_n_speed(double new_speed) { normal_speed = new_speed; }
    void set_life(int new_life) { life = new_life; }
  };

  /*
다음은 dot, MovingObject의 부모 클래스이다.
각 객체의 좌표 정보를 담고 있는 x, y를 가지고 있다.
*/
  class Object
  {
  private:
    int x;
    int y;

  public:
    Object(int new_x, int new_y);

    int get_x(void) const { return x; }
    int get_y(void) const { return y; }
    void set_x(int new_x) { x = new_x; }
    void set_y(int new_y) { y = new_y; }
  };

  /*
다음은 KacMan, Ghost의 부모 클래스이고, Object클래스를 상속받고 있다.
움직이는 객체에 대한 정보이므로 이동방향을 정보로 가지고 있다.
*/
  class MovingObject : public Object
  {
  private:
    int dir_x;
    int dir_y;

  public:
    MovingObject(int new_d_x, int new_d_y, int new_x, int new_y);

    int get_dir_x(void) const { return dir_x; }
    int get_dir_y(void) const { return dir_y; }


    void set_dir_x(int new_dir_x) { dir_x = new_dir_x; }
    void set_dir_y(int new_dir_y) { dir_y = new_dir_y; }


    // 이동방향으로 한 칸 움직이는 함수
    // 현재 x,y 좌표 각각에 dir_x, dir_y를 더한다.
    // 다음 이동방향에 다른 객체가 있다면 이 함수를 호출할 수 없다.
    void move();
  };

  /*
  다음은 ghost에 대한 정보를 가지고 있는 객체이다.
  MovingObject를 상속받고있고, 현재 weak상태 여부를 나타내는 bool 변수를
  가지고있다.
  [초기값]
  is_weak = false
  알고리즘 함수를 가리키는 함수포인터를 이용해서 ghost의 움직임을 제어할 예정
*/
  class Ghost : public MovingObject
  {
  private:
    bool is_weak;

  // 알고리즘을 가르키는 포인터
    std::function<void(ObjectManager&)> algo_ptr;
  public:
    Ghost(int pos_x, int pos_y, int dir_x, int dir_y);
    bool get_status(void) const { return is_weak; }
    void set_status(bool new_status) { is_weak = new_status; }
    void set_algo_ptr(std::function<void(ObjectManager&)> new_algorithm) {
      algo_ptr = new_algorithm;
    }
    void execute_algorithm(ObjectManager OM);
  };

  /*
  다음은 kac_man에 관한 클래스이다.
  strong여부, life수를 변수로 가지고있다.
  */
  class KacMan : public MovingObject
  {
  private:
    bool is_strong;
    int life;

  public:
  //KacMan 의 초기 dir_x, dir_y는 UNDIRECT
    KacMan(int new_x, int new_y, int new_life);

    int new_life(void) const { return life; }
    bool get_is_strong(void) const { return is_strong; }

    void set_life(int new_life) { life = new_life; }
    void set_is_strong(bool new_status) { is_strong = new_status; }

    /* 현재 life를 1 감소 시킨다.*/
    void decrease_life(void);
  };

  /*
  다음은 맵의 필드 위에 있는 점에 대한 클래스이다.
  Object를 상속받고 있고, PowDot, KacDot를 상속하고 있다.
  */
  class Dot : public Object
  {
  private:
    bool is_empty;

  public:
    Dot(int new_x, int new_y);

    bool get_is_empty(void) const { return is_empty; }

    void set_is_empty(bool new_status) { is_empty = new_status; }
  };

  /*
  다음은 pow_dot에 관한 클래스이다.
  pow_dot와 kac_man이 닿았을 때,
  ObjectManager클래스의 man-pdot_crush() 호출
  */
  class PowDot : public Dot
  {
  public:
    PowDot(int new_x, int new_y);
  };

  /*
  다음은 kac_dot에 관한 클래스이다.
  kac_dot와 kac_man이 닿았을 때
  ObjectManager클래스의 man-kdot_crush() 호출
*/
  class KacDot : public Dot
  {
  public:
    KacDot(int new_x, int new_y);
  };

  /*
맵 정보를 담고 있는 클래스
ObjectManager의 private 변수들의 초기값들을 저장하고있음.
추후 맵에디터를 제작할 때 반환값으로 쓰일 클래스
맵 크기는 row_num, col_num으로 표현
*/
  class Map
  {
  private:
    std::vector<std::vector<int>> board;
    std::vector<Ghost> ghosts;
    std::vector<PowDot> pow_dots;
    std::vector<KacDot> kac_dots;
    KacMan kac_man;
    std::vector<Object> man_respawn_spots;
    std::vector<Object> ghost_respawn_spots;
    int col_num;
    int row_num;

  public:
    Map::Map(std::vector<std::vector<int>> board,
             std::vector<Ghost> ghosts, std::vector<PowDot> pow_dots,
             std::vector<KacDot> kac_dots, KacMan kac_man,
             std::vector<Object> man_respawn_spots,
             std::vector<Object> ghost_respawn_spots, int col_num, int row_num);
    std::vector<std::vector<int>> get_board(void) const { return board; }
    std::vector<Ghost> get_ghosts(void) const { return ghosts; }
    std::vector<PowDot> get_pow_dots(void) const { return pow_dots; }
    std::vector<KacDot> get_kac_dots(void) const { return kac_dots; }
    KacMan get_kac_man(void) const { return kac_man; }
    int get_col_num(void) const { return col_num; }
    int get_row_num(void) const { return row_num; }
    std::vector<Object> get_man_respawn_spots() const
    {
      return man_respawn_spots;
    }
    std::vector<Object> get_ghost_respawn_spots() const
    {
      return ghost_respawn_spots;
    }
    int get_ObjectStatus(int x, int y) { return board[x][y]; }

    void set_board(std::vector<std::vector<int>> new_board)
    {
      board = new_board;
    }
    void set_ghosts(std::vector<Ghost> new_ghosts) { ghosts = new_ghosts; }
    void set_pow_dots(std::vector<PowDot> new_pow_dots)
    {
      pow_dots = new_pow_dots;
    }
    void set_kac_dots(std::vector<KacDot> new_kac_dots)
    {
      kac_dots = new_kac_dots;
    }
    void set_kac_man(KacMan new_kac_man) { kac_man = new_kac_man; }
    void set_col_num(int new_col_num) { col_num = new_col_num; }
    void set_row_num(int new_row_num) { row_num = new_row_num; }
  };

  /*
다음은 Object를 변수로 가지고있고, object간의 상호작용에 관련된 함수를
가지고있다. 현재 각 칸의 상태를 표시하는 board, 유령들을 모아둔 ghosts,
pow_dot을 모아둔 pow_dots
kac_dot을 모아둔 kac_dots
kac_man을 가지고 있다.
*/
  class ObjectManager : public Map
  {
  private:
    Variables variables;

    // power 지속시간 5초를 재는 타이머이다.
    pthread_t power_timer;

    // ghost들이 모두 랜덤알고리즘을 가지고 움직이는 시간 10초를 재는 타이머이다.
    pthread_t rand_timer;

  public:
    // ObjectManger의 초기생성자로서, 모든 object를 map정보, variable정보를 토대로
    // 생성한다.
    ObjectManager(std::vector<std::vector<int>> board,
                  std::vector<Ghost> ghosts, std::vector<PowDot> pow_dots,
                  std::vector<KacDot> kac_dots, KacMan kac_man,
                  std::vector<Object> man_respawn_spots,
                  std::vector<Object> ghost_respawn_spots, int col_num, int row_num,
                  Variables new_variables);
    Variables get_variables(void) const { return variables; }

  // 유저가 맵을 선택하면 다음 함수를 호출해서 private변수를 바꿔놓아야한다.
    void set_map(Map new_map);
    void set_variables(Variables new_variables) { variables = new_variables; }

    // thread가 쓸 함수이다.
    // parameter로 초를 넣으면 그 시간 만큼 시간을 잰다.
    void timer(int seconds);

    //rand_timer를 활성화시킨다.
    void activate_rand_timer(void);

    /*
    다음은 상호작용에 관한 함수들이다.
    kac_man - ghost가 닿았을 때 호출하는 함수
    is_man_strong에는 오직 kac_man.get_is_strong()이 들어간다.
    */
    void man_ghost_crush(bool is_man_strong);

    // target_ghost의 현재 위치를 리스폰지역으로 보냄.
    void ghost_respawn(Ghost target_ghost);

    //(x,y)에 해당하는 ghost의 index를 반환함
    int find_target_ghost();

    // target_kac_man의 현재 위치를 리스폰지역으로 보냄.
    void man_respawn(KacMan target_kac_man);

    //kac_man - kac_dot이 닿았을 때 호출하는 함수
    void man_kdot_crush(void);

    // ghost가 Kac_man을 향해 최단거리로 움직인다.
    // Map을 매개변수로 받아 dir_x와 dir_y값을 변경.
    void ghost_trace(void);

    // ghost가 랜덤으로 움직인다.
    // Map을 매개변수로 받아 dir_x와 dir_y값을 변경.
    void ghost_random(void);

    // ghost가 Kac_man으로부터 멀어지게 움직인다.
    // Map을 매개변수로 받아 dir_x와 dir_y값을 변경.
    void ghost_away(void);

    //좌표 x,y에 있는 위치에 vector<dot> dots의 index 반환
    // status == KAC_DOT 이면 vector<dot> kac_dots에서 찾고
    // status == POW_DOT 이면 vector<dot> pow_dots에서 찾음
    // status가 이상한거 들어가면 일부로 에러가 나도록 -1 반환
    int find_target_dot_num(int x, int y, int status) const;

    // kac_man과 pow_dot이 닿았을 때 호출하는 함수
    void man_pdot_crush(void);

    // 다음은 고스트들이 지정되어있는 알고리즘을 동작하게 하는 함수이다.
    // 이 함수를 호출하면 알고리즘이 실행되어서 ghost의 dir을 결정한다.
    void execute_ghost_algo(void);

    // 다음은 man_pdot_cursh에서 호출할 함수이다.
    // 모든 고스트의 weak = true로 만든다.
    // kac_man의 is_strong = true로 만든다.
    void make_all_ghost_weak(void);

    // 다음은 5초를 제는 쓰레드를 활성화시킨다.
    // man_pdot_crush에서 호출할 함수이다.
    void activate_power_timer(void);

    // 다음은 thread_timer로부터 시그널을 받으면 호출할 함수이다.
    // 모든 고스트의 weak = false로 만든다.
    // kac_man의 is_strong = true로 만든다.
    void make_all_ghost_strong(void);
  };

  /*
  게임 실행에 관련되어있는 최상위 클래스
  */
  class GameManager
  {
  private:
    ObjectManager object_manager;
    int score;
    /*윈도우 포인터*/
    WINDOW *main_scr;
    WINDOW *game_scr;
    WINDOW *game_score_scr;
    WINDOW *option_map_view_scr;
    WINDOW *option_map_select_scr;

  public:
    GameManager();
    WINDOW *get_main_scr() const { return main_scr; }
    WINDOW *get_game_scr() const { return game_scr; }
    WINDOW *get_game_score_scr() const { return game_scr; }
    WINDOW *get_map_view_scr() const { return option_map_view_scr; }
    WINDOW *get_map_select_scr() const { return option_map_select_scr; }
    void init_ncurses();
    void set_main_scr(WINDOW *ptr) { main_scr = ptr; }
    void set_game_scr(WINDOW *ptr) { game_scr = ptr; }
    void set_game_score_scr(WINDOW *ptr) { game_score_scr = ptr; }
    void set_map_view_scr(WINDOW *ptr) { option_map_view_scr = ptr; }
    void set_map_select_scr(WINDOW *ptr) { option_map_select_scr = ptr; }
    WINDOW *make_scr(int max_y, int max_x, int start_y, int start_x);
    void print_game_init_objs();
    void print_game_repeat_objs();
    void load_map();
    void keypad_manage();
    /*
  승리 여부를 검사하는 함수 - <algorithm> 의 std::all_of 를 이용할 것
  */
    bool check_victory() const;
    //
    /*패배 여부를 검사하는 함수 - KacMan의 life==0인지 확인*/
    bool check_defeat() const;

    /*게임을 종료하는 함수*/
  };

  /*
	클래스 space
	(x,y)좌표의 status값을 가지고 있다.
	board 클래스와 비슷하나 root_num(최단거리)과 root(최단 루트) 변수 추가.
	*/
  class space
  {
  private:
    int x;                      //보드 x 좌표
    int y;                      //보드 y 좌표
    int status;                 //현재 보드의 상태 1:EMPTY 2:WALL 3:GHOST 4:KAC_MAN
    int root_num;               //KAC_MAN부터 현재 지점까지의 최단거리
    std::stack<char> root;      //KAC_MAN부터 현재 지점까지의 최단 루트 RLUD를 이용하여 배열
    const int INFINITE = 10000; //무한
  public:
    space();
    space(int new_x, int new_y, int new_status); //생성자 (X,Y)값의 status값을 받아서 설정.
    void set_x(int new_x) { x = new_x; }
    void set_y(int new_y) { y = new_y; }
    void set_status(int new_status) { status = new_status; }
    void set_root_num(int new_root_num) { root_num = new_root_num; }
    void set_space(int new_x, int new_y, int status);
    void push_root_R(std::stack<char> ref)
    {
      root = ref;
      root.push('R');
    } //root 에 R 대입
    void push_root_L(std::stack<char> ref)
    {
      root = ref;
      root.push('L');
    } //root 에 L 대입
    void push_root_U(std::stack<char> ref)
    {
      root = ref;
      root.push('U');
    } //root 에 U 대입
    void push_root_D(std::stack<char> ref)
    {
      root = ref;
      root.push('D');
    } //root 에 D 대입
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_status() const { return status; }
    int get_root_num() const { return root_num; }
    std::stack<char> get_root() const { return root; }
    char get_root_dir() const { return root.top(); } //root(stack)의 마지막 방향을 리턴한다.
    space &operator=(const space &ref)
    {
      x = ref.x;
      y = ref.y;
      status = ref.status;
      root_num = ref.root_num;
      root = ref.root;
      return *this;
    }
    bool compare_root_num(int n) { return n < root_num; } //현재의 root_num과 n 값을 비교하여 n이 작으면 TRUE n이 크면 FALSE 리턴
  };

  /*
	클래스 shortest_root
	최단거리 알고리즘 정의한 클래스
	Map 클래스를 받아와 2차원 배열 board를 정의한다.
	trace 함수를 통해서 모든 칸의 최단경로를 업데이트 한다.(WALL제외)
	*/
  class shortest_root
  {
  private:
    std::vector<std::vector<space>> board;

  public:
    shortest_root(kac_man::Map map); //map 클래스 받아와서 2차원 배열 각각의 칸에 space를 정의한다. 정의함과 동시에 최단경로 추적 시작.
    std::vector<std::vector<space>> get_board() const { return board; }
    space get_space(int x, int y) const { return board[x][y]; }
    void set_board(kac_man::Map map); //board를 다시 현재 map상태로 바꾼다. 바꿈과 동시에 최단경로 추적 시작.
    void trace(kac_man::Map map);     //최단거리 알고리즘
  };
}; // namespace kac_man

#endif
