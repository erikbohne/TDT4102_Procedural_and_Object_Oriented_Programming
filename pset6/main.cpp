#include "writeToFile.h"
#include "debugging.h"

int main() {
    // Task 1: File writing
    writeToFile();
    addLinesNumbers();

    // Task 2: Debugging
    cout << "Capitals:" << endl;
    for (pair<const string, const string> elem : capitalsMap) {
        cout << getCapital(elem.first) << endl;
    }
    return 0;
}
