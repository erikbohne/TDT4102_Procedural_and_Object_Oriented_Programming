#pragma once
#include "std_lib_facilities.h"


// Oppgave 1
int incrementByValueNumTimes(int startValue, int increment, int numTimes);
void incrementByValueNumTimesRef(int& startValue, int increment, int numTimes);
void swapNumbers(int& a, int& b);

// Oppgave 2
struct Student{
    string name;
    string studyProgram;
    int age;
};
void printStudent(const Student& student);
bool isInProgram(const Student& student, const string& program);

// Oppgave 3
string randomizeString(int n, char minS, char maxS);
string readInputToString(int n, char minS, char maxS);
int countChar(const string& str, char c);