#include "std_lib_facilities.h"

int main() {

    vector<double> temperatures = {-10.3, 3.5, 5.5};
    temperatures.push_back(7.7);

    for(int i = 0; i < temperatures.size(); i++) {
        cout << temperatures.at(i) << endl;
    }

    return 0;
}