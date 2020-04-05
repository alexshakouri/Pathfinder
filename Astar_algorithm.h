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

	A_star_grid_info(){
		this->position_x = 0;
		this->position_y = 0;
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

	void calculate_cost_f(int cost){
		this->cost_f = cost;
	}

};

A_star_grid_info minimum_cost_f(std::stack<A_star_grid_info> list){
	A_star_grid_info min_f = list.top();
	list.pop();
	while(!list.empty()){
		
		if((list.top()).get_cost_f() < min_f.get_cost_f()){
			min_f = list.top();
		}
		list.pop();
	}
	
	return min_f;
	
}

//TODO: Need to add grid here to update the map with the best route
void Astar_algorithm(int start_x, int start_y, int end_x, int end_y){
	std::cout << end_x << " " << end_y << std::endl;
	
	A_star_grid_info start_position(start_x, start_y);

	std::stack<A_star_grid_info> open_list;
	std::stack<A_star_grid_info> closed_list;

	open_list.push(start_position);
	
	A_star_grid_info current_position_info;
	while(!open_list.empty()){
		//Find the minimum F in the open stack
		current_position_info = minimum_cost_f(open_list);
		std::cout << current_position_info.get_cost_f() << std::endl;
		open_list.pop();
		
	}
	


}

#endif // ASTAR_ALGORITHM_H
