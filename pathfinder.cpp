#include "Astar_algorithm.h"

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
	int start_y = 3;
	int end_x = 3;
	int end_y = 3;

	//Define start and end point
	g1.insert_point(start_x,start_y,1);
	g1.insert_point(end_x,end_y,1);

	//g1.print_grid();

	std::shared_ptr<grid_cost> Astar_path;
	Astar_path = Astar_algorithm(start_x,start_y,end_x,end_y);

	while(Astar_path !=NULL){
		std::cout << "[x,y] = " << Astar_path->get_position_x() << " , " << Astar_path->get_position_y() << std::endl;
		Astar_path = Astar_path->get_parent();
	}


	return 0;
}
