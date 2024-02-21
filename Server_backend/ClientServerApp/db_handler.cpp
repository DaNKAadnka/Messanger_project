#include "db_handler.h"
#include <sstream>

static int callback_all(void* data, int argc, char** argv, char** azColName);

void db_handler::open_db() {
	std::string database_name = m_database + ".dblite";
	if (sqlite3_open(database_name.c_str(), &db)) {
		std::cout << "Database opening error!\n" << sqlite3_errmsg(db);
	}
	create_table_if_not_exists();
}

void db_handler::open_db(std::string database) {
	std::string database_name = database + ".dblite";
	if (sqlite3_open(database_name.c_str(), &db)) {
		std::cout << "Database opening error!\n" << sqlite3_errmsg(db);
	}
	create_table_if_not_exists();
}

db_handler::~db_handler() {
	sqlite3_close(db);
}

void db_handler::create_table_if_not_exists() {

	if (sqlite3_exec(db, sql_create_users_table.c_str(), NULL, NULL, &err))
	{
		std::cout << "User table creating error!\n" << err << std::endl;
		sqlite3_free(err);
	}
	if (sqlite3_exec(db, sql_create_messages_table.c_str(), NULL, NULL, &err))
	{
		std::cout << "Messages table creating error!\n" << err << std::endl;
		sqlite3_free(err);
	}
}

bool db_handler::create_user_query(std::string login, std::string password) {

	std::string insert_query = "INSERT INTO USERS VALUES('" + login + "', '" + password + "');";
	if (sqlite3_exec(db, insert_query.c_str(), NULL, NULL, &err))
	{
		std::cout << "User creating error!\n" << err << std::endl;
		sqlite3_free(err);
		return false;
	}
	std::cout << "User created!\n";
	print_all_users();
	std::cout << "\n";
	return true;
}

bool db_handler::autho_user_query (std::string login, std::string password) {

	sqlite3_stmt* stmt;
	
	std::string select_query = "SELECT LOGIN FROM USERS WHERE LOGIN='" +
		login + "' AND PASSWORD='" + password + "';";

	if (sqlite3_prepare_v2(db, select_query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
		std::cout << "ERROR compiling autho sql\n";
		return false;
	}

	bool found = false;
	int ret_code = 0;
	while ((ret_code = sqlite3_step(stmt)) == SQLITE_ROW) {
		//printf("TEST: ID = %d\n", sqlite3_column_int(stmt, 0));
		found = true;
	}
	if (ret_code != SQLITE_DONE) {
		//this error handling could be done better, but it works
		//printf("ERROR: while performing sql: %s\n", sqlite3_errmsg(db));
		//printf("ret_code = %d\n", ret_code);

	}
	
	std::cout << (found ? "found" : "nout found") << "\n";
	return found;
	// 

	/*if (sqlite3_exec(db, select_query.c_str(), db_handler::autho_callback, NULL, &err))
	{
		std::cout << "User authorization error!\n" << err << std::endl;
		sqlite3_free(err);
	}*/
}


void db_handler::send_message_query(std::string sender, std::string reciever, std::string message) {

	std::string insert_query = "INSERT INTO MESSAGES VALUES('" + sender +
		"', '" + reciever + "', '" + message + "');";

	if (sqlite3_exec(db, insert_query.c_str(), NULL, NULL, &err))
	{
		std::cout << "Message Sending error!\n" << err << std::endl;
		sqlite3_free(err);
	}
	print_all_messages();

}

std::string db_handler::get_messages_query() {
	
	sqlite3_stmt* stmt;

	std::string select_query = "SELECT * FROM MESSAGES WHERE RECIEVER='@All';";

	if (sqlite3_prepare_v2(db, select_query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
		std::cout << "ERROR compiling autho sql\n";
		std::string response = "Command:Get Messages\n" \
			"Status:Error\n" \
			"Data:\n";
		return response;
	}

	bool found = false;
	int ret_code = 0;
	std::string response = "Command:Get Messages\n" \
		"Status:Success\n" \
		"Data:\n";
	while ((ret_code = sqlite3_step(stmt)) == SQLITE_ROW) {
		//printf("TEST: ID = %d\n", sqlite3_column_int(stmt, 0));
		found = true;
		//std::cout << ret_code << "\n";

		for (int i = 0; i < 3; i++) {
			const unsigned char* col_t = sqlite3_column_text(stmt, i);
			std::string xs = std::string(reinterpret_cast<char const*>(col_t));
			response += xs + "\n";
		}

		//std::cout << sqlite3_column_text(stmt, 0) << " " << sqlite3_column_text(stmt, 1) << " " << sqlite3_column_text(stmt, 2) << "\n";
	}
	if (ret_code != SQLITE_DONE) {
		//this error handling could be done better, but it works
		//printf("ERROR: while performing sql: %s\n", sqlite3_errmsg(db));
		//printf("ret_code = %d\n", ret_code);
	}

	std::cout << (found ? "messages found" : "messages not found") << "\n";

	return response;
}


// Testing functional

void db_handler::print_all_users() {

	std::string select_query = "SELECT * FROM USERS;";
	if (sqlite3_exec(db, select_query.c_str(), callback_all, NULL, &err))
	{
		std::cout << "User creating error!\n" << err << std::endl;
		sqlite3_free(err);
	}
}

void db_handler::print_all_messages() {
	std::string select_query = "SELECT * FROM MESSAGES;";
	if (sqlite3_exec(db, select_query.c_str(), callback_all, NULL, &err))
	{
		std::cout << "User creating error!\n" << err << std::endl;
		sqlite3_free(err);
	}
}

// Callback for our select command
static int callback_all(void* data, int argc, char** argv, char** azColName)
{

	const char* data_c = (const char*)data;
	//fprintf(stdin, "%s:", data_c);
	//std::string data_string = std::string(data_c);
	//std::cout << data_string << "\n";
	//std::cout << (const char*)data << std::endl;

	for (int i = 0; i < argc; i++) {
		std::cout << azColName[i] << " " << (argv[i] ? argv[i] : "NULL") << " ";
	}
	std::cout << "\n";
	return 0;
}