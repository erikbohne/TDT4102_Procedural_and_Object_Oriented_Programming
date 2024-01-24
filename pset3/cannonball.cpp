#include "cannonball.h"

// a)
double acclY() {
    return -9.81;
}

// b)
double velY(double initVelocityY, double time) {
    double vel = initVelocityY + acclY() * time;
    return vel;
}

// c)
double posX(double initPositionX, double initVelocityX, double time) {
    double pos = initPositionX + initVelocityX * time;
}

double posY(double initPositionY, double initVelocityY, double time) {
    double pos = initPositionY + initVelocityY * time + (acclY() * pow(time, 2)) / 2;
}

// d)
void printTime(double seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds - hours * 3600) / 60;
    seconds = (seconds - (hours * 3600 + minutes * 60));
    cout << hours << "h " << minutes << "m " << seconds << "s " << endl;
}

// e)
double flightTime(double initVelocityY) {
    double time = -2 * initVelocityY / acclY();
    return time;
}