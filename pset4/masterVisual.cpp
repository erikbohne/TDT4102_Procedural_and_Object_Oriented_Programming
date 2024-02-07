#include "masterVisual.h"
#include "utilities.h"

void addGuess(MastermindWindow &mwin, const string code, const char startLetter)
{
	mwin.guesses.push_back(Guess{code, startLetter});
}

void addFeedback(MastermindWindow &mwin, const int correctPosition, const int correctCharacter)
{
	mwin.feedbacks.push_back(Feedback{correctPosition, correctCharacter});
}

void MastermindWindow::drawCodeHider()
{
	if (code_hidden) {
		draw_rectangle(Point{padX, 3 * padY}, winW - size * padX, padY, Color::black);
	}
}

MastermindWindow::MastermindWindow(int x, int y, int w, int h, int size, const string &title) 
: AnimationWindow(x, y, w, h, title),
guessBtn{{upperLeftCornerBtn.x, upperLeftCornerBtn.y}, btnW, btnH, "Add"},
guess{{upperLeftCornerInBox.x, upperLeftCornerInBox.y}, inBoxW, inBoxH, ""},
size(size)
{
	add(guess);
	add(guessBtn);
	guessBtn.setCallback(std::bind(&MastermindWindow::cb_guess, this));
};

void MastermindWindow::drawGuessesAndFeedbacks()
{
	std::map<int, Color> colorConverter{
		{1, Color::red},
		{2, Color::green},
		{3, Color::yellow},
		{4, Color::blue},
		{5, Color::blue_violet},
		{6, Color::dark_cyan}};

	for (int guessIndex = 0; guessIndex < static_cast<int>(guesses.size()); guessIndex++)
	{
		Guess currentGuess = guesses[guessIndex];
		for (int i = 0; i < size; i++)
		{
			// Beregn xPos og yPos for hvert rektangel
            int xPos = padX + i * (padX + padX / 4); // Legg til litt mellomrom mellom hvert rektangel
			int yPos = 3 * padY + guessIndex * (padY + padY / 4); // Start litt ned fra toppen og legg til mellomrom mellom hver rad

			int colorIndex = currentGuess.code[i] - currentGuess.startLetter + 1;
            Color color = colorConverter.at(colorIndex);

			// Tegn rektangelet med den beregnede fargen og posisjonen
            draw_rectangle({xPos, yPos}, padX, padY, color, Color::black);
		}
	}

	for (int feedbackIndex = 0; feedbackIndex < static_cast<int>(feedbacks.size()); feedbackIndex++) {
        Feedback feedback = feedbacks[feedbackIndex];
        
        // Startposisjon for tilbakemeldingssirklene til høyre for gjettene
        int yPos = 3 * padY + feedbackIndex * (padY + padY / 4) + padY / 2; // Midtpunktet i raden for gjettet
        int xPos = winW - 5 * radCircle * 2;  // Posisjon for den første sirkelen fra høyre side
        
        // Tegn sorte sirkler for korrekt posisjon
        for (int i = 0; i < feedback.correctPosition; i++) {
            draw_circle({xPos + i * 2 * radCircle, yPos}, radCircle, Color::black);
        }

		// Fyll resten med grå sirkler for å vise for korrekte farger men feil plass
        for (int i = feedback.correctPosition; i < feedback.correctCharacter; i++) {
            draw_circle({xPos + i * 2 * radCircle, yPos}, radCircle, Color::gray);
        }
        
		// Tegn hvite sirkler for korrekt farge
        for (int i = feedback.correctCharacter; i < size; i++) {
            if (i >= feedback.correctCharacter) {
                draw_circle({xPos + i * 2 * radCircle, yPos}, radCircle, Color::black);
                draw_circle({xPos + i * 2 * radCircle, yPos}, radCircle - radCircle/4, Color::white);
            }
        }
        
        // Fyll resten med grå sirkler for å vise antall ubrukte gjetninger
        for (int i = feedback.correctCharacter; i < 4; i++) {
            draw_circle({xPos + i * 2 * radCircle, yPos}, radCircle, Color::light_gray);
        }
    }
}

string MastermindWindow::wait_for_guess()
{

	while (!button_pressed && !should_close())
	{
		drawGuessesAndFeedbacks();
		// Burde tegnes sist siden den skal ligge på toppen
		drawCodeHider();

		next_frame();
	}
	button_pressed = false;

	string newGuess = guess.getText();
	guess.setText("");

	return newGuess;
}

string MastermindWindow::getInput(unsigned int n, char lower, char upper)
{
	bool validInput = false;
	string guess;
	while (!validInput && !should_close())
	{
		guess.clear();
		string input = wait_for_guess();
		if (input.size() == n)
		{
			for (unsigned int i = 0; i < n; i++)
			{
				char ch = input.at(i);
				if (isalpha(ch) && toupper(ch) <= upper && lower <= toupper(ch))
				{
					guess += toupper(ch);
				}
				else
					break;
			}
		}
		if (guess.size() == n)
		{
			validInput = true;
		}
		else
		{
			cout << "Invalid input guess again" << endl;
		}
	}
	return guess;
}

void MastermindWindow::setCodeHidden(bool hidden) {
	code_hidden = hidden;
}

void playMastermindVisual() {
	cout << "Velkommen til Mastermind!" << endl << endl;

    // Definer konstanter for spillet
    constexpr int size = 4;  // Antall tegn i koden
    constexpr int letters = 6;  // Antall forskjellige bokstaver
    constexpr int maxAttempts = 10;  // Maks antall forsøk

	// Opprett grafikkvinduet
    MastermindWindow mwin{900, 20, winW, winH, size, "Mastermind"};
	mwin.setCodeHidden(true);

    // Generer den hemmelige koden
    string code = randomizeString(size, 'A', 'A' + letters - 1);
    int attempts = 0;

	addGuess(mwin, code, 'A');

	// Spill-løkke
    while (attempts < maxAttempts) {
        // Bruk getInput() for å få spillerens gjetning
        string guess = mwin.getInput(size, 'A', 'A' + letters - 1);

        // Legg til gjetningen i grafikkvinduet
        addGuess(mwin, guess, 'A');  // 'A' er startbokstaven

        // Beregn og vis tilbakemelding
        int correctCharsAndPos = checkCharactersAndPosition(code, guess);
        int correctChars = checkCharacters(code, guess, letters);
        addFeedback(mwin, correctCharsAndPos, correctChars);

        // Sjekk for seier
        if (correctCharsAndPos == size) {
            break;
        }

        attempts++;
    }

    mwin.drawGuessesAndFeedbacks();
	mwin.setCodeHidden(false);
	mwin.wait_for_close();
}
