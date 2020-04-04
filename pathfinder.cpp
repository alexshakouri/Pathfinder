#include "Astar_algorithm.h"

#define GRID_SIZE 4

class grid{
private:
	int**grid_data;
public:
	grid(){

	this->grid_data = new int*[GRID_SIZE];
	for(int i = 0; i < GRID_SIZE; i++){
		this->grid_data[i] = new int[GRID_SIZE];
	}	
	}
	
	~grid(){
	//Free the grid
	for(int i = 0; i < GRID_SIZE; i++){
		delete[] this->grid_data[i];
	}
	delete[] this->grid_data; 
	}

	void insert_point(int x, int y, int value){
		this->grid_data[x][y] = value;
	}

	void print_grid(){
		for(int x = 0; x < GRID_SIZE;x++){
			for(int y = 0; y < GRID_SIZE; y++){
				std::cout << grid_data[x][y] << " ";
			}
			std::cout << std::endl;
		}

	}

};

int main(){

	grid g1;
	int start_x = 0;
	int start_y = 0;
	int end_x = 3;
	int end_y = 3;

	//Define start and end point
	g1.insert_point(start_x,start_y,1);
	g1.insert_point(end_x,end_y,1);

	g1.print_grid();

	int total_cost = 0;
	total_cost = Astar_algorithm(start_x,start_y,end_x,end_y);
	std::cout << total_cost << std::endl;

	return 0;
}
