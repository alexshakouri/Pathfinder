#ifndef GRID_H
#define GRID_H

#define GRID_SIZE 20
#define BLOCKAGE ' '

struct Point{
	int x;
	int y;
};

//TODO: Implement error check for outside GRID_SIZE
class grid{
private:
	char** grid_data;
public:
	grid();
	
	~grid();

	void insert_point(Point position, char value);

	void print_grid();

	bool check_blockage(Point position);
};

#endif // GRID_H
