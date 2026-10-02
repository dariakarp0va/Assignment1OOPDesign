#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"


class Blackboard {
private:
	std::vector<std::vector<char>> grid;
	std::vector<std::unique_ptr<Shape>> shapes;
	int selected_shape = -1;

public:
	Blackboard();
	void print();
	void load_board(std::ofstream& OutFile);
	void insert(int x, int y, char color);
	bool is_clone(std::unique_ptr<Shape>& shape);
	int get_selected_shape();
	void add_shape(std::unique_ptr<Shape> shape);
	int size_count();
	void clear_shapes();
	void remove_shape_at(int index);
	Shape* get_shape(int index);
	void select(int shape);
};