#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Blackboard.h"
#include "const.h"

int Shape::unique_id = 0;

void Shape::remove(Blackboard& blackboard) {
	char temp_color = color;
	color = ' ';
	draw(blackboard);
	color = temp_color;
}
void Shape::move_to(int x, int y) {
	if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
		coordinate_x = x;
		coordinate_y = y;
	}
	else {
		std::cout << "Inlavid parameters\n";
	}

}
bool Shape::check_valid() {
	return is_valid;
}
std::string Shape::get_type() {
	return type;
}
int Shape::get_id() {
	return id;
}
void Shape::paint(char Color) {
	color = Color;
}