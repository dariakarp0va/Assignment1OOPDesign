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
	std::vector<std::unique_ptr<Shape>>& get_shapes();
	int get_selected_shape();
	void select(int shape);
};