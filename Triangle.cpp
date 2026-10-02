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
	std::string x_str, y_str, Color, width_str, heigth_str;
	bool Is_filled = 0;
	if (ss >> x_str >> y_str >> Color >> heigth_str >> Is_filled) {
		int x = convertIntoDigit(x_str);
		int y = convertIntoDigit(y_str);
		int Height = convertIntoDigit(heigth_str);
		if (x < 0 || y < 0 || Height < 0 || x > BOARD_WIDTH || y > BOARD_HEIGHT) {
			std::cout << "Parameters out of the board\n";
			is_valid = 0;
			return;
		}
		id = unique_id;
		unique_id++;
		height = Height;
		coordinate_x = x;
		coordinate_y = y;
		color = Color[0];
		is_filled = Is_filled;
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
	if (is_filled) {
		for (int i = 0; i < height; ++i) {
			int numStars = 2 * i + 1;
			int leftMost = coordinate_x - i;
			for (int j = 0; j < numStars; ++j) {
				int position = leftMost + j;
				if (position >= 0 && position < BOARD_WIDTH && (coordinate_y + i) <
					BOARD_HEIGHT && (coordinate_y + i) >= 0) {
					if (position == target_x && coordinate_y + i == target_y) {
						return 1;
					}
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
						if (position == target_x && coordinate_y + i == target_y) {
							return 1;
						}
					}

				}
			}
		}
	}
	return 0;
}
void Triangle::edit(Blackboard& blackboard, std::stringstream& ss) {

	std::string type;
	ss >> type;
	if (type == "triangle") {
		std::string x_str, y_str, color_temp, height_str;
		bool is_filled_temp = 0;
		if (ss >> x_str >> y_str >> color >> height_str >> is_filled) {
			int x = convertIntoDigit(x_str);
			int y = convertIntoDigit(y_str);
			int height_temp = convertIntoDigit(height_str);
			if (x > 0 && x < BOARD_WIDTH && y > 0 && y > BOARD_HEIGHT && height_temp < BOARD_HEIGHT) {

				height = height_temp;
				coordinate_x = x;
				coordinate_y = y;
				color = color_temp[0];
				is_filled = is_filled_temp;
			}
			else {
				std::cout << "Parametrs out of the board\n";
			}
		}

		else {
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