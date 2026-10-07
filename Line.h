#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Blackboard.h"
#include "const.h"

class Line : public Shape {
private:
	int length = 0;
	bool horison = 1;
public:
	Line(std::stringstream& ss);
	void draw(Blackboard& blackboard) override;
	bool contains(int target_x, int target_y) override;
	void edit(std::stringstream& ss) override;
	bool apply_parameters(std::stringstream& ss) override;
	std::string add_info_for_save() override;
	void info_print() override;
	~Line() override = default;

};