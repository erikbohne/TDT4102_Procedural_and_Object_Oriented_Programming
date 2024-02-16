#include "Card.h"
#include "Blackjack.h"

int main(){

    cout << "TASK 1:" << endl;
    Rank r = Rank::KING;
    Suit s = Suit::HEARTS;
    string rank = rankToString(r);
    string suit = suitToString(s);
    cout << "Rank: " << rank << " Suit: " << suit << endl << endl;

    cout << "TASK 2:" << endl;
    Card c{Suit::SPADES, Rank::ACE};
    cout << c.toString() << '\n' << endl;

    cout << "TASK 3:" << endl;
    CardDeck deck;
    deck.shuffle();
    cout << "Shuffled deck:" << endl;
    deck.print();
    Card drawnCard = deck.drawCard();
    cout << "\nDrawn card: " << drawnCard.toString() << endl;
    cout << "\nDeck after drawing a card:" << endl;
    deck.print();

    cout << "TASK 4:" << endl;
    Blackjack game;
    game.playGame();

    return 0;
}