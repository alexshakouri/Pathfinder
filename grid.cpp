#include "grid.h"
#include <iostream>

grid::grid(){
	this->grid_data = new char*[GRID_SIZE];
	for(int x = 0; x < GRID_SIZE; x++){
		this->grid_data[x] = new char[GRID_SIZE];
		for (int y = 0; y < GRID_SIZE; y++){
			this->grid_data[x][y] = '*';
		}
	}
}
	
grid::~grid(){
	//Free the grid
	for(int i = 0; i < GRID_SIZE; i++){
		delete[] this->grid_data[i];
	}
	delete[] this->grid_data; 
}

void grid::insert_point(Point position, char value){
	this->grid_data[position.x][position.y] = value;
}

void grid::print_grid(){
	for(int x = 0; x < GRID_SIZE;x++){
		for(int y = 0; y < GRID_SIZE; y++){
			std::cout << this->grid_data[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

bool grid::check_blockage(Point position){
	return (this->grid_data[position.x][position.y] == BLOCKAGE);
}
