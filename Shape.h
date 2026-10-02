

class Shape {
	virtual void draw(Blackboard& blackboard) = 0;
	virtual void info_print() = 0;
	virtual std::string add_info_for_save() = 0;
	virtual void edit(Blackboard& blackboard, std::stringstream& ss) = 0;
	virtual bool contains(int target_x, int target_y) = 0;
	void remove(Blackboard& blackboard);
	void move_to(int x, int y);
	bool check_valid();
	std::string get_type();
	int get_id();
	void paint(char Color);
	virtual ~Shape() = default;
};

