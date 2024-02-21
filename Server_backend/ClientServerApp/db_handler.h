#pragma once

#include <string>
#include <sqlite3.h>
#include <iostream>

class db_handler {

public:

	db_handler() {}
	db_handler(std::string database) : m_database(database) {}
	~db_handler();

	void open_db();
	void open_db(std::string);

	void print_all_users();
	void print_all_messages();

	void create_table_if_not_exists();

	bool create_user_query(std::string login, std::string password);

	bool autho_user_query(std::string login, std::string password);

	void send_message_query(std::string sender, std::string reciever, std::string message);

	std::string get_messages_query();
	
	


private:

	std::string m_database = "messanger_db";

	// sql create table queries
	std::string sql_create_users_table = "CREATE TABLE IF NOT EXISTS USERS(" \
		"LOGIN      TEXT     NOT NULL     UNIQUE," \
		"PASSWORD   TEXT     NOT NULL);";

	std::string sql_create_messages_table = "CREATE TABLE IF NOT EXISTS MESSAGES(" \
		"SENDER     TEXT     NOT NULL," \
		"RECIEVER   TEXT     NOT NULL," \
		"MESSAGE    TEXT     NOT NULL);";

	// sqlite handle object
	sqlite3* db = 0;
	char* err = 0;
	
};