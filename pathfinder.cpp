#include "Astar_algorithm.h"
#include "grid.h"
#include <chrono>

int main(){

	grid g1;
	//TODO:Implement test cases
	Point start_point = {0,18};
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
	
	Point p5 = {0,4};
	Point p6 = {1,4};
	Point p7 = {1,3};
	Point p8 = {1,2};
	g1.insert_point(p5,BLOCKAGE);
	g1.insert_point(p6,BLOCKAGE);
	g1.insert_point(p7,BLOCKAGE);
	g1.insert_point(p8,BLOCKAGE);


	std::shared_ptr<Astar_cost> Astar_path;
	auto start_time = std::chrono::steady_clock::now();
	Astar_path = Astar_algorithm(&g1,start_point,end_point);
	auto finish_time = std::chrono::steady_clock::now();

	std::chrono::duration<double> diff = finish_time - start_time;

	std::cout << "Time executed: "<< diff.count() << "s" << std::endl;

	insert_path(&g1,Astar_path);
	g1.print_grid();	

	return 0;
}

