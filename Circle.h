#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Blackboard.h"
#include "const.h"

class Circle : public Shape {
private:
	int radius = 0;
public:
	Circle(std::stringstream& ss);

	void draw(Blackboard& blackboard) override;
	bool contains(int target_x, int target_y) override;
	void edit(Blackboard& blackboard, std::stringstream& ss);
	std::string add_info_for_save() override;
	void info_print() override;
	~Circle() override = default;
};
