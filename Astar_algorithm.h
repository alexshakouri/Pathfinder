#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <iostream>
#include <stack>
#include <memory>
#include <math.h>
#include "grid_definition.h"

#define COST_PER_MOVE 1

class Astar_cost{
private:
	Point position;
	double cost_g;
        double cost_h, cost_f;
	std::shared_ptr<Astar_cost> parent;

public:
	Astar_cost(Point point){
		//TODO: Create exception throwing for x,y
		this->position = point;
		this->cost_g = 0;
		this->cost_h = 0;
		this->cost_f = 0;
		this->parent = NULL;
	}
	Astar_cost(){
		this->position.x = 0;
		this->position.y = 0;
		this->cost_g = 0;
		this->cost_h = 0;
		this->cost_f = 0;
		this->parent = NULL;
	}

	Point get_position() const{
		return this->position;
	}

	int get_position_x() const{
		return this->position.x;
	}
	int get_position_y() const{
		return this->position.y;
	}
	double get_cost_g() const{
		return this->cost_g;
	}
	double get_cost_h() const{
		return this->cost_h;
	}
	double get_cost_f() const{
		return this->cost_f;
	}
	std::shared_ptr<Astar_cost> get_parent() const{
		return this->parent;
	}
	void calculate_cost_f(){
		this->cost_f = this->cost_g + this->cost_h;
	}
	void calculate_cost_g(double parent_cost_g, double distance_cost){
		//Add penalty for diagonal similar to distance
		if( (abs(this->position.x - this->parent->position.x)) + (abs(this->position.y - this->parent->position.y)) == 2){
			distance_cost = distance_cost * sqrt(2.0);
		}
		this->cost_g = parent_cost_g + distance_cost;
	}
	void calculate_cost_h(Point goal){
		//Diagonal Distance for 8 possible moves
		double dx = abs(this->position.x - goal.x); 
		double dy = abs(this->position.y - goal.y);	
		this->cost_h = sqrt((dx*dx) + (dy*dy));
	}
	void insert_parent(std::shared_ptr<Astar_cost> parent){
		this->parent = parent;
	}
};

//Overload the equal operator
bool operator==(const Point &position1, const Point &position2);
bool operator==(const Astar_cost &grid1, const Astar_cost &grid2);

std::shared_ptr<Astar_cost> minimum_cost_f(std::stack<std::shared_ptr<Astar_cost>> list);

void delete_element_stack(std::stack<std::shared_ptr<Astar_cost>> &list, Astar_cost element);

bool find_lower_cost_f(std::stack<std::shared_ptr<Astar_cost>> list, std::shared_ptr<Astar_cost> element);

void insert_path(grid *grid1, std::shared_ptr<Astar_cost> Astar_path);

std::shared_ptr<Astar_cost> Astar_algorithm(grid *grid1, Point start_point, Point goal_point);


#endif // ASTAR_ALGORITHM_H
