#pragma once

#include "db_handler.h"

class p_controller {

public:

	p_controller();
	~p_controller();

	void parseString(std::string& message);
private:

	db_handler db;
};