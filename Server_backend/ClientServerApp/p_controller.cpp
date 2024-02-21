#include "p_controller.h"
#include <sstream>
#include <vector>

p_controller::p_controller() {

	db_handler db_c("messanger_db");
	db = db_c;

	db.open_db();
}


void p_controller::parseString (std::string& message) {

	std::stringstream ss;

	std::string line;
	std::vector <std::string> lines;
	while (getline(ss, line)) {
		lines.push_back(line);
	}


}

std::string p_controller::sendProtocolMessage(std::string text) {

	std::string request = "Command:Send Message\n" \
		"Status:Check" \
		"Data:\n" + text;
	
	return request;
}

std::string p_controller::processData(std::string& message) {

	std::istringstream ss(message);

	std::string line;
	std::vector <std::string> lines;
	while (getline(ss, line, '\n')) {
		lines.push_back(line);
	}

	for (auto it : lines) {
		std::cout << "l " << it << "\n";
	}

	std::string command = lines[0].erase(0, 8);
	std::string status = lines[1].erase(0, 7);
	// lines[2] - not neccessery data


	//Route commands
	if (command == "Register") {

		std::string login = lines[3].erase(0, 6);
		std::string password = lines[4].erase(0, 9);

		std::string response;
		
		if (db.create_user_query(login, password)) {

			response = "Command:Register\n" \
				"Status:Success\n" \
				"Data:\n" \
				"Login:" + login + "\n" +
				"Password:" + password;;
		}
		else {
			response = "Command:Register\n" \
				"Status:Error\n" \
				"Data:\n" \
				"Login:" + login + "\n" +
				"Password:" + password;;
		}

		return response;


		// Something should happen
		// Yes, we should send response to c# client
	}
	else if (command == "Authorize") {

		std::string login = lines[3].erase(0, 6);
		std::string password = lines[4].erase(0, 9);
		

		std::string response;

		if (db.autho_user_query(login, password)) {

			response = "Command:Authorize\n" \
				"Status:Success\n" \
				"Data:\n" \
				"Login:" + login + "\n" +
				"Password:" + password;
		}
		else {
			response = "Command:Authorize\n" \
				"Status:Error\n" \
				"Data:\n" \
				"Login:" + login + "\n" +
				"Password:" + password;;
		}

		return response;
	}
	else if (command == "Get Messages") {

		std::string response = db.get_messages_query();

		return response;

	}
	else if (command == "Send Message") {

		std::string sender = lines[3].erase(0, 7);
		std::string reciever = "@All";
		std::string message = lines[5].erase(0, 8);
		db.send_message_query(sender, reciever, message);
		// Some tricky parsing
		std::string response = "Command:Send Message\n" \
			"Status:Success\n" \
			"Data:\n" +
			message;

		return response;
	}

	std::cout << command << " " << status << "\n";
}

