#include "grid_definition.h"

int main(){

	grid g1;
	int start_x = 0;
	int start_y = 3;
	int end_x = 19;
	int end_y = 19;

	//Define start and end point
	g1.insert_point(start_x,start_y,'S');
	g1.insert_point(end_x,end_y,'F');

	std::shared_ptr<grid_cost> Astar_path;
	Astar_path = Astar_algorithm(start_x,start_y,end_x,end_y);

	g1.insert_path(Astar_path);
	g1.print_grid();	

	return 0;

	
}
