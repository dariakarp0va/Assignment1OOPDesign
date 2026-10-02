#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Line.h"
#include "const.h"

int convertIntoDigit(std::string lineNum);

Line::Line(std::stringstream& ss) {
	std::string x_str, y_str, Color, lenght_str;
	bool Horison = 0;
	if (ss >> x_str >> y_str >> Color >> lenght_str >> Horison) {
		int x = convertIntoDigit(x_str);
		int y = convertIntoDigit(y_str);
		int Length = convertIntoDigit(lenght_str);
		if (x < 0 || y < 0 || Length < 0 || x > BOARD_WIDTH || y > BOARD_HEIGHT) {
			std::cout << "Parameters out of the board\n";
			is_valid = 0;
			return;
		}
		id = unique_id;
		unique_id++;
		length = Length;
		coordinate_x = x;
		coordinate_y = y;
		color = Color[0];
		horison = Horison;
		type = "line";

	}
	else {
		std::cout << "Invalid parameters\n";
		is_valid = 0;
	}
}
void Line::draw(Blackboard& blackboard) {
	if (horison) {
		for (int x = coordinate_x; x < coordinate_x + length; x++) {
			blackboard.insert(x, coordinate_y, color);
		}
	}
	else {
		for (int y = coordinate_y; y < coordinate_y + length; y++) {
			blackboard.insert(coordinate_x, y, color);
		}
	}
}
bool Line::contains(int target_x, int target_y) {
	if (horison) {
		for (int x = coordinate_x; x < coordinate_x + length; x++) {
			if (x == target_x) {
				return 1;
			}
		}
	}
	else {
		for (int y = coordinate_y; y < coordinate_y + length; y++) {
			if (y == target_y) {
				return 1;
			}
		}
	}
	return 0;
}
void Line::edit(Blackboard& blackboard, std::stringstream& ss) {
	std::string type;
	ss >> type;
	if (type == "line") {
		std::string x_str, y_str, color_temp, lenght_str;
		bool is_filled_temp = 0;
		if (ss >> x_str >> y_str >> color >> lenght_str >> is_filled) {
			int x = convertIntoDigit(x_str);
			int y = convertIntoDigit(y_str);
			int lenght_temp = convertIntoDigit(lenght_str);
			if (x > 0 && x < BOARD_WIDTH && y > 0 && y > BOARD_HEIGHT && lenght_temp < BOARD_HEIGHT) {

				length = lenght_temp;
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
std::string Line::add_info_for_save() {
	return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(length) + " " + std::to_string(horison);
}
void Line::info_print() {
	std::cout << "id " << id << " Type: " << type << " Length " << length << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
}