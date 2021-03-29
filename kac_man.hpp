
#ifndef __KAC_MAN_HPP__
#define __KAC_MAN_HPP__

#include <ncurses.h>
#include <vector>

namespace kac_man {

//다음은 board의 원소 및 status에 들어갈 변수 목록이다.
enum ObjectStatus { EMPTY, GHOST, KAC_DOT, PAC_MAN, WALL, KAC_MAN, POW_DOT };

// dir_x에 RIGHT,LEFT, dir_y에 UP,DOWN 만이 들어갈 수 있다.
enum Direction { UP = -1, DOWN = 1, RIGHT = 1, LEFT = -1 };

/* 다음 클래스는 게임의 맵이 바뀌더라도 옵션에서 게임 옵션에서 설정할 수 있는
요소들을 모아둔 클래스이다. 유령이 느려질 때의 속도를 weak_speed,
유령/플레이어의 기본 속도를 normal_speed 라고 한다. life는 유저의 목숨 수이다.
[초기값]
weak_speed :
normal_speed :
life : 3
*/
class Variables {
private:
  double weak_speed;
  double normal_speed;
  int life;

public:
  Variables();
  const double get_w_speed(void) { return weak_speed; }
  const double get_n_speed(void) { return normal_speed; }
  const int get_life(void) { return life; }

  void set_w_speed(double new_speed) { weak_speed = new_speed; }
  void set_n_speed(double new_speed) { normal_speed = new_speed; }
  void set_life(int new_life) { life = new_life; }
};

/*
다음은 dot, MovingObject의 부모 클래스이다.
각 객체의 좌표 정보를 담고 있는 x, y를 가지고 있다.

*/
class Object {
private:
  int x;
  int y;

public:
  Object();
  Object(int new_x, int new_y);

  const int get_x(void) { return x; }
  const int get_y(void) { return y; }
  void set_x(int new_x) { x = new_x; }
  void set_y(int new_y) { y = new_y; }
};

/*
다음은 KacMan, Ghost의 부모 클래스이고, Object클래스를 상속받고 있다.
움직이는 객체에 대한 정보이므로 이동방향을 정보로 가지고 있다.
*/
class MovingObject : public Object {
private:
  int dir_x;
  int dir_y;

public:
  MovingObject();
  MovingObject(int new_d_x, int new_d_y);

  const int get_dir_x(void) { return dir_x; }
  const int get_dir_y(void) { return dir_y; }

  void set_dir_x(int new_dir_x) { dir_x = new_dir_x; }
  void set_dir_y(int new_dir_y) { dir_y = new_dir_y; }

  // 이동방향으로 한 칸 움직이는 함수
  // 현재 x,y 좌표 각각에 dir_x, dir_y를 더한다.
  // 다음 이동방향에 다른 객체가 있다면 이 함수를 호출할 수 없다.
  void move();
};

/*
다음은 Object를 변수로 가지고있고, object간의 상호작용에 관련된 함수를
가지고있다. 현재 각 칸의 상태를 표시하는 board, 유령들을 모아둔 ghosts,
pow_dot을 모아둔 pow_dots
kac_dot을 모아둔 kac_dots
kac_man을 가지고 있다.

*/
class ObjectManager {
private:
  std::vector<std::vector<int>> board;
  std::vector<Ghost> ghosts;
  std::vector<PowDot> pow_dots;
  std::vector<KacDot> kac_dots;
  KacMan kac_man;

public:
  // ObjectManger의 초기생성자로서, 모든 object를 map정보, variable정보를 토대로
  // 생성한다.
  ObjectManager();

  std::vector<std::vector<int>> get_board(void) const { return board; }
  std::vector<Ghost> get_ghosts(void) const { return ghosts; }
  std::vector<PowDot> get_pow_dots(void) const { return pow_dots; }
  std::vector<KacDot> get_kac_dots(void) const { return kac_dots; }
  KacMan get_kac_man(void) const { return kac_man; }

