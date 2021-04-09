#include <iostream>
#include "shortest_root.hpp"
#include "kac_man.hpp"

namespace ims{
    shortest_root::shortest_root(kac_man::Map map){
        std::vector<std::vector<kac_man::ObjectStatus>> temp_board=map.get_board();
        for(int i=0;i<map.get_x();i++){
            std::vector<space> temp;
            for(int j=0;j<map.get_y();j++){
                space temp_space(i,j,temp_board[i][j]);
                temp.push_back(temp_space);
            }
            board.push_back(temp);
        }
    }

    void shortest_root::trace(kac_man::Map map){
        kac_man::KacMan temp_kac_man=map.get_kac_man();
        int x=temp_kac_man.get_x();
        int y=temp_kac_man.get_y();
        std::queue<space> board_q;
	    space temp;
	    space ref;

	    board_q.push(board[x][y]);
	    for (int n = 0; board_q.size() > 0; n++) {
	    	while (1) {
	    		temp = board_q.front();
			
	    		if (temp.get_root_num() == n) {
		    		int i = temp.get_x();
		    		int j = temp.get_y();
		    		ref = board[i][j + 1];
		    		if (board[i][j + 1].compare_root_num(n+1)) {
				    	board[i][j+1].set_root_num(n + 1);
				    	board[i][j + 1].push_root_R(temp.get_root());
				    	board_q.push(board[i][j + 1]);
			    	}

			    	ref = board[i + 1][j];
			    	if (board[i + 1][j].compare_root_num(n+1)) {
				    	board[i + 1][j].set_root_num(n + 1);
					    board[i + 1][j].push_root_D(temp.get_root());
				    	board_q.push(board[i + 1][j]);
			    	}

			    	ref = board[i][j - 1];
			    	if (board[i][j - 1].compare_root_num(n+1)) {
			    		board[i][j - 1].set_root_num(n + 1);
			    		board[i][j - 1].push_root_L(temp.get_root());
			    		board_q.push(board[i][j - 1]);
			    	}

			    	ref = board[i - 1][j];
			    	if (board[i - 1][j].compare_root_num(n+1)) {
			    		board[i - 1][j].set_root_num(n + 1);
			    		board[i - 1][j].push_root_U(temp.get_root());
			    		board_q.push(board[i - 1][j]);
			    	}
			    	board_q.pop();
		    	}
		    	else
		    		break;
		    	if (board_q.size() == 0)
			    	break;
		}
	}


    }
}//end of namespace ims