#include "std_lib_facilities.h"

// 1a)
double acclY();

// 1b)
double velY(double initVelocityY, double time);

// 1c)
double posX(double initPositionX, double initVelocityX, double time);
double posY(double initPositionY, double initVelocityY, double time);

// 1d)
void printTime(double seconds);

// 1e)
double flightTime(double initVelocityY);

// 4a)
double getUserInputTheta();
double getUserInputInitVelocity();
double degToRad(double deg);
double getVelocityX(double theta, double initVelocity);
double getVelocityY(double theta, double initVelocity);
vector<double> getVelocityVector(double theta, double initVelocity);

// 4b)
double getDistanceTraveled(double velocityX, double velocityY);

// 4c)
double targetPractice(double distanceToTarget, double velocityX, double velocityY);