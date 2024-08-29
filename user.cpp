#include "user.h"

User::User(const std::string& name, const std::string& surname, const std::string email, int age)
:_name(name),_surname(surname),_email(email),_age(age){

}

User::getName() const{
    return _name;
}

User::getSurname() const{
    return _surname;
}

User::getAge() const{
    return _age;
}

User::getEmail() const{
    return _email;
}

User::setAge(int new age){
    _age = age;
}

User::setName(std::string newname){
    _name = newname;
}

User::setSurname(std::string newsurname){
    _surname = newsurname;
}

User::setEmail(std::string newemail){
    _email = newemail;
}