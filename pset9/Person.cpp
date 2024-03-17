#include "Person.h"

Person::Person(std::string name, std::string email, int seats) : name(name), email(email) {
    if (seats > 0) {
        car = std::make_unique<Car>(seats);
    }
}

std::string Person::get_name() const {
    return name;
}

std::string Person::get_email() const {
    return email;
}

void Person::set_email(const std::string& newEmail) {
    this->email = newEmail;
}

bool Person::hasAvailableSeats() const {
    if (car != nullptr) {
        return this->car->hasFreeSeats();
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Name: " << person.get_name() << "\n";
    os << "Email: " << person.get_email() << "\n";
    os << "Available Seats: " << (person.hasAvailableSeats() ? "Yes" : "No") << "\n";
    return os;
}