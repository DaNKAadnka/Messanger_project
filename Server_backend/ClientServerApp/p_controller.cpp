#include "p_controller.h"
#include <sstream>
#include <vector>

p_controller::p_controller() {

	db_handler db_c("messanger_db");
	db = db_c;

	db.open_db();
}


void p_controller::parseString(std::string& message) {

	std::stringstream ss;

	std::string line;
	std::vector <std::string> lines;
	while (getline(ss, line)) {
		lines.push_back(line);
	}


}