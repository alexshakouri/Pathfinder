#include <iostream>

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
		std::cout << grid_data[0][0] << std::endl;
	}

};

int main(){

	grid g1;

	//Define start and end point
	g1.insert_point(0,0,1);
	g1.insert_point(3,3,1);

	g1.print_grid();

	return 0;
}
