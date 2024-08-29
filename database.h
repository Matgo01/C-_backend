#ifndef DATABASE_H
#define DATABASE_H

#include "crow_all.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <memory>

class Database {
private:
    sql::mysql::MySQL_Driver *driver;
    std::unique_ptr<sql::Connection> conn;
    std::unique_ptr<sql::Statement> stmt;
    std::unique_ptr<sql::ResultSet> res;

    std::string host;
    std::string user;
    std::string password;
    std::string database;

public:
    // Constructor to initialize the connection details
    Database(const std::string& db_host, const std::string& db_user, const std::string& db_password, const std::string& db_database);

    // Establish connection to the MySQL database
    bool connect();

    // Execute a query and return the result
    std::unique_ptr<sql::ResultSet> executeQuery(const std::string& query);

    // Destructor
    ~Database();
};

#endif // DATABASE_H