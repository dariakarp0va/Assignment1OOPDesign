#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Triangle.h"
#include "const.h"

int convertIntoDigit(std::string lineNum);

Triangle::Triangle(std::stringstream& ss) {
	if (Triangle::apply_parameters(ss)){
		id = unique_id;
		unique_id++;
		type = "triangle";
	}
	else {
		std::cout << "Invalid parameters\n";
		is_valid = 0;
		return;
	}

}
void Triangle::draw(Blackboard& blackboard) {
	if (is_filled) {
		for (int i = 0; i < height; ++i) {
			int numStars = 2 * i + 1;
			int leftMost = coordinate_x - i;
			for (int j = 0; j < numStars; ++j) {
				int position = leftMost + j;
				if (position >= 0 && position < BOARD_WIDTH && (coordinate_y + i) <
					BOARD_HEIGHT && (coordinate_y + i) >= 0) {

					blackboard.insert(position, coordinate_y + i, color);
				}
			}
		}
	}
	else {
		for (int i = 0; i < height; ++i) {
			int numStars = 2 * i + 1;
			int leftMost = coordinate_x - i;
			for (int j = 0; j < numStars; ++j) {
				int position = leftMost + j;
				if (position >= 0 && position < BOARD_WIDTH && (coordinate_y + i) <
					BOARD_HEIGHT && (coordinate_y + i) >= 0) {

					if (position == leftMost || position == leftMost + numStars - 1 || i == height - 1) {
						blackboard.insert(position, coordinate_y + i, color);
					}

				}
			}
		}
	}

}
bool Triangle::contains(int target_x, int target_y) {
		int level = target_y - coordinate_y;
		if (level < 0 || level >= height) {
			return 0;
		}
		bool in_bounds = target_x >= coordinate_x - level && target_x <= coordinate_x + level;
		bool on_frame = target_x == coordinate_x - level || target_x == coordinate_x + level || (level == height - 1 && in_bounds);
		if (is_filled) {
			return in_bounds;
		}
		else {
			return on_frame;
		}
		return 0;
}
bool Triangle::apply_parameters(std::stringstream& ss) {
	std::string x_str, y_str, color_temp, height_str;
	bool is_filled_temp = 0;
	if (ss >> x_str >> y_str >> color_temp >> height_str >> is_filled_temp) {
		int x = convertIntoDigit(x_str);
		int y = convertIntoDigit(y_str);
		int height_temp = convertIntoDigit(height_str);
		if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT && height_temp < BOARD_HEIGHT) {

			height = height_temp;
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
void Triangle::edit(std::stringstream& ss) {

	std::string type;
	ss >> type;
	if (type == "triangle") {
		if (!Triangle::apply_parameters(ss)){
			std::cout << "Invalid parametrs\n";
		}
	}
	else {
		std::cout << "You can`t change the type of shape\n";
	}
}
std::string Triangle::add_info_for_save() {
	return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(height) + " " + std::to_string(is_filled);
}
void Triangle::info_print() {
	std::cout << "id " << id << " Type: " << type << " Height " << height << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
}