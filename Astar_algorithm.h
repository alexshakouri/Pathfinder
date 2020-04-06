#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <iostream>
#include <stack>
#include <memory>

#define GRID_SIZE 4
#define COST_PER_MOVE 1

class grid_cost{
private:
	int position_x, position_y;
	int cost_g, cost_h, cost_f;
	std::shared_ptr<grid_cost> parent;

public:
	grid_cost(int x, int y){
		//TODO: Create exception throwing for x,y 
		this->position_x = x;
		this->position_y = y;
		this->cost_g = 0;
		this->cost_h = 0;
		this->cost_f = 0;
		this->parent = NULL;
	}
	grid_cost(){
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
	std::shared_ptr<grid_cost> get_parent(){
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
	void insert_parent(std::shared_ptr<grid_cost> parent){
		this->parent = parent;
	}
};

std::shared_ptr<grid_cost> minimum_cost_f(std::stack<std::shared_ptr<grid_cost>> list){
	std::shared_ptr<grid_cost> min_f = list.top();
	
	list.pop();
	while(!list.empty()){	
		if((list.top())->get_cost_f() < min_f->get_cost_f()){
			min_f = (list.top());
		}
		list.pop();
	}	
	return min_f;
	
}

void delete_element_stack(std::stack<std::shared_ptr<grid_cost>> &list, grid_cost element){
	std::stack<std::shared_ptr<grid_cost>> save_list;

	while(!list.empty()){ 
		//TODO: Implement operator== for the grid_cost class
		//TODO: Create error checks here
		if ((list.top()->get_position_x() == element.get_position_x()) && (list.top()->get_position_y() == element.get_position_y()) 
			&& (list.top()->get_cost_f() == element.get_cost_f()) && (list.top()->get_parent() == element.get_parent())){
			list.pop();
			break;
		}	
		save_list.push(list.top());
		list.pop();
	}
	//Put the elements back into the list
	while(!save_list.empty()){
		list.push(save_list.top());
		save_list.pop();
	}


}

bool find_lower_cost_f(std::stack<std::shared_ptr<grid_cost>> list, int successor_x, int successor_y, int successor_cost_f){
	while(!list.empty()){
		if((list.top())->get_position_x() == successor_x && (list.top())->get_position_y() == successor_y){
			//Assume there can bever be multiple elements in the list that have the same (x,y)
			return ((list.top())->get_cost_f() < successor_cost_f);
		}
		list.pop();
	}
	return false;
}

//TODO: Need to add grid here to update the map with the best route
std::shared_ptr<grid_cost> Astar_algorithm(int start_x, int start_y, int goal_x, int goal_y){
	
	std::shared_ptr<grid_cost> start_position(new grid_cost(start_x, start_y));

	std::stack<std::shared_ptr<grid_cost>> open_list;
	std::stack<std::shared_ptr<grid_cost>> closed_list;

	open_list.push(start_position);
	
	std::shared_ptr<grid_cost> current_position;
	while(!open_list.empty()){
		//Find the minimum F in the open stack
		current_position = minimum_cost_f(open_list);
		delete_element_stack(open_list, *current_position);

		//Generate successor paths
		int successor_x, successor_y;
		for(int x = -1; x < 2; x++){
			for(int y = -1; y < 2; y++){
				if(x == 0 && y == 0){
					continue;
				}
				successor_x = x + current_position->get_position_x();
				successor_y = y + current_position->get_position_y();
				
				//Skip parent node position
				if(current_position->get_parent() != NULL){
						if((current_position->get_parent())->get_position_x() == successor_x && 
								(current_position->get_parent())->get_position_y() == successor_y){
							continue;
						}
				}
				//Need values that are within the GRID_SIZE
				if(successor_x < 0 || successor_y < 0 || successor_x > GRID_SIZE-1 || successor_y > GRID_SIZE-1){
					continue;
				}
				
				std::shared_ptr<grid_cost> successor_position(new grid_cost(successor_x, successor_y));
				successor_position->insert_parent(current_position);

				//Stop search if we are at the end
				if(successor_x == goal_x && successor_y == goal_y){
					//while(successor_position != NULL){
					//std::cout << successor_position->get_position_x() <<  " : " << successor_position->get_position_y() << " F: " << successor_position->get_cost_f() << std::endl;
					//successor_position = (successor_position->get_parent());
					//}
					return successor_position;
				}

				successor_position->calculate_cost_g(current_position->get_cost_g(), COST_PER_MOVE);
				successor_position->calculate_cost_h(goal_x, goal_y);
				successor_position->calculate_cost_f();

				if(find_lower_cost_f(open_list, successor_position->get_position_x(), successor_position->get_position_y(), successor_position->get_cost_f())){
					continue;
				}

				if(find_lower_cost_f(closed_list, successor_position->get_position_x(), successor_position->get_position_y(), successor_position->get_cost_f())){
					continue;
				}

				open_list.push(successor_position);
			}
		}
		//After going through all the successors push current node to closed_list
		closed_list.push(current_position);
	}
	std::cout << "Unable to find path to goal" << std::endl;
	return NULL;
}

#endif // ASTAR_ALGORITHM_H
