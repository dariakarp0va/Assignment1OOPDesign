#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Blackboard.h"
#include "const.h"

int convertIntoDigit(std::string lineNum);

class Manager {
private:
	void RenewScreen(Blackboard& blackboard);


	void Handle_Type(std::string command, std::stringstream& ss, Blackboard& blackboard);
public:
	void run(Blackboard& blackboard);
};
