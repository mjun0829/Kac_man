#include "kac_man.hpp"

using namespace kac_man;


void Ghost::ghost_trace(Map ref_map)
{
    shortest_root ref_short(ref_map);
    space ref_space;
    ref_space = ref_short.get_space(get_x(), get_y());
    char ref_direct = ref_space.get_root_dir();
    if (ref_direct == 'R')
    {
        set_dir_x(LEFT);
        set_dir_y(UNDIRECT);
    }
    else if (ref_direct == 'L')
    {
        set_dir_x(RIGHT);
        set_dir_y(UNDIRECT);
    }
    else if (ref_direct == 'U')
    {
        set_dir_x(UNDIRECT);
        set_dir_y(DOWN);
    }
    else if (ref_direct == 'D')
    {
        set_dir_x(UNDIRECT);
        set_dir_y(UP);
    }
    else
    {
        set_dir_x(LEFT);
        set_dir_y(UNDIRECT);
    }
}

void Ghost::ghost_random(Map ref_map)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rand_100(0, 99); //random 으로 0부터 99사이 난수 생성

    if (rand_100(gen) == 0)
    {
        std::vector<char> dir;
        if (ref_map.get_ObjectStatus(get_x() + abs(get_dir_x()) - 1, get_y() + abs(get_dir_y()) - 1) != WALL){
            dir.push_back('a');
        }
        if (ref_map.get_ObjectStatus(get_x() - abs(get_dir_x()) + 1, get_y() - abs(get_dir_y()) + 1) != WALL){
            dir.push_back('b');
        }
        if(ref_map.get_ObjectStatus(get_x()-get_dir_x(),get_y()-get_dir_y())!=WALL){
            dir.push_back('c');
        }
        char dir_result = dir[rand_100(gen) % dir.size()];
        switch(dir_result){
            case 'a':
                set_dir_x(abs(get_dir_x()) - 1);
                set_dir_y(abs(get_dir_y()) - 1);
                
                break;
            case 'b':
                set_dir_x(1 - abs(get_dir_x()));
                set_dir_y(1 - abs(get_dir_y()));
                
                break;
            case 'c':
                set_dir_x(-get_dir_x());
                set_dir_y(-get_dir_y());
                
                break;
            default:
                break;
            }
    }
    else
    {
        if (ref_map.get_ObjectStatus(get_x() + get_dir_x(), get_y() + get_dir_y()) == WALL)
        {
            if (ref_map.get_ObjectStatus(get_x() + abs(get_dir_x()) - 1, get_y() + abs(get_dir_y()) - 1) == WALL 
            && ref_map.get_ObjectStatus(get_x() - abs(get_dir_x()) + 1, get_y() - abs(get_dir_y()) + 1) == WALL)
            {
                set_dir_x(-get_dir_x());
                set_dir_y(-get_dir_y());
                
            }
            else
            {
                std::vector<char> dir;
                if (ref_map.get_ObjectStatus(get_x() + abs(get_dir_x()) - 1, get_y() + abs(get_dir_y()) - 1) != WALL)
                {
                    dir.push_back('a');
                }
                if (ref_map.get_ObjectStatus(get_x() - abs(get_dir_x()) + 1, get_y() - abs(get_dir_y()) + 1) != WALL)
                {
                    dir.push_back('b');
                }
                char dir_result = dir[rand_100(gen)%dir.size()];
                switch(dir_result){
                    case 'a':
                        set_dir_x(abs(get_dir_x())-1);
                        set_dir_y(abs(get_dir_y())-1);
                        
                        break;
                    case 'b':
                        set_dir_x(1-abs(get_dir_x()));
                        set_dir_y(1-abs(get_dir_y()));
                        
                        break;
                    default:
                        break;
                    }
            }
        }
        else
        {
        }
    }
}

void Ghost::ghost_away(Map ref_map)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rand_100(0, 99); //random 으로 0부터 99사이 난수 생성

    shortest_root ref_short(ref_map);
    space ref_space;
    ref_space = ref_short.get_space(get_x(), get_y());
    char ref_direct = ref_space.get_root_dir();
    int ref_dir_x;
    int ref_dir_y;
    switch (ref_direct)
    {
    case 'R':
        ref_dir_x = 1;
        ref_dir_y = 0;
        break;
    case 'L':
        ref_dir_x = -1;
        ref_dir_y = 0;
        break;
    case 'U':
        ref_dir_x = 0;
        ref_dir_y = -1;
        break;
    case 'D':
        ref_dir_x = 0;
        ref_dir_y = 1;
        break;
    default:
        break;
    }

    std::vector<char> dir;
    if (ref_map.get_ObjectStatus(get_x() + abs(ref_dir_x) - 1, get_y() + abs(ref_dir_y) - 1) != WALL)
    {
        dir.push_back('a');
    }
    if (ref_map.get_ObjectStatus(get_x() - abs(ref_dir_x) + 1, get_y() - abs(ref_dir_y) + 1) != WALL)
    {
        dir.push_back('b');
    }
    if (ref_map.get_ObjectStatus(get_x() - ref_dir_x, get_y() - ref_dir_y) != WALL)
    {
        dir.push_back('c');
    }

    char dir_result = dir[rand_100(gen) % dir.size()];
    switch (dir_result)
    {
    case 'a':
        set_dir_x(abs(ref_dir_x) - 1);
        set_dir_y(abs(ref_dir_y) - 1);
        break;
    case 'b':
        set_dir_x(1 - abs(ref_dir_x));
        set_dir_y(1 - abs(ref_dir_y));
        break;
    case 'c':
        set_dir_x(-ref_dir_x);
        set_dir_y(-ref_dir_y);
        break;
    default:
        break;
    }
}