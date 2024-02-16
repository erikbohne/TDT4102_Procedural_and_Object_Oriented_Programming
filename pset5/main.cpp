#include "Card.h"

int main(){
    Rank r = Rank::KING;
    Suit s = Suit::HEARTS;
    string rank = rankToString(r);
    string suit = suitToString(s);
    cout << "Rank: " << rank << " Suit: " << suit << endl;
    return 0;
}