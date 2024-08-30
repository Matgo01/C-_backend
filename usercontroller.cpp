#include "userController.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>


UserController::UserController(Database& database) : db(database){}

void UserController::addRoutes(crow::SimpleApp& app){
    CROW_ROUTE(app, "/user/create").methods(crow::HTTPMethod::Post)([this](const crow::request& req){
        crow::response res;
        createUser(req, res);
        return res;
     });

    CROW_ROUTE(app, "/user/<int>").methods(crow::HTTPMethod::Get)([this](const crow::request& req, int userId) {
        crow::response res;
        getUser(req, res);
        return res;
    });

    CROW_ROUTE(app, "/user/update/<int>").methods(crow::HTTPMethod::Put)([this](const crow::request& req, int userId) {
        crow::response res;
        updateUser(req, res);
        return res;
    });

    CROW_ROUTE(app, "/user/delete/<int>").methods(crow::HTTPMethod::Delete)([this](const crow::request& req, int userId) {
        crow::response res;
        deleteUser(req, res);
        return res;
    });
    }

}

void UserController::createUser(const crow::request& req, crow::response& res){
    try{
        auto json = crow::json::load(req.body);
        if(!json){
            res.code = 400;
            res.write("Invalid json");
            return;
        }
        std::string name = json["name"].s();
        std::string surname = json["surname"].s();
        std::string email = json["email"].s();
        int age = json["age"].i();

        std::string query = "INSERT INTO users (name,surname,email,age) VALUES (?,?,?,?)";
        auto result = db.executeQuery(query);

        if(result){
            res.code = 201;
            res.write("User created");

        }else {
            res.code = 500;
            res.write("database error");
            
        }
        

    }catch(sql::SQLException& e){
        res.code = 500;
        res.write("Database error: " + std::string(e.what()));

    }
}

void UserController::getUser(const crow::request& req, crow::response& res){
    try{
        int userId = std::stoi(req.url_params.get("userId"));
        std::string query = "SELECT name, surname, email, age FROM users WHERE id = "+std::to_string(userId);
        auto result = db.executeQuery(query);

        crow::json::wvalue response;
        if(result && result->next()){
            response["name"] = result->getString("name");
            response["surname"] = result->getString("surname");
            response["email"] = result->getString("email");
            response["age"] = result->getInt("age");
        }else {
            res.code = 404;
            res.write("User not found");
            return;
        }
        res.code = 200;
        res.write(response.dump());

    }catch(sql::Exception& e){
        res.code = 500;
        res.write("Database error:" +std::string(e.what()));
    }

}

void UserController::updateUser(const crow::request& req, crow::response& res){
    try{
        int userId = std::stoi(req.url_params.get("userId"));
        auto json = crow::json::load(req.body);
        if(!json){
            res.code = 400;
            res.write("Invalid json");
            return;
        }
        std::string name = json["name"].s();
        std::string surname = json["surname"].s();
        std::string email = json["email"].s();
        int age = json["age"].i();

        std::string query = "UPDATE users SET name = '" + name + "', surname = '" + surname + "', email = '" + email + "', age = " + std::to_string(age) + " WHERE id = " + std::to_string(userId); 
        auto result = db.executeQuery(query);
        if(result){
            res.code = 200;
            res.write("User updated");
        }else{
            res.code = 500;
            res.write("Database error");
        }
           }catch(sql::Exception& e){
            res.code = 500;
            res.write("Database error"+std::string(e.what()));
           }
}

void UserController::deleteUser(const crow::request& req, crow::response& res){
    try{
        int userId = std::stoi(req.url_params.get("userId"));
        std::string query = "DELETE FROm users WHERE id = "+std::to_string(userId);
        auto result = db.executeQuery(query);

        if(result){
            res.code = 200;
            res.write("User deleted");
        }else{
            res.code = 500;
            res.write("Database error");
        }
    }catch(sql::Exception& e){
        res.code = 500;
        res.write("Database error:"+std::string(e.what()));
    }
}
