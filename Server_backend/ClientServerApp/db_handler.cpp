#include "db_handler.h"

static int callback_all(void* data, int argc, char** argv, char** azColName);

void db_handler::open_db() {
	std::string database_name = m_database + ".dblite";
	if (sqlite3_open(database_name.c_str(), &db)) {
		std::cout << "Database opening error!\n" << sqlite3_errmsg(db);
	}
}

void db_handler::open_db(std::string database) {
	std::string database_name = database + ".dblite";
	if (sqlite3_open(database_name.c_str(), &db)) {
		std::cout << "Database opening error!\n" << sqlite3_errmsg(db);
	}
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

void db_handler::create_user_query(std::string login, std::string password) {

	std::string insert_query = "INSERT INTO USERS VALUES('" + login + "', '" + password + "');";
	if (sqlite3_exec(db, insert_query.c_str(), NULL, NULL, &err))
	{
		std::cout << "User creating error!\n" << err << std::endl;
		sqlite3_free(err);
	}
}

void db_handler::autho_user_query(std::string login, std::string password) {
	
	std::string select_query = "SELECT * FROM USERS;";
	if (sqlite3_exec(db, select_query.c_str(), callback_all, NULL, &err))
	{
		std::cout << "User creating error!\n" << err << std::endl;
		sqlite3_free(err);
	}
}


void db_handler::send_message_query(std::string sender, std::string reciever, std::string message) {

	std::string insert_query = "INSERT INTO MESSAGES VALUES('" + sender +
		"', '" + reciever + "', '" + message + "');";

	if (sqlite3_exec(db, insert_query.c_str(), NULL, NULL, &err))
	{
		std::cout << "Message Sending error!\n" << err << std::endl;
		sqlite3_free(err);
	}
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

// Callback for our select command
static int callback_all(void* data, int argc, char** argv, char** azColName)
{
	int i;
	const char* data_c = (const char*)data;
	//fprintf(stdin, "%s:", data_c);
	//std::string data_string = std::string(data_c);
	//std::cout << data_string << "\n";
	//std::cout << (const char*)data << std::endl;

	for (i = 0; i < argc; i++) {
		std::cout << azColName[i] << " " << (argv[i] ? argv[i] : "NULL") << " ";
	}
	std::cout << "\n";
	return 0;
}