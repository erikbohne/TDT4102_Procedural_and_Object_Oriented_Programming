#include "utilities.h"


// Oppgave 1
int incrementByValueNumTimes(int startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
    return startValue;
}

void incrementByValueNumTimesRef(int& startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
}

void swapNumbers(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

// Oppgave 2
void printStudent(const Student& student) {
    cout << student.name << " (" << student.age << ")" << endl;
    cout << student.studyProgram << endl;
}

bool isInProgram(const Student& student, const string& program) {
    if (student.studyProgram == program) {
        return true;
    } else {
        return false;
    }
}

// Oppgave 3
string randomizeString(int n, char minS, char maxS) {

    int min = static_cast<int>(minS);
    int max = static_cast<int>(maxS);

    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(min, max);

    string result = "";
    for (int i = 0; i < n; i++) {
        result += static_cast<char>(distribution(generator));
    } 

    return result;
}

string readInputToString(int n, char minS, char maxS) {
    string result;
    cout << "Enter " << n << " characters between " << minS << " and " << maxS << ": ";

    while (result.length() < n) {
        char inputChar;
        cin >> inputChar;
        inputChar = toupper(inputChar);

        if (inputChar >= toupper(minS) && inputChar <= toupper(maxS)) {
            result += inputChar;
        } else {
            cout << "Invalid input. Please enter a character between " << minS << " and " << maxS << ": ";
        }
    }

    return result;
}

int countChar(const string& str, char c) {
    int count = 0;
    for (char i : str) {
        if (i == c) {
            ++count;
        }
    }
    return count;
}

// Oppgave 4
int checkCharactersAndPosition(const string& code, const string& guess) {

    int correct = 0;
    for (size_t i = 0; i < code.length(); ++i) {
        if (code[i] == guess[i]) { // Sjekk om bokstaven er korrekt og på riktig posisjon
            ++correct;
        }
    }

    return correct;
}

int checkCharacters(const string& code, const string& guess, const int& letters) {
    int totalCorrect = 0;

    const char minChar = 'A';
    const char maxChar = 'A' + letters - 1;

    for (char ch = minChar; ch <= maxChar; ++ch) {
        int countInCode = countChar(code, ch);
        int countInGuess = countChar(guess, ch);

        // Manuell sammenligning uten std::min
        if (countInCode < countInGuess) {
            totalCorrect += countInCode;
        } else {
            totalCorrect += countInGuess;
        }
    }

    return totalCorrect;
}
