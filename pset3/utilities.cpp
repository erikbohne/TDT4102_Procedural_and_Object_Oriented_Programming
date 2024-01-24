#include "utilities.h"

int randomWithLimits(int lowerLimit, int upperLimit) {

    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(lowerLimit, upperLimit);

    int number = distribution(generator);
    return number;
}
