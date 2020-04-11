#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <iostream>
#include <stack>
#include <memory>
#include "grid.h"

#define COST_PER_MOVE 1

class Astar_cost{
private:
	Point position;
	double cost_g;
        double cost_h, cost_f;
	std::shared_ptr<Astar_cost> parent;

public:
	Astar_cost(Point point);

	Astar_cost();

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
	void calculate_cost_f();
	
	void calculate_cost_g(double parent_cost_g, double distance_cost);
	
	void calculate_cost_h(Point goal);
	
	void insert_parent(std::shared_ptr<Astar_cost> parent);
	
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
