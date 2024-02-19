#include "writeToFile.h"

void writeToFile() {
    std::ofstream file;
    file.open("output.txt");
    std:string input;
    do {
        std::cout << "Enter a string to write to the file: ";
        std::cin >> input;
        file << input << std::endl;
    } while(input != "quit");
}

void addLinesNumbers() {
    std::ifstream file;
    file.open("output.txt");

    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }

    std::ofstream newFile;
    newFile.open("withLines.txt");
    std::string line;
    int lineNumber = 1;
    while(std::getline(file, line)) {
        newFile << lineNumber << ": " << line << std::endl;
        lineNumber++;
    }
}