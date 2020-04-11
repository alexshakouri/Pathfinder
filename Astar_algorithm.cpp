#include "Astar_algorithm.h"

Astar_cost::Astar_cost(Point point){
	//TODO: Create exception throwing for x,y
	this->position = point;
	this->cost_g = 0;
	this->cost_h = 0;
	this->cost_f = 0;
	this->parent = NULL;
}
Astar_cost::Astar_cost(){
	this->position.x = 0;
	this->position.y = 0;
	this->cost_g = 0;
	this->cost_h = 0;
	this->cost_f = 0;
	this->parent = NULL;
}

void Astar_cost::insert_parent(std::shared_ptr<Astar_cost> parent){
	this->parent = parent;
}

void Astar_cost::calculate_cost_f(){
	this->cost_f = this->cost_g + this->cost_h;
}

void Astar_cost::calculate_cost_g(double parent_cost_g, double distance_cost){
	//Add penalty for diagonal similar to distance
	if( (abs(this->position.x - this->parent->position.x)) + (abs(this->position.y - this->parent->position.y)) == 2){
		distance_cost = distance_cost * sqrt(2.0);
	}
	this->cost_g = parent_cost_g + distance_cost;
}

void Astar_cost::calculate_cost_h(Point goal){
	//Diagonal Distance for 8 possible moves
	double dx = abs(this->position.x - goal.x); 
	double dy = abs(this->position.y - goal.y);	
	this->cost_h = sqrt((dx*dx) + (dy*dy));
}


