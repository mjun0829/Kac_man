#include "kac_man.hpp"

using namespace kac_man;

Variables::Variables() {
  /*
  값을 정해야함
  */
  life = 3;
}

Object::Object(int new_x, int new_y) : x(new_x), y(new_y) {}

MovingObject::MovingObject(int new_d_x, int new_d_y, int new_x, int new_y)
    : dir_x(new_d_x), dir_y(new_d_y), Object(new_x, new_y) {}

void MovingObject::move() {
  int temp_x = get_x();
  int temp_y = get_y();
  temp_x += get_dir_x();
  temp_y += get_dir_y();
  set_x(temp_x);
  set_y(temp_y);
}

Ghost::Ghost(int pos_x,int pos_y,int dir_x, int dir_y)
    : MovingObject(dir_x, dir_y, pos_x, pos_y) {
  is_weak = false;
  algo_ptr = &ObjectManager::ghost_random;
}

void Ghost::execute_algorithm(ObjectManager OM){
  algo_ptr(OM);
}

KacMan::KacMan(int new_x, int new_y, int new_life)
 : MovingObject(UNDIRECT, UNDIRECT, new_x, new_y) {
   is_strong = false;
   life = new_life;
}

Dot::Dot(int new_x, int new_y) : Object(new_x, new_y) {
  is_empty = false;
}

PowDot::PowDot(int new_x, int new_y) : Dot(new_x, new_y) {}

KacDot::KacDot(int new_x, int new_y) : Dot(new_x, new_y) {}

Map::Map(std::vector<std::vector<int>> board,
         std::vector<Ghost> ghosts, std::vector<PowDot> pow_dots,
         std::vector<KacDot> kac_dots, KacMan kac_man,
         std::vector<Object> man_respawn_spots,
         std::vector<Object> ghost_respawn_spots, int col_num, int row_num){
    this->board = board;
    this->pow_dots = pow_dots;
    this->ghosts = ghosts;
    this->kac_dots = kac_dots;
    this->kac_man = kac_man;
    this->man_respawn_spots = man_respawn_spots;
    this->ghost_respawn_spots = ghost_respawn_spots;
    this->col_num = col_num;
    this->row_num = row_num;
}

ObjectManager::ObjectManager(std::vector<std::vector<int>> board,
    std::vector<Ghost> ghosts, std::vector<PowDot> pow_dots,
    std::vector<KacDot> kac_dots, KacMan kac_man,
    std::vector<Object> man_respawn_spots,
    std::vector<Object> ghost_respawn_spots, int col_num, int row_num,
    Variables new_variables) : Map(board, ghosts, pow_dots, kac_dots,
      kac_man, man_respawn_spots, ghost_respawn_spots, col_num,row_num) {
  variables = new_variables;
  power_timer = pthread_create(ㄷ)
}

void ObjectManager::set_map(Map new_map) {
  set_board(new_map.get_board());
  set_ghosts(new_map.get_ghosts());
  set_pow_dots(new_map.get_pow_dots());
  set_kac_dots(new_map.get_kac_dots());
  set_kac_man(new_map.get_kac_man());
}

void ObjectManager::man_ghost_crush(bool is_man_strong) {
  if (is_man_strong) {
    std::vector<Ghost> temp_ghost = get_ghosts();
    ghost_respawn(temp_ghost[find_target_ghost()]);
    /*
    score 증가
    */
  } else {
    KacMan temp_kac_man = get_kac_man();
    man_respawn(temp_kac_man);
    temp_kac_man.decrease_life();
    set_kac_man(temp_kac_man);
  }
}

void ObjectManager::man_kdot_crush(void) {
  KacMan temp_kac_man = get_kac_man();
  int target_dot_num =
      find_target_dot_num(temp_kac_man.get_x(), temp_kac_man.get_y(), KAC_DOT);
  std::vector<KacDot> result_dots = get_kac_dots();
  result_dots[target_dot_num].set_is_empty(true);
  set_kac_dots(result_dots);
  set_kac_man(temp_kac_man);
  // score증가
}

int ObjectManager::find_target_dot_num(int x, int y, int status) const {
  int index = 0;
  if (status == KAC_DOT) {
    for (auto kac_dot : get_kac_dots()) {
      if (kac_dot.get_x() == x && kac_dot.get_y() == y) {
        return index;
      }
      index++;
    }
  } else if (status == POW_DOT) {
    for (auto pow_dot : get_pow_dots()) {
      if (pow_dot.get_x() == x && pow_dot.get_y() == y) {
        return index;
      }
      index++;
    }
  } else {
    return -1;
  }
}

void ObjectManager::man_pdot_crush(void) {
  KacMan temp_kac_man = get_kac_man();
  temp_kac_man.set_is_strong(true);
  int target_dot_num =
      find_target_dot_num(temp_kac_man.get_x(), temp_kac_man.get_y(), POW_DOT);
  std::vector<PowDot> result_dots = get_pow_dots();
  result_dots[target_dot_num].set_is_empty(true);
  std::vector<Ghost> temp_ghosts = get_ghosts();
  for (auto one_ghost : temp_ghosts) {
    one_ghost.set_status(true);
  }
  set_pow_dots(result_dots);
  set_kac_man(temp_kac_man);
  set_ghosts(temp_ghosts);
  /*ghost가 man으로부터 멀어지는 알고리즘 호출*/
  /*일정 시간이 지난 후 kacman, ghost의 상태 Default로 수정되어야함*/
}
