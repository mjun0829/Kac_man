#ifndef __SHORTEST_ROOT__
#define __SHORTEST_ROOT__

#include <iostream>
#include <vector>
#include <queue>

namespace ims {
	class space {
	private:
		int x;
		int y;
		int status;
		int root_num;
		std::vector<char> root;
	public:
		space();
		space(int new_x, int new_y, int new_status);
		void set_x(int new_x) { x = new_x; }
		void set_y(int new_y) { y = new_y; }
		void set_status(int new_status) { status = new_status; }
		void set_root_num(int new_root_num) { root_num = new_root_num; }
		void set_space(int new_x, int new_y, int status);
		void push_root_R(std::vector<char> ref) { root = ref; root.push_back('R'); }
		void push_root_L(std::vector<char> ref) { root = ref; root.push_back('L'); }
		void push_root_U(std::vector<char> ref) { root = ref; root.push_back('U'); }
		void push_root_D(std::vector<char> ref) { root = ref; root.push_back('D'); }
		const int get_x() { return x; }
		const int get_y() { return y; }
		const int get_status() { return status; }
		const int get_root_num() { return root_num; }
		const std::vector<char> get_root(){ return root; }
		space& operator=(const space &ref) { x = ref.x; y = ref.y; status = ref.status; root_num = ref.root_num; root = ref.root; return *this; }
		bool compare_root_num(int n);
	};

	class shortest_root {
	private:
		std::vector<std::vector<space>> board;
	public:
		shortest_root();
		void trace();
	};
	
	space::space() {
		int x = 0;
		int y = 0;
		int status = 0;
		int root_num = 0;
	}

	space::space(int new_x, int new_y, int new_status) {
		x = new_x;
		y = new_y;
		status = new_status;
		if (new_status == 0)
			root_num = 10000;
		else if (new_status == 1)
			root_num = -1;
		else if (new_status == 2)
			root_num = 0;
		else if (new_status == 3)
			root_num = 10000;
		else
			root_num = 10000;
	}

	void space::set_space(int new_x, int new_y, int new_status) {
		x = new_x;
		y = new_y;
		status = new_status;
		if (new_status == 0)
			root_num = 10000;
		else if (new_status == 1)
			root_num = -1;
		else if (new_status == 2)
			root_num = 0;
		else if (new_status == 3)
			root_num = 10000;
		else
			root_num = 10000;
	}

	bool space::compare_root_num(int n) {
		if (n < root_num)
			return 1;
		else
			return 0;
	}
}

#endif