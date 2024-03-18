#include "std_lib_facilities.h"
#include "Person.h"
#include "MeetingWindow.h"
#include <iostream>

int main() {
    Person erik{"erik", "erik@bohne.com", 2};
    std::cout << erik;

    // Task 4
    MeetingWindow w{0, 0, 500, 500, "test"};
    w.wait_for_close();

    return 0;
}
