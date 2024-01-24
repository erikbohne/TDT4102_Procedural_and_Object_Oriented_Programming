#include "cannonball.h"

// 2a)
double acclY() {
    return -9.81;
}

// 2b)
double velY(double initVelocityY, double time) {
    double vel = initVelocityY + acclY() * time;
    return vel;
}

// 2c)
double posX(double initPositionX, double initVelocityX, double time) {
    double pos = initPositionX + initVelocityX * time;
    return pos;
}

double posY(double initPositionY, double initVelocityY, double time) {
    double pos = initPositionY + initVelocityY * time + (acclY() * pow(time, 2)) / 2;
    return pos;
}

// 2d)
void printTime(double seconds) {
    int hours = static_cast<int>(seconds) / 3600;
    int minutes = static_cast<int>(seconds - hours * 3600) / 60;
    seconds = (seconds - (hours * 3600 + minutes * 60));
    cout << hours << "h " << minutes << "m " << seconds << "s " << endl;
}

// 2e)
double flightTime(double initVelocityY) {
    double time = -2 * initVelocityY / acclY();
    return time;
}

// 4a)
// Ber brukeren om en vinkel i grader
double getUserInputTheta() {
    cout << "Skriv inn en vinkel i grader: ";
    double inputTheta;
    cin >> inputTheta;
    return inputTheta;
}

//Ber brukeren om en startfart
double getUserInputInitVelocity() {
    cout << "Skriv inn startfart: ";
    double initVelocity;
    cin >> initVelocity;
    return initVelocity;
}

// Konverterer fra grader til radianer
double degToRad(double deg) {
    double rad = deg * (M_PI / 180.0);
    return rad;
}

// Returnerer henholdsvis farten i x-, og y-retning, gitt en vinkel
// theta i grader og en startfart initVelocity.
double getVelocityX(double theta, double initVelocity) {
    double velX = cos(degToRad(theta)) * initVelocity;
    return velX;
}
double getVelocityY(double theta, double initVelocity) {
    double velY = sin(degToRad(theta)) * initVelocity;
    return velY;
}

// Dekomponerer farten gitt av initVelocity, i x- og y-komponentene
// gitt vinkelen theta. Det første elementet i vectoren skal være
//x-komponenten, og det andre elementet skal være y-komponenten.
// "Vector" i funksjonsnavnet er vektor-begrepet i geometri
vector<double> getVelocityVector(double theta, double initVelocity) {
    vector<double> velVector {getVelocityX(theta, initVelocity), getVelocityY(theta, initVelocity)};
    return velVector;
}

// 4b)
double getDistanceTraveled(double velocityX, double velocityY) {
    double pos = posX(0, velocityX, flightTime(velocityY));
    return pos;
}

// 4c)
double targetPractice(double distanceToTarget, double velocityX, double velocityY) {
    double error = distanceToTarget - getDistanceTraveled(velocityX, velocityY);
    return error;
}