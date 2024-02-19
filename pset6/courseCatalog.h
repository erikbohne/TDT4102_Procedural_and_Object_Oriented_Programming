#pragma once
#include "std_lib_facilities.h"

class CourseCatalog {
private:
    map<string, string> courseMap;
public:
    void addCourse(string code, string name);
    void removeCourse(string code);
    string getCourse(string code);
    void loadCatalog(string filename);
    void saveCatalog(string filename);

    friend ostream& operator<<(ostream& os, const CourseCatalog& c);
};