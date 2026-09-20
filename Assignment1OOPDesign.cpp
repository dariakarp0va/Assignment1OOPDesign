// Assignment1OOPDesign.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

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
	void remove(Blackboard& blackboard) {
		char temp_color = color;
		color = ' ';
		draw(blackboard);
		color = temp_color;
	}
	int get_id() {
		return id;
	}
	virtual ~Shape() = default;
};

class Circle : public Shape {
private:
	int radius = 0;
	std::string type = "Circle";
public:
	Circle(int Radius, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		id = unique_id;
		unique_id++;
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
	~Circle() override = default;
};

class Rectangle : public Shape {
private:
	int width = 0;
	int height = 0;
	std::string type = "Rectangle";
public:
	Rectangle(int Width,int Height, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		id = unique_id;
		unique_id++;
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
	~Rectangle() override = default;
};

class Line : public Shape {
private:
	int length = 0;
	std::string type = "Line";
	bool horison = 1;
public:
	Line(int Length, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		id = unique_id;
		unique_id++;
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
	~Line() override = default;

};

class Triangle : public Shape {
private:

	int height = 0;
	std::string type = "Triangle";
public:
	Triangle(int Height, int Coordinate_x, int Coordinate_y, char Color, bool Is_filled) {
		id = unique_id;
		unique_id++;
		height = Height;
		coordinate_x = Coordinate_x;
		coordinate_y = Coordinate_y;
		color = Color;
		is_filled = Is_filled;
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
						
						blackboard.insert(position, coordinate_y + i, color);
					}
				}
			}
		}
		
	}
	void info_print() override {
		std::cout << "id " << id << "Type: " << type << "Height " << height << "Coordinate x " << coordinate_x << "Coordinate y " << coordinate_y;
	}
	~Triangle() override = default;
};

class Manager {
private:
	std::vector<std::unique_ptr<Shape>> shapes;
	int selected_shape = -1;

	void RenewScreen(Blackboard& blackboard) {
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->remove(blackboard);
		}
		blackboard.print();
	}
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

	void Handle_Type( std::string command, std::stringstream& ss, Blackboard& blackboard) {
		std::string type;
		ss >> type;
		if (command == "add") {
			if (type == "circle") {
				std::string x_str, y_str, color, radius_str;
				bool is_filled = 0;
				if (ss >> x_str >> y_str >> color >> radius_str >> is_filled) {
					int x = convertIntoDigit(x_str);
					int y = convertIntoDigit(y_str);
					int radius = convertIntoDigit(radius_str);
					if (x < 0 || y < 0 || radius < 0 || x + radius > BOARD_WIDTH || y + radius > BOARD_HEIGHT || x - radius < 0 || y - radius < 0) {
						return;
					}
					std::unique_ptr<Shape> circle = std::make_unique<Circle>(radius, x, y, color[0], is_filled);

					circle->draw(blackboard);
					shapes.push_back(std::move(circle));
					
				}
				else {
					std::cout << "Invalid parameters";
					return;
				}
			}

			else if (type == "line") {
				std::string x_str, y_str, color, lenght_str;
				bool horison = 0;
				if (ss >> x_str >> y_str >> color >> lenght_str >> horison) {
					int x = convertIntoDigit(x_str);
					int y = convertIntoDigit(y_str);
					int length = convertIntoDigit(lenght_str);
					if (x < 0 || y < 0 || length < 0 || x > BOARD_WIDTH || y > BOARD_HEIGHT || (horison && x + length > BOARD_WIDTH) || (!horison && y + length > BOARD_HEIGHT)) {
						return;
					}
					std::unique_ptr<Shape> line = std::make_unique<Line>(length, x, y, color[0], horison);

					line->draw(blackboard);
					shapes.push_back(std::move(line));

				}
				else {
					std::cout << "Invalid parameters";
					return;
				}
			}

			else if (type == "rectangle") {
				std::string x_str, y_str, color, width_str, heigth_str;
				bool is_filled = 0;
				if (ss >> x_str >> y_str >> color >> width_str >> heigth_str >> is_filled) {
					int x = convertIntoDigit(x_str);
					int y = convertIntoDigit(y_str);
					int width = convertIntoDigit(width_str);
					int height = convertIntoDigit(heigth_str);
					if (x < 0 || y < 0 || width < 0 || height < 0 || x > BOARD_WIDTH || y > BOARD_HEIGHT || x + width > BOARD_WIDTH || y  + height > BOARD_HEIGHT) {
						return;
					}
					std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(width, height, x, y, color[0], is_filled);

					rectangle->draw(blackboard);
					shapes.push_back(std::move(rectangle));
				}
				else {
					std::cout << "Invalid parameters";
					return;
				}
			}
			else if (type == "triangle") {
				std::string x_str, y_str, color, width_str, heigth_str;
				bool is_filled = 0;
				if (ss >> x_str >> y_str >> color >> heigth_str >> is_filled) {
					int x = convertIntoDigit(x_str);
					int y = convertIntoDigit(y_str);
					int height = convertIntoDigit(heigth_str);
					if (x < 0 || y < 0 || height < 0 || x > BOARD_WIDTH || y > BOARD_HEIGHT || y + height > BOARD_HEIGHT  || x - height < 0 || x + height > BOARD_WIDTH){
						return;
					}
					std::unique_ptr<Shape> triangle = std::make_unique<Triangle>( height, x, y, color[0], is_filled);

					triangle->draw(blackboard);
					shapes.push_back(std::move(triangle));

				}
				else {
					std::cout << "Invalid parameters";
					return;
				}
			}
			else {
				std::cout << "Invalid type";
				return;
			}
		}
		else if (command == "draw") {
			blackboard.print();
		}
		else if (command == "list") {
			for (int i = 0; i < shapes.size(); i++) {
				shapes[i]->info_print();
			}
		}
		else if (command == "shapes") {
			std::printf("1. Circle \n 2. Rectangle \n 3. Line \n 4. Triangle \n ");
		}
		else if (command == "select") {
			std::string id_str;
			ss >> id_str;
			int id = convertIntoDigit(id_str);
			for (int i = 0; i < shapes.size(); i++) {
				if (shapes[i]->get_id() == id) {
					shapes[i]->info_print();
					selected_shape = i;
					break;
				}
				else {
					if (i == shapes.size() - 1) {
						std::printf("shape was not found");
					}
				}
			}
		}
		
		else if (command == "remove") {
			if (0 <= selected_shape < shapes.size()) {
				shapes[selected_shape]->remove(blackboard);
				shapes.erase(shapes.begin() + selected_shape);
				RenewScreen(blackboard);
			}
			else {
				std::printf("no selected shape");
			}
			
		}
		else if (command == "edit") {
			shapes[selected_shape]->remove(blackboard);
			shapes.erase(shapes.begin() + selected_shape);
			Handle_Type("add", ss, blackboard);
			RenewScreen(blackboard);
		}
		else if (command == "clear") {
			for (int i = 0; i < shapes.size(); i++) {
				shapes[i]->remove(blackboard);
				shapes.erase(shapes.begin() + i);
			}
			std::printf("Board is cleared!");
		}
		else if (command == "move") {

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
