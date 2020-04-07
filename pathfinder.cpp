#include "Astar_algorithm.h"

int main(){

	grid g1;
	int start_x = 0;
	int start_y = 3;
	int end_x = 19;
	int end_y = 19;

	//Define start and end point
	g1.insert_point(start_x,start_y,'S');
	g1.insert_point(end_x,end_y,'F');

	//Insert blockage
	g1.insert_point(18,19,BLOCKAGE);
	g1.insert_point(18,18,BLOCKAGE);
	g1.insert_point(18,17,BLOCKAGE);
	g1.insert_point(18,16,BLOCKAGE);


	std::shared_ptr<grid_cost> Astar_path;
	Astar_path = Astar_algorithm(&g1,start_x,start_y,end_x,end_y);

	insert_path(&g1,Astar_path);
	g1.print_grid();	

	return 0;

	
}
