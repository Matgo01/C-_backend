#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "crow_all.h"
#include "database.h"
#include "user.h"
#include <string>
#include <memory>

class UserController{
    private:
      Database& db;

    public: 
       UserController(Database& database);

       void addRoutes(crow::SimpleApp& app);

    private:
       void createUser(const crow::request& req, crow::response& res);
       void getUser(const crow::request& req, crow::response& res);
       void updateUser(const crow::request& req, crow::response& res);
       void deleteUser(const crow::request& req, crow::response& res);
};

#endif 