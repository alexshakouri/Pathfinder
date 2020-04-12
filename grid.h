#ifndef GRID_H
#define GRID_H

#define GRID_SIZE 20
#define BLOCKAGE ' '

struct Point{
	int x;
	int y;
};

class grid{
private:
	char** grid_data;
public:
	grid();
	
	~grid();

	void insert_point(Point position, char value);

	void print_grid();

	bool within_blockage(Point position);

	bool not_within_grid(Point position);
};

#endif // GRID_H
