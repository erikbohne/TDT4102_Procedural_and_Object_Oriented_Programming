# Del 1

> **1.** Hva må minimum presiseres ved funksjonsdeklarasjon?

1. **Parameterlist**
2. ~~Verdi~~
3. **Funksjonsnavn**
4. ~~Returtype~~

> **2.** Hvilke (en eller flere) av følgende utsagn er korrekt?

1. **Medlemsfunksjonen `rend()` til `std::list` returnerer en iterator.**
2. ~~Medlemsfunksjonen `rbegin()` og `end()` til `std::list` returnerer samme element.~~
3. ~~Medlemsfunksjonen `rbegin()` til en STL-beholder peker til det første elementet i beholderen.~~
4. **Medlemsfunksjonene `begin()` og `rend()` til `std::list` returnerer ikke samme element.**


> **3.** Hvilke (en eller flere) av alternativene om operatoroverlasting er korrekt/viktig i følge læreboken?
1. **Bruk returtype og parametre som samsvarer med operatortypen og (resten av) språket.**
2. ~~Deklarer operatoroverlastningen som en muterende medlemsfunksjon.~~
3. **Ikke overlast en operator med mindre nytten er stor.**
4. ~~En overlastet operator må ha minst to brukerdefinerte typer som operander.~~

> **4.** Hvilke (en eller flere) av kopikonstruktørene under gjør en grunn kopi av objektet Object?

```c++
class Object {
    int number;
    Object * theOtherObject;

public:
    Object(int number, Object * theOtherObject = nullptr) : number{number}, theOtherObject{theOtherObject} {}
};
```

1. ~~`Object(const Object &o) = default;`~~
2. ~~`Object(const Object &o) {}`~~
3. **`Object(const Object &o) { number = o.number; theOtherObject = new Object(theOtherObject->number, theOtherObject->theOtherObject); }`**
4. ~~`Object(const Object &o) = delete;`~~


> **5.** Hvilke (en eller flere) av følgende utsagn er i følge læreboka vår korrekt om klassen `Syllabus` skal
gjøres om til en templateklasse ved å bytte ut `string` content med `Template<T>` content?

```c++
class Syllabus {
    string name;
    string content;

    public:
        Syllabus(string name, string content) : name{name}, content{content} {}

        void changeConent(string newContent) {
            content = newContent;
        }

        string getContent() {
            return content;
        }
}
```

1. **Vi må endre alle medlemsfunksjonene til klassen.**
2. ~~Vi må skrive template over hver funksjonsdeklarasjon inne i klassen.~~
3. ~~Vi bør ha alle funksjonsdefinisjonene i samme fil som klassedeklarasjonen.~~
4. ~~Vi må ha funksjonsimplementasjonene utenfor klassedeklarasjonen.~~

> **6.** Hvilke (en eller flere) av følgende utsagn er korrekt?

```c++
struct Flower {
    int numberOfPetals;
    string color;
    int weight;
    Flower(int numberOfPetals, string color, int weight = 3) : numberOfPetals{numberOfPetals}, color{color}, weight{weight} {}
    Flower() : Flower{6, "yellow", 2} {}
};
```

1. ~~Klassen har en default konstruktør.~~
3. ~~Medlemsfunksjoner må lages for å kunne endre på medlemsvariablene.~~ (Nei, Flower er en struct og den er i utgangspunktet public.)
4. **Klassen har en delegerende konstruktør.** (Ja, og den setter en flower med parametere 6, yellow og 2)

> **7** Hvilke (en eller flere) av følgende par av klassedeklarasjoner gjør det mulig for brukeren av et Child-object å endre variabelen number direkte?

1. Ja
```c++
class Parent {
    public:
        int number = 5;
};

class Child : public Parent {
};
```

2. Nei
```c++
class Parent {
    protected:
        int number = 5;
};

class Child : public Parent {
};
```

3. Nei
```c++
class Parent {
    int number = 5;
};

class Child : public Parent {
};
```

4. Ja
```c++
struct Parent {
    int number = 5;
};

class Child : public Parent {
};
```

> **8.** Hvilket (en eller flere) av følgende utsagn er korrekt?

```c++
#include <iostream>
#include <vector>
using namespace std;

enum class FishName{Nemo, Dory, Marlin, Wanda, Cleo, Larry, count};
enum class FishType{Anemonefish, Angelfish, Goldfish, Salmon, Sunfish, Surgeonfish, count};

class Fish {
    static inline vector<Fish*> otherFish;
    FishName name;
    FishType type;

public:
    bool operator==(const Fish& rhs) {
        if(name == rhs.name) return true;
        return false;
    }

    Fish() : name(FishName::Cleo), type(FishType::Goldfish) {
        bool fishFlag = true;
        while(fishFlag) {
            fishFlag = false;
            for(auto fish : otherFish) {
                while(*this == *fish) {
                    type = static_cast<FishType>(rand() % static_cast<int>(FishType::count));
                    name = static_cast<FishName>(rand() % static_cast<int>(FishName::count));
                    fishFlag = true;
                }
            }
        }
        otherFish.push_back(this);
    }
};
```

1. **Vi må uansett ha en fisk som heter Cleo.**
2. ~~Koden går i en uendelig løkke når man opretter den 7. fisken.~~
3. ~~Vi kan ikke ha to gullfisker.~~
4. ~~Vi kan bare ha én fisk som heter Dory.~~

> **9.** Hvilke (en eller flere) av de følgende konseptene må vi implementere i klassen for at koden skal
kjøre?

```c++
#include <iostream>
using namespace std;

class Animal {
    string name;
public:
    Animal(string name) : name{name} {}
};

template<typename T>
void function(T one, T two) {
    if(one == two) return;
    else cout << (one > two);
}

int main() {
    Animal dog{};
    Animal cat{};
    function(dog, cat);
    return 0;
}
```

1. ~~`<< operator`~~ (Bool printes som int)
2. **`== operator`** (Ja, vi skal sjekke to uvisste klasser)
3. **`> operator`** (Ja, av samme grunn som over)
4. ~~Move-konstruktør~~
5. **Default konstruktør** (Ja, for dog og cat må initialiseres uten paramatere)
6. ~~Kopikonstruktør~~ (Nei, for det skjer ingen kopiering)

> **10.** Du har fått i oppgave å programmere sjakk. Kort fortalt består sjakk av 16 svarte og 16 hvite brikker på et 8x8-rutenett. Det finnes 6 ulike typer sjakkbrikker i hver farge, der alle typene ser forskjellige ut og kan bevege seg på forskjellige måter.

> **10.a** Du ønsker å lage en klasse ChessPiece for å representere sjakkbrikkene. Hvilke (en eller flere) av alternativene under kan man gjøre for å gjøre klassen abstrakt?

1. **Lage en "helt virtuell" funksjon.**
2. **Lage alle konstruktører abstrakte.**
3. ~~Kun bruke virtuelle funksjoner.~~
4. ~~Slette kopikonstruktøren og tilordningsoperatoren.~~

> **10.b** Hvilken av disse (en eller flere) funksjonalitetene er det naturlig å ha med i den abstrakte ChessPiece-klassen?

1. ~~Logikken for hvordan brikken skal bevege seg.~~
2. ~~Grafikken til brikkene.~~
3. **Fargen på brikken.**
4. **Posisjonen til brikken.**


