#include "Astar_algorithm.h"
#include "grid_definition.h"

int main(){

	grid g1;
	//TODO:Implement test cases
	Point start_point = {0,8};
	Point end_point = {9,9};
	//Define start and end point
	g1.insert_point(start_point,'S');
	g1.insert_point(end_point,'F');

	//Insert blockage
	Point p1 = {8,9};
	Point p2 = {8,8};
	Point p3 = {8,7};
	Point p4 = {8,6};
	g1.insert_point(p1,BLOCKAGE);
	g1.insert_point(p2,BLOCKAGE);
	g1.insert_point(p3,BLOCKAGE);
	g1.insert_point(p4,BLOCKAGE);


	std::shared_ptr<Astar_cost> Astar_path;
	Astar_path = Astar_algorithm(&g1,start_point,end_point);

	insert_path(&g1,Astar_path);
	g1.print_grid();	

	return 0;
}

//Overload the equal operator
bool operator==(const Point &position1, const Point &position2){
	return ((position1.x == position2.x) && (position1.y == position2.y));
}

bool operator==(const Astar_cost &grid1, const Astar_cost &grid2){
	return ((grid1.get_position() == grid2.get_position())
		       	&& (grid1.get_cost_g() == grid2.get_cost_g()) && (grid1.get_cost_h() == grid2.get_cost_h())	
			&& (grid1.get_cost_f() == grid2.get_cost_f()) && (grid1.get_parent() == grid2.get_parent()));
}

std::shared_ptr<Astar_cost> minimum_cost_f(std::stack<std::shared_ptr<Astar_cost>> list){
	std::shared_ptr<Astar_cost> min_f = list.top();
	
	list.pop();
	while(!list.empty()){	
		if((list.top())->get_cost_f() < min_f->get_cost_f()){
			min_f = (list.top());
		}
		list.pop();
	}	
	return min_f;
}

void delete_element_stack(std::stack<std::shared_ptr<Astar_cost>> &list, Astar_cost element){
	std::stack<std::shared_ptr<Astar_cost>> save_list;

	while(!list.empty()){ 
		//TODO: Create error checks here
		if(*list.top() == element){
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

bool find_lower_cost_f(std::stack<std::shared_ptr<Astar_cost>> list, std::shared_ptr<Astar_cost> element){
	while(!list.empty()){
		if((list.top())->get_position() == element->get_position()){
			//Assume there can bever be multiple elements in the list that have the same (x,y)
			return ((list.top())->get_cost_f() < element->get_cost_f());
		}
		list.pop();
	}
	return false;
}

void insert_path(grid *grid1, std::shared_ptr<Astar_cost> Astar_path){
	//skip the start and final point of the path
	Astar_path = Astar_path->get_parent();
	while(Astar_path->get_parent() != NULL){
		grid1->insert_point(Astar_path->get_position(),'|');
		Astar_path = Astar_path->get_parent();
	}
}


std::shared_ptr<Astar_cost> Astar_algorithm(grid *grid1, Point start_point, Point goal_point){
	//TODO:Implement Priority queue
	std::shared_ptr<Astar_cost> start_position(new Astar_cost(start_point));

	std::stack<std::shared_ptr<Astar_cost>> open_list;
	std::stack<std::shared_ptr<Astar_cost>> closed_list;

	open_list.push(start_position);
	
	std::shared_ptr<Astar_cost> current_position;
	while(!open_list.empty()){
		//Find the minimum F in the open stack
		current_position = minimum_cost_f(open_list);
		delete_element_stack(open_list, *current_position);

		//Generate successor paths
		Point successor_point;
		for(int x = -1; x < 2; x++){
			for(int y = -1; y < 2; y++){
				if(x == 0 && y == 0){
					continue;
				}
				successor_point.x = x + current_position->get_position_x();
				successor_point.y = y + current_position->get_position_y();	

				//Skip parent node position
				if(current_position->get_parent() != NULL){
						if((current_position->get_parent())->get_position() == successor_point){
							continue;
						}
				}
				//Need values that are within the GRID_SIZE
				if(successor_point.x < 0 || successor_point.y < 0 || successor_point.x > GRID_SIZE-1 || successor_point.y > GRID_SIZE-1){
					continue;
				}

				//Skip blockages in the path
				if(grid1->check_blockage(successor_point)){
					continue;
				}

				//std::cout << successor_point.x << " : " << successor_point.y << std::endl;	
				std::shared_ptr<Astar_cost> successor_position(new Astar_cost(successor_point));
				successor_position->insert_parent(current_position);

				//Stop search if we are at the end
				if(successor_point == goal_point){
					return successor_position;
				}

				successor_position->calculate_cost_g(current_position->get_cost_g(), COST_PER_MOVE);
				successor_position->calculate_cost_h(goal_point);
				successor_position->calculate_cost_f();

				if(find_lower_cost_f(open_list, successor_position)){
					continue;
				}

				if(find_lower_cost_f(closed_list, successor_position)){
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


