#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "Car.h"

class Person {
    private:
        std::string name;
        std::string email;
        std::unique_ptr<Car> car;
    public:
        Person(std::string name, std::string email, int seats = 0);

        std::string get_name() const;
        std::string get_email() const;
        void set_email(const std::string& newEmail);
        bool hasAvailableSeats() const;

        friend std::ostream& operator<<(std::ostream& os, const Person& person);
};