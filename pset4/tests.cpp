#include "tests.h"
#include "utilities.h"

void testCallByValue() {
    cout << "Tester incrementByValueNumTimes(0, 12, 12)" << endl;
    cout << incrementByValueNumTimes(0, 12, 12) << endl;
}

void testCallByValueRef() {
    int startValue = 0;
    int increment = 14;
    int numTimes = 14;
    incrementByValueNumTimesRef();
}