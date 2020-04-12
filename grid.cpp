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
	if(not_within_grid(position)){
		throw position;
	}
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

bool grid::within_blockage(Point position){
	return (this->grid_data[position.x][position.y] == BLOCKAGE);
}

bool grid::not_within_grid(Point position){
	return ((position.x < 0) || (position.y) < 0 || (position.x > GRID_SIZE-1) || (position.y > GRID_SIZE-1));
}
