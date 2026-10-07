#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Circle.h"
#include "const.h"

int convertIntoDigit(std::string lineNum);

Circle::Circle(std::stringstream& ss) {
	if (Circle::apply_parameters(ss)) {
		id = unique_id;
		unique_id++;
		type = "circle";
	}
	else {
		std::cout << "Invalid parameters\n";
		is_valid = 0;
	}

}

bool Circle::apply_parameters(std::stringstream& ss) {
	std::string x_str, y_str, color_temp, radius_str;
	bool is_filled_temp = 0;
	if (ss >> x_str >> y_str >> color_temp >> radius_str >> is_filled_temp) {
		int x = convertIntoDigit(x_str);
		int y = convertIntoDigit(y_str);
		int radius_temp = convertIntoDigit(radius_str);
		if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
			coordinate_x = x;
			coordinate_y = y;
			radius = radius_temp;
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
void Circle::draw(Blackboard& blackboard) {
	if (is_filled) {
		for (int x = coordinate_x - radius; x <= coordinate_x + radius; x++) {
			for (int y = coordinate_y - radius; y <= coordinate_y + radius; y++) {
				if ((x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) <= radius * radius + radius) {
					blackboard.insert(x, y, color);
				}
			}
		}
	}
	else {
		for (int x = coordinate_x - radius; x <= coordinate_x + radius; x++) {
			for (int y = coordinate_y - radius; y <= coordinate_y + radius; y++) {
				if ((x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) < radius * radius + radius && (x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) > radius * radius - radius) {
					blackboard.insert(x, y, color);
				}
			}
		}
	}
}
bool Circle::contains(int target_x, int target_y) {
	if (is_filled) {
		return (target_x - coordinate_x) * (target_x - coordinate_x) + (target_y - coordinate_y) * (target_y - coordinate_y) <= radius * radius + radius;
	}
	else {
		return (target_x - coordinate_x) * (target_x - coordinate_x) + (target_y - coordinate_y) * (target_y - coordinate_y) < radius * radius + radius && (target_x - coordinate_x) * (target_x - coordinate_x) + (target_y - coordinate_y) * (target_y - coordinate_y) > radius * radius - radius;
	}
	return 0;
}
void Circle::edit(std::stringstream& ss) {
	std::string type;
	ss >> type;
	if (type == "circle") {
		if (!Circle::apply_parameters(ss)) {
			std::cout << "Invalid parameters\n";
		}
	}
	else {
		std::cout << "You can`t change the type of shape\n";
	}
}
std::string Circle::add_info_for_save() {
	return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(radius) + " " + std::to_string(is_filled);
}
void Circle::info_print() {
	std::cout << "id " << id << " Type: " << type << " Radius " << radius << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
}