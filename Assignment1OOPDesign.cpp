// Assignment1OOPDesign.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "const.h"
#include "Shape.h"
#include "Blackboard.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "Triangle.h"
#include "Manager.h"


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
	try {
		return std::stoi(lineNum); 
	}
	catch (const std::exception& e) {
		std::cout << "number is too large\n";
		return -1;
	}
}

int main()
{
	Blackboard blackboard = Blackboard();
	Manager mng = Manager();
	mng.run(blackboard);
}
