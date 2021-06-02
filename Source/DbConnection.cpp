/*
	SimpleERP ERP System
	Copyright (C) 2021 Miguel Nischor

	File: DbConnection.cpp
	Description: Implementation for DbConnection class.
	Author: Miguel Nischor <miguel@nischor.com.br>
*/
#include "DbConnection.hpp"
#include <iostream>

using namespace SimpleERP;
using namespace std;

DbConnection::DbConnection()
{
	// Initializes the database instance
	dbInstance = mysql_init(dbInstance);
	clog << "[Log] dbInstance initialized";

	// Set current configuration for database connection
	dbInstance = mysql_real_connect(dbInstance,				// Instance
									"localhost",			// Server address
									"root",					// Username
									"CodeBrasil",			// Password
									"SERP",					// Database
									3306,					// Port (Default is 3306)
									NULL,					// Socket
									CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS);
	clog << "[Log] dbInstance connected to database";

	// Set current database character set for utf8
	mysql_set_character_set(dbInstance, "utf8");
	clog << "[Log] dbInstance changed default charset to UTF-8";

	if (dbInstance == NULL)
	{
		// Raise error message for any MySQL/MariaDB issue
		cerr << "[Error] An database error has occured: " << mysql_error(dbInstance);
	}
	else
	{
		// Enable the connection flag
		this->connected = true;
		clog << "[Log] Database successfully connected";
	};
};

DbConnection::~DbConnection()
{
	if (this->connected)
	{
		mysql_shutdown(dbInstance, SHUTDOWN_DEFAULT);
		mysql_close(dbInstance);

		this->connected = false;
	}
	else
	{
		cerr << "[Error] An database error has occured: " << mysql_error(dbInstance);
	};
};

void DbConnection::reconnect()
{
	if (this->connected == false && dbInstance == NULL)
	{
		// Initializes the database instance
		dbInstance = mysql_init(dbInstance);
		clog << "[Log] dbInstance initialized";

		// Set current configuration for database connection
		dbInstance = mysql_real_connect(dbInstance,				// Instance
										"localhost",			// Server address
										"root",					// Username
										"CodeBrasil",			// Password
										"SERP",					// Database
										3306,					// Port (Default is 3306)
										NULL,					// Socket
										CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS);
		clog << "[Log] dbInstance connected to database";

		this->connected = true;
	}
	else
	{
		cerr << "[Error] An database error has occured: " << mysql_error(dbInstance);
		return;
	};
};

void DbConnection::query(const char* Statement, unsigned long Size)
{
	if (this->connected == true && dbInstance != NULL)
	{
		mysql_real_query(dbInstance, Statement, Size);
		clog << "[Log] Database query performed successfully";
	}
	else
	{
		cerr << "[Error] An database error has occured: " << mysql_error(dbInstance);
		return;
	};
};