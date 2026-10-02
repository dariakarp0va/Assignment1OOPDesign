#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Blackboard.h"
#include "const.h"


class Triangle : public Shape {
private:

	int height = 0;
public:
	Triangle(std::stringstream& ss);
	void draw(Blackboard& blackboard) override;
	bool contains(int target_x, int target_y) override;
	void edit(Blackboard& blackboard, std::stringstream& ss) override;
	std::string add_info_for_save() override;
	void info_print() override;
	~Triangle() override = default;
};