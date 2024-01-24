#include "std_lib_facilities.h"
#include "cannonball.h"

void testDeviation(double compareOperand, double toOperand, 
                   double maxError, string name);

int main() {

    // a) test functions from cannonball.h
    cout << "acclY(): " << acclY() << endl;
    cout << "velY(): " << velY(20, 1) << endl;
    cout << "posX(): " << posX(0, 20, 1) << endl;
    cout << "posY(): " << posY(0, 20, 1) << endl;
    cout << "printTime(): ";
    printTime(234);
    cout << "flightTime(): " << flightTime(20) << endl;

    // c)
    double maxError = 0.01;
    testDeviation(velY(25, 2.5), 0.475, maxError, "velY at t=2.5");
    testDeviation(posX(0, 50, 2.5), 125.0, maxError, "posX at t=2.5");
    testDeviation(posY(0, 25, 2.5), 31.84, maxError, "posY at t=2.5");

    testDeviation(velY(25, 5.0), -24.05, maxError, "velY at t=5.0");
    testDeviation(posX(0, 50, 5.0), 250, maxError, "posX at t=5.0");
    testDeviation(posY(0, 25, 5.0), 2.375, maxError, "posY at t=5.0");

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