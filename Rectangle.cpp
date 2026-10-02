#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Blackboard.h"
#include "Rectangle.h"
#include "const.h"

int convertIntoDigit(std::string lineNum);  

Rectangle::Rectangle(std::stringstream& ss) {
	std::string x_str, y_str, Color, width_str, heigth_str;
	bool Is_filled = 0;
	if (ss >> x_str >> y_str >> Color >> width_str >> heigth_str >> Is_filled) {
		int x = convertIntoDigit(x_str);
		int y = convertIntoDigit(y_str);
		int Width = convertIntoDigit(width_str);
		int Height = convertIntoDigit(heigth_str);
		if (x < 0 || y < 0 || Width < 0 || Height < 0 || x > BOARD_WIDTH || y > BOARD_HEIGHT) {
			std::cout << "Parameters out of the board\n";
			is_valid = 0;
			return;
		}
		id = unique_id;
		unique_id++;
		width = Width;
		height = Height;
		coordinate_x = x;
		coordinate_y = y;
		color = Color[0];
		is_filled = Is_filled;
		type = "rectangle";
	}
	else {
		std::cout << "Invalid parameters\n";
		is_valid = 0;
		return;
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
	if (is_filled) {
		for (int x = coordinate_x; x < width + coordinate_x; x++) {
			for (int y = coordinate_y; y < height + coordinate_y; y++) {
				if (x == target_x && y == target_y) {
					return 1;
				}
			}
		}
	}
	else {
		for (int x = coordinate_x; x < width + coordinate_x; x++) {
			for (int y = coordinate_y; y < height + coordinate_y; y++) {
				if (x == coordinate_x || y == coordinate_y || x == width + coordinate_x - 1 || y == height + coordinate_y - 1) {
					if (x == target_x && y == target_y) {
						return 1;
					}
				}

			}
		}
	}
	return 0;
}
void Rectangle::edit(Blackboard& blackboard, std::stringstream& ss) {
	std::string type;
	ss >> type;
	if (type == "rectangle") {
		std::string x_str, y_str, color_temp, width_str, height_str;
		bool is_filled_temp = 0;
		if (ss >> x_str >> y_str >> color >> width_str >> height_str >> is_filled) {
			int x = convertIntoDigit(x_str);
			int y = convertIntoDigit(y_str);
			int width_temp = convertIntoDigit(width_str);
			int height_temp = convertIntoDigit(height_str);
			if (x > 0 && x < BOARD_WIDTH && y > 0 && y > BOARD_HEIGHT && width_temp < BOARD_WIDTH && height_temp < BOARD_HEIGHT) {

				height = height_temp;
				width = width_temp;
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
std::string Rectangle::add_info_for_save() {
	return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(is_filled);
}
void Rectangle::info_print() {
	std::cout << "id " << id << " Type: " << type << " Width " << width << " Height " << height << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
}