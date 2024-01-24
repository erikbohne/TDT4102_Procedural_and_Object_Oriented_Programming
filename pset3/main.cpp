#include "std_lib_facilities.h"
#include "cannonball.h"
#include "utilities.h"

void testDeviation(double compareOperand, double toOperand, 
                   double maxError, string name);

int main() {

    //double maxError = 0.01;

    // // 1a) test functions from cannonball.h
    // cout << "acclY(): " << acclY() << endl;
    // cout << "velY(): " << velY(20, 1) << endl;
    // cout << "posX(): " << posX(0, 20, 1) << endl;
    // cout << "posY(): " << posY(0, 20, 1) << endl;
    // cout << "printTime(): ";
    // printTime(234);
    // cout << "flightTime(): " << flightTime(20) << endl;

    // // 1c)
    // testDeviation(velY(25, 2.5), 0.475, maxError, "velY at t=2.5");
    // testDeviation(posX(0, 50, 2.5), 125.0, maxError, "posX at t=2.5");
    // testDeviation(posY(0, 25, 2.5), 31.84, maxError, "posY at t=2.5");

    // testDeviation(velY(25, 5.0), -24.05, maxError, "velY at t=5.0");
    // testDeviation(posX(0, 50, 5.0), 250, maxError, "posX at t=5.0");
    // testDeviation(posY(0, 25, 5.0), 2.375, maxError, "posY at t=5.0");

    // // 4d)
    // testDeviation(getVelocityX(27.5, 15.64), 13.8728, maxError, "getVelocityX");
    // testDeviation(getVelocityY(27.5, 15.64), 7.22175, maxError, "getVelocityY");

    // vector<double> velocityVector = getVelocityVector(27.5, 15.64);
    // testDeviation(velocityVector[0], 13.8728, maxError, "getVelocityVector X");
    // testDeviation(velocityVector[1], 7.22175, maxError, "getVelocityVector Y");

    // double velocityX = getVelocityX(27.5, 15.64);
    // double velocityY = getVelocityY(27.5, 15.64);
    // testDeviation(getDistanceTraveled(velocityX, velocityY), 20.4253, maxError, "getDistanceTraveled");

    // double distanceToTarget = 20.4253; // Eksempelavstand
    // testDeviation(targetPractice(distanceToTarget, velocityX, velocityY), 0.0, maxError, "targetPractice");

    // // 5b) test pseudorandom number generator
    // for(int i = 0; i < 10; i++) {
    //     cout << randomWithLimits(100, 1000) << endl;
    // }
    
    // 5c)
    playTargetPractice();

    return 0;
}


// b)
void testDeviation(double compareOperand, double toOperand, double maxError, string name) {
    if (abs(compareOperand - toOperand) <= maxError) {
        cout << name << ": Success" << endl;
    } else {
        cout << name << ": Failure  -> got value " << compareOperand << " vs expected " << toOperand <<  endl;

    }
}