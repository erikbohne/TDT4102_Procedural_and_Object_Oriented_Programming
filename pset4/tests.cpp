#include "tests.h"
#include "utilities.h"

// Oppgave 1
void testCallByValue() {
    int v0 = 5;
    int increment = 2;
    int iterations = 10;
    int result = incrementByValueNumTimes(v0, increment, iterations);
    cout << "v0: " << v0
    << " increment: " << increment
    << " iterations: " << iterations
    << " result: " << result << endl;
}

void testCallByReference() {
    int v0 = 5;
    int increment = 2;
    int iterations = 10;
    cout << "v0 before: " << v0 << endl;
    incrementByValueNumTimesRef(v0, increment, iterations);
    cout << "increment: " << increment << endl;
    cout << "iterations: " << iterations << endl;
    cout << "v0 after: " << v0 << endl;
}

void testSwapNumbers() {
    int a = 69;
    int b = 420;
    cout << "Before: " << endl << "   a = " << a << " and b = " << b << endl;
    swapNumbers(a, b);
    cout << "After: " << endl << "   a = " << a << " and b = " << b << endl;

}

// Oppgave 2
void testStudentStruct() {
    Student erik {"Erik Nymo Bohne", "Kybernetikk og robotikk", 21};
    printStudent(erik);
    cout << "Studerer Indøk? " << isInProgram(erik, "Indøk") << endl;
    cout << "Studerer Kybernetikk og robotikk? " << isInProgram(erik, "Kybernetikk og robotikk") << endl;
}

// Oppgave 3
void testString() {
    string grades = randomizeString(150, 'A', 'F');
    vector<int> gradeCount(6, 0); // A-F
    for (char grade : grades) {
        if (grade >= 'A' && grade <= 'F') {
            gradeCount[grade - 'A']++;
        }
    }

    int total = 0, count = 0;
    for (size_t i = 0; i < gradeCount.size(); ++i) {
        total += (6 - i) * gradeCount[i]; // A=6, B=5, ..., F=1
        count += gradeCount[i];
    }

    double average = count > 0 ? static_cast<double>(total) / count : 0;
    cout << "Average grade: " << average << endl;
}

void testRandomizeString() {
    char min = 'A';
    char max = 'G';
    int n = 10;
    cout << "defined, lets try to random shit" << endl;
    string result = randomizeString(n, min, max);
    cout << result << endl;
}

void testReadInputToString() {
    string streng = readInputToString(10, 'A', 'F');
    cout << "Resultat: " << streng << endl;
}

void testCountChar() {
    string grades = randomizeString(1000, 'A', 'F');
    cout << "A: " << countChar(grades, 'A') << endl;
    cout << "B: " << countChar(grades, 'B') << endl;
    cout << "C: " << countChar(grades, 'C') << endl;
    cout << "D: " << countChar(grades, 'D') << endl;
    cout << "E: " << countChar(grades, 'E') << endl;
    cout << "F: " << countChar(grades, 'F') << endl;
}