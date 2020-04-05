#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <iostream>
#include <stack>

#define GRID_SIZE 4
#define COST_PER_MOVE 1

class A_star_grid_info{
private:
	int position_x, position_y;
	int cost_g, cost_h, cost_f;
	A_star_grid_info* parent;

public:
	A_star_grid_info(int x, int y){
		//TODO: Create exception throwing for x,y 
		this->position_x = x;
		this->position_y = y;
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

	A_star_grid_info* get_parent(){
		return this->parent;
	}

	void calculate_cost_f(){
		this->cost_f = this->cost_g + this->cost_h;
	}

	void calculate_cost_g(int parent_cost_g, int distance_cost){
		this->cost_g = parent_cost_g + distance_cost;
	}

	void calculate_cost_h(int goal_x, int goal_y){
		//Diagonal Distance for 8 possible moves
		this->cost_h = std::max( abs(this->position_x - goal_x), abs(this->position_y - goal_y));
	}
	void insert_parent(A_star_grid_info* parent){
		this->parent = parent;
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

bool find_lower_cost_f(std::stack<A_star_grid_info> list, int successor_x, int successor_y, int successor_cost_f){
	while(!list.empty()){
		if((list.top()).get_position_x() == successor_x && (list.top()).get_position_y() == successor_y){
			//TODO: Make sure that there can bever be multiple elements in the list that have the same (x,y)
			return ((list.top()).get_cost_f() < successor_cost_f);
		}
		list.pop();
	}
	return false;
}

//TODO: Need to add grid here to update the map with the best route
void Astar_algorithm(int start_x, int start_y, int goal_x, int goal_y){
	
	A_star_grid_info start_position(start_x, start_y);

	std::stack<A_star_grid_info> open_list;
	std::stack<A_star_grid_info> closed_list;

	open_list.push(start_position);
	
	A_star_grid_info current_position_info;
	while(!open_list.empty()){
		//Find the minimum F in the open stack
		current_position_info = minimum_cost_f(open_list);
		//std::cout << current_position_info.get_cost_f() << std::endl;
		//TODO::I NEED to fix the POP here (I'm not popping the right element
		open_list.pop();

		//Generate successor paths
		int successor_x, successor_y;
		for(int x = -1; x < 2; x++){
			for(int y = -1; y < 2; y++){
				if(x == 0 && y == 0){
					continue;
				}
				successor_x = x + current_position_info.get_position_x();
				successor_y = y + current_position_info.get_position_y();
				

				//Skip parent node position
				if(current_position_info.get_parent() != NULL){
						if((current_position_info.get_parent())->get_position_x() == successor_x && 
								(current_position_info.get_parent())->get_position_y() == successor_y){
							continue;
						}
				}

				//Need values that are within the GRID_SIZE
				if(successor_x < 0 || successor_y < 0 || successor_x > GRID_SIZE-1 || successor_y > GRID_SIZE-1){
					continue;
				}
				
				A_star_grid_info successor_position_info(successor_x, successor_y);
				successor_position_info.insert_parent(&current_position_info);
				std::cout << "succussor: " << successor_x << " " << successor_y << " parent: " << current_position_info.get_position_x() << " " << current_position_info.get_position_y() << " F: " << current_position_info.get_cost_f() << std::endl;


				//Stop search if we are at the end
				if(successor_x == goal_x && successor_y == goal_y){
					while(successor_position_info.get_parent() != NULL){
					std::cout << successor_position_info.get_position_x() <<  " : " << successor_position_info.get_position_y() << " F: " << successor_position_info.get_cost_f() << std::endl;
					std::cout << successor_position_info.get_parent()->get_position_x() <<  " : " << successor_position_info.get_parent()->get_position_y() << " F: " << successor_position_info.get_parent()->get_cost_f() << std::endl;
					std::cout << successor_position_info.get_parent()->get_parent()->get_position_x() <<  " : " << successor_position_info.get_parent()->get_parent()->get_position_y() << " F: " << successor_position_info.get_parent()->get_parent()->get_cost_f() << std::endl;
					successor_position_info = *(successor_position_info.get_parent());
					break;
					}
					return;
				}

				successor_position_info.calculate_cost_g(current_position_info.get_cost_g(), COST_PER_MOVE);
				//std::cout << successor_position_info.get_cost_g() << " : " << successor_position_info.get_cost_f() << std::endl; 
				successor_position_info.calculate_cost_h(goal_x, goal_y);

				successor_position_info.calculate_cost_f();
				//std::cout << "F: " << successor_position_info.get_cost_f() << std::endl;
				//std::cout << " pos:" << successor_position_info.get_position_x() << " " << successor_position_info.get_position_y() << std::endl;

				if(find_lower_cost_f(open_list, successor_position_info.get_position_x(), successor_position_info.get_position_y(), successor_position_info.get_cost_f())){
					continue;
				}

				if(find_lower_cost_f(closed_list, successor_position_info.get_position_x(), successor_position_info.get_position_y(), successor_position_info.get_cost_f())){
					continue;
				}

				open_list.push(successor_position_info);
			}
		}
		//After going through all the successors push current node to closed_list
		closed_list.push(current_position_info);
	}
	


}

#endif // ASTAR_ALGORITHM_H
