#pragma once
#include <iostream>
#include <vector>
#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "Blackboard.h"
#include "const.h"

class Rectangle : public Shape {
private:
	int width = 0;
	int height = 0;
public:
	Rectangle(std::stringstream& ss);

	void draw(Blackboard& blackboard) override;
	bool contains(int target_x, int target_y) override;
	void edit( std::stringstream& ss) override;
	bool apply_parameters(std::stringstream& ss) override;
	std::string add_info_for_save() override;
	void info_print() override;
	~Rectangle() override = default;
};