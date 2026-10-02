#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Manager.h"
#include "const.h"

void Manager::RenewScreen(Blackboard& blackboard) {
	std::vector<std::unique_ptr<Shape>>& shapes = blackboard.get_shapes();
	for (int i = 0; i < blackboard.get_shapes().size(); i++) {
		blackboard.get_shapes()[i]->remove(blackboard);
		blackboard.get_shapes()[i]->draw(blackboard);
	}
	blackboard.print();
}


void Manager::Handle_Type(std::string command, std::stringstream& ss, Blackboard& blackboard) {
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
				if (!blackboard.is_clone(line)) {
					line->draw(blackboard);
					blackboard.get_shapes().push_back(std::move(line));
				}
				else {
					std::cout << "Can`t add the same shapes on board\n";
				}
			}
		}

		else if (type == "rectangle") {

			std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(ss);
			if (rectangle->check_valid()) {
				if (!blackboard.is_clone(rectangle)) {
					rectangle->draw(blackboard);
					blackboard.get_shapes().push_back(std::move(rectangle));
				}
				else {
					std::cout << "Can`t add the same shapes on board\n";
				}
			}
		}
		else if (type == "triangle") {

			std::unique_ptr<Shape> triangle = std::make_unique<Triangle>(ss);
			if (triangle->check_valid()) {
				if (!blackboard.is_clone(triangle)) {
					triangle->draw(blackboard);
					blackboard.get_shapes().push_back(std::move(triangle));
				}
				else {
					std::cout << "Can`t add the same shapes on board\n";
				}
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
		std::string x_str, y_str;
		if (ss >> x_str) {
			if (ss >> y_str) {
				int x = convertIntoDigit(x_str);
				int y = convertIntoDigit(y_str);
				for (int i = blackboard.get_shapes().size() - 1; i >= 0; i--) {
					if (blackboard.get_shapes()[i]->contains(x, y)) {
						shapes[i]->info_print();
						blackboard.select(i);
						break;
					}
				}
			}
			else {
				int id = convertIntoDigit(x_str);
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
		}
		else {
			std::cout << "You need to pass arguments \n";
		}


	}

	else if (command == "remove") {
		if (0 <= blackboard.get_selected_shape() && blackboard.get_selected_shape() < shapes.size()) {
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
			if (ss >> color) {
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

void Manager::run(Blackboard& blackboard) {
	while (true) {
		std::string input_line;
		std::getline(std::cin, input_line);
		std::stringstream ss(input_line);
		std::string action;
		ss >> action;
		Handle_Type(action, ss, blackboard);
	}
}