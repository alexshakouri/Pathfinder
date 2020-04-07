#ifndef GRID_DEFINITION_H
#define GRID_DEFINITION_H

#define GRID_SIZE 20

#include "Astar_algorithm.h"

class grid{
private:
	char**grid_data;
public:
	grid(){

	this->grid_data = new char*[GRID_SIZE];
	for(int i = 0; i < GRID_SIZE; i++){
		this->grid_data[i] = new char[GRID_SIZE];
		for (int j = 0; j < GRID_SIZE; j++){
			this->grid_data[i][j] = '*';
		}
	}	
	}
	
	~grid(){
	//Free the grid
	for(int i = 0; i < GRID_SIZE; i++){
		delete[] this->grid_data[i];
	}
	delete[] this->grid_data; 
	}

	void insert_point(int x, int y, char value){
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

	void insert_path(std::shared_ptr<grid_cost> Astar_path){
		//skip the start and final point of the path
		Astar_path = Astar_path->get_parent();
		while(Astar_path->get_parent() != NULL){
			this->grid_data[Astar_path->get_position_x()][Astar_path->get_position_y()] = '|';
			Astar_path = Astar_path->get_parent();
		}
	}
};

#endif // GRID_DEFINITION_H
