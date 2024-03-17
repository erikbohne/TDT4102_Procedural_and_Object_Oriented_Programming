#pragma once

class Car {
    private:
        int freeSeats;
    public:
        Car(int nFreeSeats) : freeSeats(nFreeSeats) {};
        bool hasFreeSeats() const;
        void reserveFreeSeat();
};