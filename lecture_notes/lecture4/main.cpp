#include "std_lib_facilities.h"

int main() {

    // vector
    vector<string> klassement = {
        "Max Verstappen",
        "Lewis Hamilton",
        "George Russel"
    };

    vector<double> lapTimes(10, 10);
    lapTimes.push_back(110.2378);

    cout << "The winner is: " << klassement.at(0) << endl;

    // array
    array<string, 5> pitStopCrew = {
        "John Doe",
        "Jonas Jacobsen",
        "Erik Bohne",
        "Eddie McFreddie",
        "Ingrid Hygen"
    };

    // for (int i = 0; i < pitStopCrew.size(); i++) {
    //     cout << "The " << i + 1 << "th crew member: " << pitStopCrew.at(i) << endl;
    // }

    // Chess board
    array<array<string, 8>, 8> chessBoard;
    vector<array<array<string, 8>, 8>> boards;

    chessBoard.at(5).at(3) = "King";

    // Random numbers
    default_random_engine engine;
    uniform_real_distribution distribution(0.0, 1.0);
    cout << distribution(engine) << endl;

    uniform_int_distribution tickets(0, 100000);
    int winningTicket = tickets(engine);

    // int userTicket;
    // cin >> userTicket;

    // if(userTicket == winningTicket) {
    //     cout << "You win lets go!!!!!" << endl;
    // } else {
    //     cout << "Of course you didn't win" << endl;
    // }

    int count = 0;
    bool winning = false;
    do {
        int currentTicket = tickets(engine);
        if(currentTicket == winningTicket) {
            winning = true;
        } else {
            count++;
        }
    }
    while (winning == false);

    cout << "It took " << count << " tries to win the lottery" << endl;

    return 0;
}
