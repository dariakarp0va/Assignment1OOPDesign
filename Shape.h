#pragma once

class Blackboard;

class Shape {
protected:
	int id = 0;
	int coordinate_x = 0;
	int coordinate_y = 0;
	char color = '*';
	bool is_filled = 0;
	bool is_valid = 1;
	std::string type;
	static int unique_id;
public:
	virtual void draw(Blackboard& blackboard) = 0;
	virtual void info_print() = 0;
	virtual std::string add_info_for_save() = 0;
	virtual bool apply_parameters(std::stringstream& ss) = 0;
	virtual void edit( std::stringstream& ss) = 0;
	virtual bool contains(int target_x, int target_y) = 0;
	void remove(Blackboard& blackboard);
	void move_to(int x, int y);
	bool check_valid();
	std::string get_type();
	int get_id();
	void paint(char Color);
	virtual ~Shape() = default;
};

