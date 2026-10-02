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
	std::string x_str, y_str, color_temp, radius_str;
	bool Is_filled = 0;
	if (ss >> x_str >> y_str >> color_temp >> radius_str >> Is_filled) {
		int x = convertIntoDigit(x_str);
		int y = convertIntoDigit(y_str);
		int radius_temp = convertIntoDigit(radius_str);
		if (x < 0 || y < 0 || radius_temp < 0) {
			std::cout << "Parameters out of the board\n";
			is_valid = 0;
			return;
		}

		id = unique_id;
		unique_id++;
		radius = radius_temp;
		coordinate_x = x;
		coordinate_y = y;
		color = color_temp[0];
		is_filled = Is_filled;
		type = "circle";
	}
	else {
		std::cout << "Invalid parameters\n";
		is_valid = 0;
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
		for (int x = coordinate_x - radius; x <= coordinate_x + radius; x++) {
			for (int y = coordinate_y - radius; y <= coordinate_y + radius; y++) {
				if ((x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) <= radius * radius + radius) {
					if (x == target_x && y == target_y) {
						return 1;
					}
				}
			}
		}
	}
	else {
		for (int x = coordinate_x - radius; x <= coordinate_x + radius; x++) {
			for (int y = coordinate_y - radius; y <= coordinate_y + radius; y++) {
				if ((x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) < radius * radius + radius && (x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) > radius * radius - radius) {
					if (x == target_x && y == target_y) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
void Circle::edit(Blackboard& blackboard, std::stringstream& ss) {
	std::string type;
	ss >> type;
	if (type == "circle") {
		std::string x_str, y_str, color_temp, radius_str;
		bool is_filled_temp = 0;
		if (ss >> x_str >> y_str >> color_temp >> radius_str >> is_filled) {
			int x = convertIntoDigit(x_str);
			int y = convertIntoDigit(y_str);
			int radius_temp = convertIntoDigit(radius_str);
			if (x > 0 && y > 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
				coordinate_x = x;
				coordinate_y = y;
				radius = radius_temp;
				color = color_temp[0];
				is_filled = is_filled_temp;
			}
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