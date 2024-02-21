#pragma once

#include "db_handler.h"

class p_controller {

public:

	p_controller();

	std::string processData(std::string& message);
	void parseString(std::string& message);
	
	std::string sendProtocolMessage(std::string text);
private:

	db_handler db;
};