  void set_board(std::vector<std::vector<int>> new_board) { board = new_board; }
  void set_ghosts(std::vector<Ghost> new_ghosts) { ghosts = new_ghosts; }
  void set_pow_dots(std::vector<PowDot> new_pow_dots) {
    pow_dots = new_pow_dots;
  }
  void set_kac_dots(std::vector<KacDot> new_kac_dots) {
    kac_dots = new_kac_dots;
  }
  void set_kac_man(KacMan new_kac_man) { kac_man = new_kac_man; }

  /*
    다음은 상호작용에 관한 함수들이다.
    kac_man - ghost가 닿았을 때 호출하는 함수
    man_status에는 오직 kac_man.get_is_strong()이 들어간다.
  */
  void man_ghost_crush(bool man_status);

  /*
    kac_man - kac_dot이 닿았을 때 호출하는 함수
  */
  void man_kdot_crush(void);

  //좌표 x,y에 있는 위치에 vector<dot> dots의 index 반환
  // status == KAC_DOT 이면 vector<dot> kac_dots에서 찾고
  // status == POW_DOT 이면 vector<dot> pow_dots에서 찾음
  // status가 이상한거 들어가면 일부로 에러가 나도록 -1 반환
  int find_dot_num(int x, int y, int status) const;

  /*
     kac_man과 pow_dot이 닿았을 때 호출하는 함수
  */
  void man_pdot_crush(void);
};

/*
  다음은 ghost에 대한 정보를 가지고 있는 객체이다.
  MovingObject를 상속받고있고, 현재 weak상태 여부를 나타내는 bool 변수를
  가지고있다.
  [초기값]
  is_weak = false
*/
class Ghost : public MovingObject {
private:
  bool is_weak;

public:
  Ghost();

  const bool get_status(void) { return is_weak; }
  void set_status(bool new_status) { is_weak = new_status; }
};

/*
  다음은 맵의 필드 위에 있는 점에 대한 클래스이다.
  Object를 상속받고 있고, PowDot, KacDot를 상속하고 있다.
*/
class Dot : public Object {
private:
  bool is_empty;

public:
  Dot();
  Dot(int new_x, int new_y);

  bool get_is_empty(void) const { return is_empty; }

  void set_is_empty(bool new_status) { is_empty = new_status; }
};

/*
  다음은 pow_dot에 관한 클래스이다.
  pow_dot와 kac_man이 닿았을 때,
  ObjectManager클래스의 man-pdot_crush() 호출
*/
class PowDot : public Dot {
public:
  PowDot();
};

/*
  다음은 kac_dot에 관한 클래스이다.
  kac_dot와 kac_man이 닿았을 때
  ObjectManager클래스의 man-kdot_crush() 호출
*/
class KacDot : public Dot {
public:
  KacDot();
};

/*
  다음은 kac_man에 관한 클래스이다.
  strong여부, life수를 변수로 가지고있다.

*/
class KacMan : public MovingObject {
private:
  bool is_strong;
  int life;

public:
  KacMan();
  KacMan(int new_x, int new_y, int new_life);

  int new_life(void) const { return life; }
  bool get_is_strong(void) const { return is_strong; }

  void set_life(int new_life) { life = new_life; }
  void set_is_strong(bool new_status) { is_strong = new_status; }

  /* 현재 life를 1 감소 시킨다.*/
  void decrease_life(void);
};

class GameManager {
private:
  ObjectManager object_manager;
  int score;
  /*윈도우 포인터*/

public:
  GameManager();
  /*
  승리 여부를 검사하는 함수 - <algorithm> 의 std::all_of 를 이용할 것
  */
  const bool check_victory();

  /*패배 여부를 검사하는 함수 - KacMan의 life==0인지 확인*/
  const bool check_defeat();

  /*게임을 종료하는 함수*/
};

class Map {
private:
  std::vector<std::vector<int>> board;
  int ghost_num;
  int pow_num;
  int kac_num;

public:
  std::vector<std::vector<int>> get_board(void) const { return board; }
};

}; // namespace kac_man

#endif
