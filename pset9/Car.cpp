#include "Car.h"

bool Car::hasFreeSeats() const {
    return freeSeats > 0;
}

void Car::reserveFreeSeat() {
    freeSeats--;
}