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
#include <chrono> // For time routines

using namespace SimpleERP;
using namespace std;

// Global instances
LogSystem* ls;

DbConnection::DbConnection()
{
	// Global instances
	ls = new LogSystem();

	// Initializes the database instance
	dbInstance = mysql_init(dbInstance);

	if (dbInstance == NULL)
	{
		ls->write("[Error] An database error has occured: ");
		ls->write(mysql_error(dbInstance));
	}
	else
	{
		ls->write("[Log] dbInstance initialized successfully");
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
		ls->write("[Error] An database error has occured: ");
		ls->write(mysql_error(dbInstance));
	}
	else
	{
		ls->write("[Log] Database successfully connected");
	};

	// Set current database character set for utf8
	mysql_set_character_set(dbInstance, "utf8");

	if (dbInstance == NULL)
	{
		ls->write("[Error] An database error has occured: ");
		ls->write(mysql_error(dbInstance));
	}
	else
	{
		// Enable the connection flag
		this->connected = true;

		ls->write("[Log] Database charset successfully changed to UTF-8");
	};
};

DbConnection::~DbConnection()
{
	if (this->connected)
	{
		mysql_shutdown(dbInstance, SHUTDOWN_DEFAULT);
		mysql_close(dbInstance);

		this->connected = false;
		ls->write("[Log] Database disconnected successfully");
	}
	else
	{
		ls->write("[Error] An database error has occured: ");
		ls->write(mysql_error(dbInstance));
	};
};

void DbConnection::reconnect()
{
	if (this->connected == false && dbInstance == NULL)
	{
		// Initializes the database instance
		dbInstance = mysql_init(dbInstance);
		
		if (dbInstance == NULL)
		{
			ls->write("[Error] An database error has occured: ");
			ls->write(mysql_error(dbInstance));
		}
		else
		{
			ls->write("[Log] dbInstance initialized successfully");
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
			ls->write("[Error] An database error has occured: ");
			ls->write(mysql_error(dbInstance));
		}
		else
		{
			ls->write("[Log] Database successfully reconnected");
		};

		this->connected = true;
	}
	else
	{
		ls->write("[Error] An database error has occured: ");
		ls->write(mysql_error(dbInstance));
		
		return;
	};
};

void DbConnection::query(const char* Statement, unsigned long Size)
{
	if (this->connected == true && dbInstance != NULL)
	{
		mysql_real_query(dbInstance, Statement, Size);

		ls->write("[Log] Database query performed successfully");
	}
	else
	{
		ls->write("[Error] An database error has occured: ");
		ls->write(mysql_error(dbInstance));
		
		return;
	};
};