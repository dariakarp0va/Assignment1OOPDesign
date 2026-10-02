#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Blackboard.h"
#include "const.h"

Blackboard::Blackboard() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

void Blackboard::print() {
	for (auto& row : grid) {
		for (char c : row) {
			if (c == 'r') {
				std::cout << "\033[31m" << c << "\033[0m";
			}
			else if (c == 'g') {
				std::cout << "\033[32m" << c << "\033[0m";
			}
			else if (c == 'b') {
				std::cout << "\033[34m" << c << "\033[0m";
			}
			else if (c == 'p') {
				std::cout << "\033[35m" << c << "\033[0m";
			}
			else if (c == 'y') {
				std::cout << "\033[33m" << c << "\033[0m";
			}
			else if (c == 'm') {
				std::cout << "\033[38;5;48m" << c << "\033[0m";
			}
			else {
				std::cout << c;
			}

		}
		std::cout << "\n";
	}
}
void Blackboard::load_board(std::ofstream& OutFile) {
	for (auto& row : grid) {
		for (char c : row) {
			OutFile << c;
		}
		OutFile << "\n";
	}

}
void Blackboard::insert(int x, int y, char color) {
	if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
		grid[y][x] = color;
	}

}
void Blackboard::add_shape(std::unique_ptr<Shape> shape) {
	shapes.push_back(std::move(shape));
}

bool Blackboard::is_clone(std::unique_ptr<Shape>& shape) {
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]->add_info_for_save() == shape->add_info_for_save()) {
			return 1;
		}
	}
	return 0;
}
int Blackboard::get_selected_shape() {
	return selected_shape;
}
void Blackboard::select(int shape) {
	selected_shape = shape;
}
int Blackboard::size_count() {
	return shapes.size();
}
void Blackboard::remove_shape_at(int index) {
	shapes.erase(shapes.begin() + index);
}
void Blackboard::clear_shapes() {
	shapes.clear();
}
Shape* Blackboard::get_shape(int index) {
	return shapes[index].get();
}