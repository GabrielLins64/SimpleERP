/*
	SimpleERP ERP System
	Copyright (C) 2021 Miguel Nischor

	File: DbConnection.cpp
	Description: Implementation for DbConnection class.
	Author: Miguel Nischor <miguel@nischor.com.br>
*/
#include "DbConnection.hpp"
#include "LogSystem.hpp"
#include <iostream>
#include <cstdio>
#ifdef __linux__
#include <cstring>
#endif

using namespace SimpleERP;
using namespace std;

// Global instances
LogSystem* ls;

// Global variables
static string db_error				= "[Error] An database error has occured: ";
static string db_initialization		= "[Log] dbInstance initialized successfully";
static string db_connected			= "[Log] Database successfully connected";
static string db_disconnect 		= "[Log] Database disconnected successfully";
static string db_reconnect 			= "[Log] Database successfully reconnected";
static string db_mysql_client		= "[Log] MySQL client version: ";
static string db_mysql_server		= "[Log] MySQL server version: ";
static string db_mysql_charset		= "[Log] Database charset successfully changed to UTF-8";
static string db_mysql_fields		= "[Log] Number of fields obtained from database";
static string db_mysql_query		= "[Log] MySQL query performed successfully";

/*
	Function: DbConnection()
	Description: Default constructor, initialize database connection
	Return value: No return value
*/
DbConnection::DbConnection()
{
	// Global instances
	ls = new LogSystem();

	// Initializes the database instance
	dbInstance = mysql_init(dbInstance);

	if (dbInstance == NULL)
	{
		ls->write(db_error.c_str());
		ls->write(mysql_error(dbInstance));
	}
	else
	{
		ls->write(db_initialization.c_str());
	}

	// Set current configuration for database connection
	dbInstance = mysql_real_connect(dbInstance,				// Instance
									"localhost",			// Server address
									"root",					// Username
									"root",					// Password
									"SERP",					// Database
									3306,					// Port (Default is 3306)
									NULL,					// Socket
									CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS);

	if (dbInstance == NULL)
	{
		ls->write(db_error.c_str());
		ls->write(mysql_error(dbInstance));
	}
	else
	{
		ls->write(db_mysql_client.c_str(), mysql_get_client_info());
		ls->write(db_mysql_server.c_str(), mysql_get_server_info(dbInstance));
		ls->write(db_connected.c_str());
	};

	// Set current database character set for utf8
	mysql_set_character_set(dbInstance, "utf8");

	if (dbInstance == NULL)
	{
		ls->write(db_error.c_str());
		ls->write(mysql_error(dbInstance));
	}
	else
	{
		// Enable the connection flag
		this->connected = true;

		ls->write(db_mysql_charset.c_str());
	};
};

/*
	Function: ~DbConnection()
	Description: Default destructor, terminate database connection
	Return value: No return value
*/
DbConnection::~DbConnection()
{
	if (this->connected)
	{
		mysql_close(dbInstance);

		this->connected = false;
		ls->write(db_disconnect.c_str());
	}
	else
	{
		ls->write(db_error.c_str());
		ls->write(mysql_error(dbInstance));
	};
};

/*
	Function: reconnect()
	Description: Atempt to reconnect to the database
	Return value: No return value
*/
void DbConnection::reconnect()
{
	if (this->connected == false && dbInstance == NULL)
	{
		// Initializes the database instance
		dbInstance = mysql_init(dbInstance);
		
		if (dbInstance == NULL)
		{
			ls->write(db_error.c_str());
			ls->write(mysql_error(dbInstance));
		}
		else
		{
			ls->write(db_initialization.c_str());
		}

		// Set current configuration for database connection
		dbInstance = mysql_real_connect(dbInstance,				// Instance
										"localhost",			// Server address
										"root",					// Username
										"root",					// Password
										"SERP",					// Database
										3306,					// Port (Default is 3306)
										NULL,					// Socket
										CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS);

		if (dbInstance == NULL)
		{
			ls->write(db_error.c_str());
			ls->write(mysql_error(dbInstance));
		}
		else
		{
			ls->write(db_reconnect.c_str());
		};

		this->connected = true;
	}
	else
	{
		ls->write(db_error.c_str());
		ls->write(mysql_error(dbInstance));
		
		return;
	};
};

/*
	Function: query(const char*, const char*)
	Description: Perform a SQL query to the database
	Return value: No return value
*/
void DbConnection::query(const char* Statement, unsigned long Size)
{
	if (this->connected == true && dbInstance != NULL)
	{
		if (mysql_real_query(dbInstance, Statement, Size))
		{
			ls->write(db_error.c_str());
			ls->write(mysql_error(dbInstance));
		}
		dbResult = mysql_store_result(dbInstance);

		ls->write(db_mysql_query.c_str());
	}
	else
	{
		ls->write(db_error.c_str());
		ls->write(mysql_error(dbInstance));
		
		return;
	};
};

/*
	Function: getQueryData()
	Description: Returns all data from previous database query
	Return value: Previous data from database query
*/
const char* DbConnection::getQueryData()
{
	string buffer(4096, 0);
	static char* field_data = new char[4096];

	if (this->connected == true && dbInstance != NULL)
	{
		memset(field_data, '\0', 4096);

		// Get number of fields (cells) from executed query
		int fields = mysql_num_fields(dbResult);
		ls->write(db_mysql_fields.c_str());

		// Keep fetching result rows until the end
		while (dbRow = mysql_fetch_row(dbResult))
		{
			// Print all columns
			for (int i = 0; i < fields; i++)
			{
				strcat(field_data, (char*)dbRow[i]);
				strcat(field_data, (char*)"\n");
			};
		};

		buffer.assign(field_data);

		return (const char*)buffer.c_str();
	}
	else
	{
		ls->write(db_error.c_str());
		ls->write(mysql_error(dbInstance));

		return nullptr;
	};

	if (dbResult != NULL)
		mysql_free_result(dbResult);

	free(field_data);
};

/*
	Function: isConnected()
	Description: Check is database is connected
	Return value: true or false
*/
bool DbConnection::isConnected()
{
	return connected;
};