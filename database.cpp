#include "Database.h"

// Constructor: Initializes the MySQL driver and connection details
Database::Database(const std::string& db_host, const std::string& db_user, const std::string& db_password, const std::string& db_database)
    : driver(sql::mysql::get_mysql_driver_instance()), host(db_host), user(db_user), password(db_password), database(db_database) {
}

// Connect to the MySQL database
bool Database::connect() {
    try {
        
        conn = std::unique_ptr<sql::Connection>(driver->connect(host, user, password));
        // Set the database schema
        conn->setSchema(database);
        return true;
    } catch (sql::SQLException &e) {
        // Print the error message
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

std::unique_ptr<sql::ResultSet> Database::executeQuery(const std::string& query){
    try{
        stmt = std::unique_ptr<sql::Statement>(conn->createStatement());
        res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query));
        return std::move(res);
    }catch(sql::SQLException &e){
        std::cerr<<"SQL error:"<<e.what()<<std::enl;
        return nullptr;
    }
}

Database::~Database() {
   
}
