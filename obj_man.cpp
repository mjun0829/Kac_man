#include "kac_man.hpp"

using namespace kac_man;

void ObjectManager::man_ghost_crush(bool man_status) {
  if (man_status) {
    /*
    ghost -> 리스폰 지역으로
    score 증가
    */
  } else {
    /*
    man -> 리스폰지역으로
    */
    kac_man.decrease_life();
  }
}

void ObjectManager::man_kdot_crush(void) {
  int dot_num = find_dot_num(kac_man.get_x(), kac_man.get_y(), KAC_DOT);
  std::vector<KacDot> result_dots = get_kac_dots();
  result_dots[dot_num].set_is_empty(true);
  set_kac_dots(result_dots);
  // score증가
}

int ObjectManager::find_dot_num(int x, int y, int status) const {
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

void ObjectManager::man_pdot_crush(void) {}
