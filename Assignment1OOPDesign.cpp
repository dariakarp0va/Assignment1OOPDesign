// Assignment1OOPDesign.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

enum class Color {
	Red,
	Green,
	Blue,
	Default
};

enum class Type {
	Circle,
	Line,
	Rectangle,
	Triangle
};

int unique_id = 0;

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

class Blackboard {
private:
	std::vector<std::vector<char>> grid;

public:
	Blackboard() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

	void print() {
		for (auto& row : grid) {
			for (char c : row) {
				std::cout << c;
			}
			std::cout << "\n";
		}
	}
	void insert(int x, int y, char color) {
		grid[y][x] = color;
	}
};
class Shape {
protected:  
	int id = 0;
	int coordinate_x = 0;
	int coordinate_y = 0;
	char color = '*';
	bool is_filled = 0;
public:
	Shape(){}
	virtual void draw(Blackboard& blackboard) = 0;
	virtual void info_print() = 0;

	virtual ~Shape() = default;
	// Base class for shapes
};

class Circle : public Shape {
private:
	int radius = 0;
	std::string type = "Circle";
public:
	Circle(int Radius, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		radius = Radius;
		coordinate_x = Coordinate_x;
		coordinate_y = Coordinate_y;
		color = Color;
		is_filled = Is_filled;
	}

	void draw(Blackboard& blackboard) override {
		if (is_filled) {
			for (int x = coordinate_x - radius; x < coordinate_x + radius; x++) {
				for (int y = coordinate_y - radius; y < coordinate_y + radius; y++) {
					if ((x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) <= radius * radius) {
						blackboard.insert(x, y, color);
					}
				}
			}
		}
		else {
			for (int x = coordinate_x - radius; x < coordinate_x + radius; x++) {
				for (int y = coordinate_y - radius; y < coordinate_y + radius; y++) {
					if ((x - coordinate_x) * (x - coordinate_x) + (y - coordinate_y) * (y - coordinate_y) == radius * radius) {
						blackboard.insert(x, y, color);
					}
				}
			}
		}
	}
	void info_print() override {
		std::cout << "id " << id << "Type: " << type << "Radius " << radius << "Coordinate x " << coordinate_x << "Coordinate y " << coordinate_y;
	}
	~Circle() override;
};

class Rectangle : public Shape {
private:
	int width = 0;
	int height = 0;
	std::string type = "Rectangle";
public:
	Rectangle(int Width,int Height, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		width = Width;
		height = Height;
		coordinate_x = Coordinate_x;
		coordinate_y = Coordinate_y;
		color = Color;
		is_filled = Is_filled;
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
	void info_print() override {
		std::cout << "id " << id << "Type: " << type << "Width " << width << "Height " << height << "Coordinate x " << coordinate_x << "Coordinate y " << coordinate_y;
	}
	~Rectangle() override;
};

class Line : public Shape {
private:
	int length = 0;
	std::string type = "Line";
	bool horison = 1;
public:
	Line(int Length, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		length = Length;
		coordinate_x = Coordinate_x;
		coordinate_y = Coordinate_y;
		color = Color;
		is_filled = Is_filled;
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
	void info_print() override {
		std::cout << "id " << id << "Type: " << type << "Length " << length << "Coordinate x " << coordinate_x << "Coordinate y " << coordinate_y;
	}

};

class Triangle : public Shape {
private:
	int height = 0;
	std::string type = "Triangle";
public:
	Triangle(int Height, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		height = Height;
		coordinate_x = Coordinate_x;
		coordinate_y = Coordinate_y;
		color = Color;
		is_filled = Is_filled;
	}
	void draw(Blackboard& blackboard) override {
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
	void info_print() override {
		std::cout << "id " << id << "Type: " << type << "Height " << height << "Coordinate x " << coordinate_x << "Coordinate y " << coordinate_y;
	}

};

class Manager {
private:
	std::vector<std::unique_ptr<Shape>> shapes;

	void Handle_Type(std::string type, std::string command, std::stringstream& ss) {
		std::string x, y, color, radius;
		if (command == "add") {
			if (type == "circle") {
				if (ss >> x >> y >> color >> radius) {

				}
			}
			else if (type == "line") {

			}
			else if (type == "rectangle") {

			}
			else if (type == "triangle") {

			}
			else {
				std::cout << "Invalid type";
				return;
			}
		}
		else {
			return;
		}
		
	}
public:
	void run(Blackboard& blackboard) {
		while (true) {
			std::string input_line;
			std::getline(std::cin, input_line);
			std::stringstream ss(input_line);
			std::string action, shape_type;
			ss >> action;
			ss >> shape_type;
			Handle_Type(shape_type, action, ss);
		}
	}
};



int main()
{
    
}
