// Assignment1OOPDesign.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"

A a;


int unique_id = 0;

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

int convertIntoDigit(std::string lineNum)
{
	bool isDigit = false;
	while (!isDigit)
	{
		bool isSymbolDigit = true;
		for (int i = 0; i < lineNum.length(); i++)
		{
			if (!isdigit(lineNum[i]))
			{
				isSymbolDigit = false;
			}
		}
		isDigit = isSymbolDigit;
		if (isDigit == false)
		{
			printf("input should be numeric \n");
			return -1;
		}
	}
	int LineNum = std::stoll(lineNum);
	return LineNum;
}

class Shape;

class Blackboard {
private:
	std::vector<std::vector<char>> grid;
	std::vector<std::unique_ptr<Shape>> shapes;
	int selected_shape = -1;

public:
	Blackboard() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

	void print() {
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
	void load_board(std::ofstream& OutFile) {
		for (auto& row : grid) {
			for (char c : row) {
					OutFile << c;
			}
			OutFile << "\n";
		}  

	}
	void insert(int x, int y, char color) {
		if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
			grid[y][x] = color;
		}
		
	}
	bool is_clone(std::unique_ptr<Shape>& shape) {
		for (int i = 0; i < shapes.size(); i++) {
			if (shapes[i]->add_info_for_save() == shape->add_info_for_save()) {
				return 1;
			}
		}
		return 0;
	}
	std::vector<std::unique_ptr<Shape>>& get_shapes() {
		return shapes;
	}
	int get_selected_shape() {
		return selected_shape;
	}
	void select(int shape) {
		selected_shape = shape;
	}

};
class Shape {
protected:  
	int id = 0;
	int coordinate_x = 0;
	int coordinate_y = 0;
	char color = '*';
	bool is_filled = 0;
	bool is_valid = 1;
	std::string type;
public:
	Shape(){}
	virtual void draw(Blackboard& blackboard) = 0;
	virtual void info_print() = 0;
	virtual std::string add_info_for_save() = 0;
	virtual void edit(Blackboard& blackboard, std::stringstream& ss) = 0;
	virtual bool contains(int target_x, int target_y) = 0;
	void remove(Blackboard& blackboard) {
		char temp_color = color;
		color = ' ';
		draw(blackboard);
		color = temp_color;
	}
	void move_to(int x, int y) {
		if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
			coordinate_x = x;
			coordinate_y = y;
		}
		else {
			std::cout << "Inlavid parameters\n";
		}
		
	}
	bool check_valid() {
		return is_valid;
	}
	std::string get_type() {
		return type;
	}
	int get_id() {
		return id;
	}
	void paint(char Color) {
		color = Color;
	}
	virtual ~Shape() = default;
};

class Circle : public Shape {
private:
	int radius = 0;
public:
	Circle(std::stringstream& ss) {
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

	void draw(Blackboard& blackboard) override {
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
			for (int x = coordinate_x - radius; x <=  coordinate_x + radius; x++) {
				for (int y = coordinate_y - radius; y <= coordinate_y + radius; y++) {
					if ((x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) < radius * radius + radius && (x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) > radius * radius - radius) {
						blackboard.insert(x, y, color);
					}
				}
			}
		}             
	}
	void edit(Blackboard& blackboard, std::stringstream& ss){
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
	std::string add_info_for_save() override {
		return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(radius) + " " + std::to_string(is_filled);
	}
	void info_print() override {
		std::cout << "id " << id << " Type: " << type << " Radius " << radius << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
	}
	~Circle() override = default;
};

class Rectangle : public Shape {
private:
	int width = 0;
	int height = 0;
public:
	Rectangle(std::stringstream& ss) {
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
	
	void draw(Blackboard& blackboard) override {
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
					if (x == coordinate_x || y == coordinate_y || x == width + coordinate_x - 1 || y == height + coordinate_y -1 ) {
						blackboard.insert(x, y, color);
					}
					
				}
			}
		}
	}
	void edit(Blackboard& blackboard, std::stringstream& ss) {
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
	std::string add_info_for_save() override {
		return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(is_filled);
	}
	void info_print() override {
		std::cout << "id " << id << " Type: " << type << " Width " << width << " Height " << height << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
	}
	~Rectangle() override = default;
};

