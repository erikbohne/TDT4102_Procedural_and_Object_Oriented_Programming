#include "mastermind.h"
#include "utilities.h"

int playMastermind() {
    cout << "Velkommen til Mastermind!" << endl << endl;

    constexpr int size = 4;  // Antall tegn i koden
    constexpr int letters = 6;  // Antall forskjellige bokstaver
    constexpr int maxAttempts = 10;  // Maks antall forsøk

    string code = randomizeString(size, 'A', 'A' + letters - 1);
    string guess;
    int correctCharsAndPos;
    int correctChars;
    int attempts = 0;

    do {
        cout << "Forsøk " << attempts + 1 << " av " << maxAttempts << endl;
        guess = readInputToString(size, 'A', 'A' + letters - 1);
        correctCharsAndPos = checkCharactersAndPosition(code, guess);
        correctChars = checkCharacters(code, guess, letters);

        cout << "Korrekte bokstaver uavhengig av posisjon: " << correctChars << endl;
        cout << "Korrekte bokstaver på riktig posisjon: " << correctCharsAndPos << endl << endl;

        attempts++;
    } while (correctCharsAndPos < size && attempts < maxAttempts);

    if (correctCharsAndPos == size) {
        cout << "Gratulerer, du gjettet riktig kode" << endl;
    } else {
        cout << "Beklager, du klarte ikke å gjette koden. Riktig kode var: " << code << endl;
    }

    // Tilby valg om å spille igjen eller avslutte
    char playAgain;
    cout << "Vil du spille igjen? (Y/N): ";
    cin >> playAgain;

    if (toupper(playAgain) == 'Y') {
        return playMastermind();
    }

    return 0;
}
