#include "animal.h"
#include "Emoji.h"

int main() {

    // Teste oppgave 1
    vector<unique_ptr<Animal>> animals;
    animals.emplace_back(make_unique<Cat>("Pus", 3));
    animals.emplace_back(make_unique<Dog>("Fido", 5));

    for (auto& animal : animals) {
        cout << animal->toString() << endl;
    }

    // Teste oppgave 2
    TDT4102::Point p;
    p.x = 250;
    p.y = 250;
    AnimationWindow win(500, 500);
    vector<unique_ptr<Emoji>> emojis;
    emojis.emplace_back(make_unique<Face>(p, 50));

    return 0;
}