class Line : public Shape {
private:
	int length = 0;
	bool horison = 1;
public:
	Line(std::stringstream& ss) {
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
	void draw(Blackboard& blackboard) override {
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
	void edit(Blackboard& blackboard, std::stringstream& ss) {
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
	std::string add_info_for_save() override {
		return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(length) + " " + std::to_string(horison);
	}
	void info_print() override {
		std::cout << "id " << id << " Type: " << type << " Length " << length << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
	}
	~Line() override = default;

};

class Triangle : public Shape {
private:

	int height = 0;
public:
	Triangle(std::stringstream& ss) {
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
	void draw(Blackboard& blackboard) override {
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
	void edit(Blackboard& blackboard, std::stringstream& ss) {

		std::string type;
		ss >> type;
		if (type == "triangle") {
			std::string x_str, y_str, color_temp, height_str;
			bool is_filled_temp = 0;
			if (ss >> x_str >> y_str >> color >> height_str >> is_filled) {
				int x = convertIntoDigit(x_str);
				int y = convertIntoDigit(y_str);
				int height_temp = convertIntoDigit(height_str);
				if (x > 0 && x < BOARD_WIDTH && y > 0 && y > BOARD_HEIGHT && height_temp < BOARD_HEIGHT){
					
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
	std::string add_info_for_save() override {
		return "add " + type + " " + std::to_string(coordinate_x) + " " + std::to_string(coordinate_y) + " " + color + " " + std::to_string(height) + " " + std::to_string(is_filled);
	}
	void info_print() override {
		std::cout << "id " << id << " Type: " << type << " Height " << height << " Coordinate x " << coordinate_x << " Coordinate y " << coordinate_y << "\n";
	}
	~Triangle() override = default;
};

class Manager {
private:
	
	void RenewScreen(Blackboard& blackboard) {
		std::vector<std::unique_ptr<Shape>>& shapes = blackboard.get_shapes();
		for (int i = 0; i < blackboard.get_shapes().size(); i++) {
			blackboard.get_shapes()[i]->remove(blackboard);
			blackboard.get_shapes()[i]->draw(blackboard);
		}
		blackboard.print();
	}
	

	void Handle_Type( std::string command, std::stringstream& ss, Blackboard& blackboard) {
		std::vector<std::unique_ptr<Shape>>& shapes = blackboard.get_shapes();
		if (command == "add") {
			std::string type;
			ss >> type;
			if (type == "circle") {
				std::unique_ptr<Shape> circle = std::make_unique<Circle>(ss);
				if (circle->check_valid()) {
					if (!blackboard.is_clone(circle)) {
						circle->draw(blackboard);
						blackboard.get_shapes().push_back(std::move(circle));
					}
					else {
						std::cout << "Can`t add the same shapes on board\n";
					}
				}
			}

			else if (type == "line") {
				
				std::unique_ptr<Shape> line = std::make_unique<Line>(ss);
				if (line->check_valid()) {
					line->draw(blackboard);
					blackboard.get_shapes().push_back(std::move(line));
				}
			}

			else if (type == "rectangle") {
				
				std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(ss);
				if (rectangle->check_valid()) {
					rectangle->draw(blackboard);
					blackboard.get_shapes().push_back(std::move(rectangle));
				}
			}
			else if (type == "triangle") {
				
				std::unique_ptr<Shape> triangle = std::make_unique<Triangle>(ss);
				if (triangle->check_valid()) {
					triangle->draw(blackboard);
					blackboard.get_shapes().push_back(std::move(triangle));
				}
			}
			else {
				std::cout << "Invalid type\n";
				return;
			}
		}
		else if (command == "draw") {
			blackboard.print();
		}
		else if (command == "list") {
			for (int i = 0; i < blackboard.get_shapes().size(); i++) {
				blackboard.get_shapes()[i]->info_print();
			}
		}
		else if (command == "shapes") {
			std::printf("1. Circle: x y color radius is_filled \n 2. Rectangle: x y color width heigth is_filled \n 3. Line: x y color lenght is_horisontal \n 4. Triangle: x y color heigth is_filled \n ");
		}
		else if (command == "select") {
			if (blackboard.get_shapes().size() == 0) {
				std::printf("no shapes on board\n");
				return;
			}
			std::string id_str;
			if (ss >> id_str) {
				int id = convertIntoDigit(id_str);
				for (int i = 0; i < blackboard.get_shapes().size(); i++) {
					if (blackboard.get_shapes()[i]->get_id() == id) {
						shapes[i]->info_print();
						blackboard.select(i);
						break;
					}
					else {
						if (i == shapes.size() - 1) {
							std::printf("shape was not found\n");
						}
					}
				}
			}
			else {
				std::cout << "You need to pass arguments \n";
			}
			
			
		}
		
		else if (command == "remove") {
			if (0 <= blackboard.get_selected_shape() && blackboard.get_selected_shape() <  shapes.size()) {
				shapes[blackboard.get_selected_shape()]->remove(blackboard);
				shapes.erase(shapes.begin() + blackboard.get_selected_shape());
				RenewScreen(blackboard);
				blackboard.select(-1);
			}
			else {
				std::printf("no selected shape\n");
			}
			
		}
		else if (command == "edit") {
			if (0 <= blackboard.get_selected_shape() && blackboard.get_selected_shape() < shapes.size()) {
				shapes[blackboard.get_selected_shape()]->remove(blackboard);
				shapes[blackboard.get_selected_shape()]->edit(blackboard, ss);
				RenewScreen(blackboard);
			}
			else {
				std::printf("no selected shape\n");
			}
			
		}
		else if (command == "clear") {

			for (int i = 0; i < shapes.size(); i++) {
				shapes[i]->remove(blackboard);
			}
			shapes.clear();
			blackboard.select(-1);
			std::printf("Board is cleared!\n");
		}
		else if (command == "move") {
			if (0 <= blackboard.get_selected_shape() && blackboard.get_selected_shape() < shapes.size()) {
				std::string x_str, y_str;
				if (ss >> x_str >> y_str) {
					int x = convertIntoDigit(x_str);
					int y = convertIntoDigit(y_str);
					if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
						shapes[blackboard.get_selected_shape()]->remove(blackboard);
						shapes[blackboard.get_selected_shape()]->move_to(x, y);
						RenewScreen(blackboard);
					}
					else {
						std::cout << "Invalid coordinates\n";
					}
					
				}
				else {
					std::cout << "Invalid parameters\n";
					return;
				}
			}
			else {
				std::printf("no selected shape\n");
			}
			
		}
		else if (command == "paint") {
			if (0 <= blackboard.get_selected_shape() && blackboard.get_selected_shape() < shapes.size()) {
				std::string color;
				if (ss >> color){
					shapes[blackboard.get_selected_shape()]->remove(blackboard);
					shapes[blackboard.get_selected_shape()]->paint(color[0]);
					RenewScreen(blackboard);
				}
				else {
					std::cout << "Invalid parameters\n";
					return;
				}
			}
			else {
				std::printf("no selected shape\n");
			}
		}
		else if (command == "save") {
			std::string fileName;
			if (ss >> fileName) {
				std::ofstream outFile(fileName);

				if (!outFile.is_open()) {
					printf("Issues with opening file\n");
					return;
				}
				for (int i = 0; i < shapes.size(); i++) {
					outFile << shapes[i]->add_info_for_save();
					outFile << "\n";
				}
				outFile << "end";
				outFile << "\n";
				blackboard.load_board(outFile);
			}
			else {
				std::printf("invalid parameters \n");
			}
			
		}
		else if (command == "load") {
			std::string fileName;
			if (ss >> fileName) {
				std::ifstream inFile(fileName);
				if (!inFile.is_open()) {
					std::cout << "Issues with opening file\n";
					return;
				}
				
				Handle_Type("clear", ss, blackboard);

				std::string line;
				while (std::getline(inFile, line)) {
					if (line == "end") {
						break;
					}
					std::stringstream ss(line);
					std::string action;
					if (ss >> action && action == "add") {
						Handle_Type(action, ss, blackboard);
					}
					else {
						std::printf("some parts of files are broken\n");
					}
					
				}
				RenewScreen(blackboard);
			}
		}
		else {
			std::printf("no such command\n");
			return;
		}
		
	}
public:
	void run(Blackboard& blackboard) {
		while (true) {  
			std::string input_line;
			std::getline(std::cin, input_line);
			std::stringstream ss(input_line);
			std::string action;
			ss >> action;
			Handle_Type( action, ss, blackboard);
		} 
	} 
};



int main()
{
	Blackboard blackboard = Blackboard();
	Manager mng = Manager();
	mng.run(blackboard);
}
