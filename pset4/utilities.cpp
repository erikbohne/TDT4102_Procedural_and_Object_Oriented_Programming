#include "utilities.h"

int incrementByValueNumTimes(int startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
    return startValue;
}

void incrementByValueNumTimes(int& startValue, int& increment, int& numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
}