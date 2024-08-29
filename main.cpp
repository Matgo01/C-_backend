#include "crow_all.h"
#include "database.h"
#include "usercontroller.h"
#include <iostream>

int main(){
    crow::SimpleApp app;

    Database db("mysql://localhost:3306","username","passowrd","mydb");

    if(!db.connect()){
        std::cerr<<"failed to connect to the database"<<std::endl;
        return 1;
    }

    UserController userController(db);
    userController.addRoutes(app);

    app.port(8080).multithreaded().run();

    return 0;
}