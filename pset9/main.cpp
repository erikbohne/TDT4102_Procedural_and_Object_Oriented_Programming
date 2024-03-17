#include "std_lib_facilities.h"
#include "Person.h"
#include <iostream>

int main() {
    Person erik{"erik", "erik@bohne.com", 2};
    std::cout << erik;
    return 0;
}
