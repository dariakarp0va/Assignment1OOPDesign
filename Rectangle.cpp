#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Blackboard.h"
#include "Rectangle.h"
#include "const.h"

int convertIntoDigit(std::string lineNum);  

Rectangle::Rectangle(std::stringstream& ss) {
	if (Rectangle::apply_parameters(ss)) {
		id = unique_id;
		unique_id++;
		type = "rectangle";
	}
	else {
		std::cout << "Invalid parameters\n";
		is_valid = 0;
		return;
	}
}
bool Rectangle::apply_parameters(std::stringstream& ss) {
	std::string x_str, y_str, color_temp, width_str, height_str;
	bool is_filled_temp = 0;
	if (ss >> x_str >> y_str >> color_temp >> width_str >> height_str >> is_filled_temp) {
		int x = convertIntoDigit(x_str);
		int y = convertIntoDigit(y_str);
		int width_temp = convertIntoDigit(width_str);
		int height_temp = convertIntoDigit(height_str);
		if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT && width_temp < BOARD_WIDTH && height_temp < BOARD_HEIGHT) {

			height = height_temp;
			width = width_temp;
			coordinate_x = x;
			coordinate_y = y;
			color = color_temp[0];
			is_filled = is_filled_temp;
			return 1;
		}
		else {
			std::cout << "Parametrs out of the board\n";
			return 0;
		}
	}
	else {
		return 0;
	}
}

void Rectangle::draw(Blackboard& blackboard){
	if (is_filled) {
		for (int x = coordinate_x; x < width + coordinate_x; x++) {
			for (int y = coordinate_y; y < height + coordinate_y; y++) {
				blackboard.insert(x, y, color);
			}
		}
	}
	else {
		for (int x = coordinate_x; x < width + coordinate_x; x++) {
			for (int y = coordinate_y; y < height + coordinate_y; y++) {
				if (x == coordinate_x || y == coordinate_y || x == width + coordinate_x - 1 || y == height + coordinate_y - 1) {
					blackboard.insert(x, y, color);
				}

			}
		}
	}
}
bool Rectangle::contains(int target_x, int target_y){
	bool in_x_bounds = (target_x >= coordinate_x && target_x < coordinate_x + width);
	bool in_y_bounds = (target_y >= coordinate_y && target_y < coordinate_y + height);
	bool on_frame = (target_x == coordinate_x || target_x == coordinate_x + width - 1 || target_y == coordinate_y || target_y == coordinate_y + height - 1);
	if (is_filled) {
		return in_x_bounds && in_y_bounds;
	}
	else {
		return in_x_bounds && in_y_bounds && on_frame;
	}
	return 0;
}

void Rectangle::edit(std::stringstream& ss) {
	std::string type;
	ss >> type;
	if (type == "rectangle") {
		if (!Rectangle::apply_parameters(ss)){
			std::cout << "Invalid parametrs\n";
		}
	}
	else {
		std::cout << "You can`t change the type of shape\n";
	}
}
std::string Rectangle::add_info_for_save() {
	return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(is_filled);
}
void Rectangle::info_print() {
	std::cout << "id " << id << " Type: " << type << " Width " << width << " Height " << height << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
}