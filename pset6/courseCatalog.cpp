#include "courseCatalog.h"

void CourseCatalog::addCourse(string code, string name) {
    courseMap[code] = name;
}

void CourseCatalog::removeCourse(string code) {
    courseMap.erase(code);
}

string CourseCatalog::getCourse(string code) {
    return courseMap.at(code);
}

void CourseCatalog::loadCatalog(string filename) {
    ifstream file(filename);
    if (!file) {
        error("Could not open file ", filename);
    }
    string line;
    getline(file, line); // Skip the first line
    while (getline(file, line)) {
        stringstream ss(line);
        string code, name;
        getline(ss, code, ',');
        getline(ss, name, ',');
        addCourse(code, name);
    }
    file.close();
}

void CourseCatalog::saveCatalog(string filename) {
    ofstream file(filename);
    if (!file) {
        error("Could not open file ", filename);
    }
    file << "Course code, Course name" << endl;
    for (pair<const string, const string> elem : courseMap) {
        file << elem.first << ", " << elem.second << endl;
    }
    file.close();
}

ostream& operator<<(ostream& os, const CourseCatalog& c) {
    for (pair<const string, const string> elem : c.courseMap) {
        os << elem.first << ", " << elem.second << endl;
    }
    return os;
}