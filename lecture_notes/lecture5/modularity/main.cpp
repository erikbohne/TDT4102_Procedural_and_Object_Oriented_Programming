#include "std_lib_facilities.h"
#include "print.h"

// Ny fil:
// 1. Lag en .cpp fil
// 2. Lag en .h fil med samme navn som .cpp filen
// 3. Legg til #pragma once på linje 1 i .h fila
// 4. Legg til #include "filename.h" i .cpp fila

// Legg til ny funksjon
// 1. Definer funkjsonen i .cpp filen
// 2. #include .h fila i .cpp filen

int main() {
    string message = "hello, world!";
    print(message);
    return 0;
}