#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string _name;
    std::string _surname;
    std::string _email;
    int _age;

public:
    // Constructor declaration
    User(const std::string& name, const std::string& surname, const std::string& email, int age);

    // Getter methods
    std::string getName() const;
    std::string getSurname() const;
    std::string getEmail() const;
    int getAge() const;

    // Setter methods
    void setName(const std::string& name);
    void setSurname(const std::string& surname);
    void setEmail(const std::string& email);
    void setAge(int age);
};

#endif // USER_H
