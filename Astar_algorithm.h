#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <iostream>
#include <stack>

class A_star_grid_info{
private:
	int position_x, position_y;
	int cost_g, cost_h, cost_f;
	A_star_grid_info* parent;

public:
	A_star_grid_info(int start_x, int start_y){
		this->position_x = start_x;
		this->position_y = start_y;
		this->cost_g = 0;
		this->cost_h = 0;
		this->cost_f = 0;
		this->parent = NULL;
	}

	int get_position_x(){
		return this->position_x;
	}

	int get_position_y(){
		return this->position_y;
	}

	int get_cost_g(){
		return this->cost_g;
	}

	int get_cost_h(){
		return this->cost_h;
	}

	int get_cost_f(){
		return this->cost_f;
	}

};

//TODO: Need to add grid here to update the map with the best route
int Astar_algorithm(int start_x, int start_y, int end_x, int end_y){
	std::stack<int> open_list;
	std::stack<int> closed_list;

	A_star_grid_info g1_info(start_x, start_y);
	std::cout << g1_info.get_position_x() << " " << g1_info.get_position_y() << std::endl;
	std::cout << end_x << " " << end_y << std::endl;
	

	return 0;
}

#endif // ASTAR_ALGORITHM_H
