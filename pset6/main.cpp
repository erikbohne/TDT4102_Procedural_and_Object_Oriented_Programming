#include "writeToFile.h"
#include "debugging.h"
#include "courseCatalog.h"

int main() {
    // Task 1: File writing
    writeToFile();
    addLinesNumbers();

    // Task 2: Debugging
    cout << endl << "Capitals:" << endl;
    for (pair<const string, const string> elem : capitalsMap) {
        cout << getCapital(elem.first) << endl;
    }

    // Task 3: Course catalog
    CourseCatalog catalog;
    catalog.addCourse("TDT4102", "Prosedyre- og objektorientert programmering");
    catalog.addCourse("TMA4106", "Matematikk 2");
    catalog.addCourse("TMA4245", "Statistikk");
    catalog.addCourse("TTK4101", "Instrumentering og måleteknikk");
    cout << endl << "Catalog 1: " << endl << catalog;

    catalog.addCourse("TDT4102", "C++");
    cout << endl << "Edited catalog: " << endl << catalog;

    catalog.saveCatalog("courseCatalog.csv");
    
    CourseCatalog catalog2;
    catalog2.loadCatalog("courseCatalog.csv");
    cout << endl << "Catalog 2: " << endl << catalog2;

    return 0;
}
