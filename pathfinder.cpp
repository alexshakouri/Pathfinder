#include "Astar_algorithm.h"

int main(){

	grid g1;

	Point start_point = {0,3};
	Point end_point = {19,19};
	//Define start and end point
	g1.insert_point(start_point,'S');
	g1.insert_point(end_point,'F');

	//Insert blockage
	Point p1 = {18,19};
	Point p2 = {18,18};
	Point p3 = {18,17};
	Point p4 = {18,16};
	g1.insert_point(p1,BLOCKAGE);
	g1.insert_point(p2,BLOCKAGE);
	g1.insert_point(p3,BLOCKAGE);
	g1.insert_point(p4,BLOCKAGE);


	std::shared_ptr<grid_cost> Astar_path;
	Astar_path = Astar_algorithm(&g1,start_point,end_point);

	insert_path(&g1,Astar_path);
	g1.print_grid();	

	return 0;

	
}
