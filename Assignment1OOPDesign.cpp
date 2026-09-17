// Assignment1OOPDesign.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

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
	void info_print() override {
		std::cout << "id " << id << "Type: " << type << "Width " << width << "Height " << height << "Coordinate x " << coordinate_x << "Coordinate y " << coordinate_y;
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
	~Rectangle() override;
};

class Line : public Shape {
	// Derived class for lines
};

class Triangle : public Shape {
	// Derived class for triangles
};




int main()
{
    std::cout << "Hello World!\n";
}
