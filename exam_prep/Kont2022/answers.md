# Del 1

> **1.** Hva må minimum presiseres ved funksjonsdeklarasjon?

1. **Parameterliste**
2. ~~Verdi~~
3. **Funksjonsnavn**
4. **Returtype**

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

1. **`Object(const Object &o) = default;`**
2. ~~`Object(const Object &o) {}`~~
3. ~~`Object(const Object &o) { number = o.number; theOtherObject = new Object(theOtherObject->number, theOtherObject->theOtherObject); }`~~
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
4. **Vi må ha funksjonsimplementasjonene utenfor klassedeklarasjonen.**

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

1. **Klassen har en default konstruktør.** (Ja, og den delegerer videre)
2. **Klassen kan konstrueres med to inputparametere.**
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
2. **Koden går i en uendelig løkke når man opretter den 7. fisken.**
3. ~~Vi kan ikke ha to gullfisker.~~
4. **Vi kan bare ha én fisk som heter Dory.**

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


# Del 2

> **1.** Forklar kort hvilke elementer som er nødvendig for å definere en variabel.

Vi trenger først og fremst typen, dette kan være alt fra innebygde typer som `int`, `double`, og `string` til egene klasser. Vi kan velge om vi ønsker å lage en peker (`int*`), da vil vi få plass på heap memory, eller vi kan kjøre bare `int` og den vil lagres på stack. I tillegg trenger man et variabelnavn. Ellers trenger man ikke definere noe verdi, da man kan gjøre dette senere. Man har også mulighet til å velge om en variabel skal være `const`, altså at den ikke kan endres etter definering, eller `constexpr`, altså at den settes ved kompilering og kan ikke endres i kjøretid.

> **2.** Forklar kort hvilke elementer som er nødvendig for å definere en funkjson.

Først trenger vi å velge hva funksjonen skal returnere, altså en returverdi. Om den ikke skal returnere noe bruker vi `void`. Ellers trenger vi et funksjonsnavn, som i utgangspunktet ikke trenger å være unikt, så lenge funksjonsparameterne er unik. Dette kalles function overloading. Vi trenger så parametere, her velger vi hva som skal sendes med funksjonen og vi kan for eksempel sende inn `int n`. Men om vi ikke ønsker å lage en kopi av det vi sender inn, kan vi bruke pass-by-refrence `int& n`. Om vi ønsker å forsikre oss om at vi ikke skal endre parameteren kan vi bruke `const` slik at `const int n` blir parameteren. Siden vi skal definere en funksjon trenger vi også å implementere selve funksjonen. Her er det viktig at funksjonen returner verdi av riktig type.

> **3.** Hva er hovedfordelen med lenket liste sammenlignet med tabller/vector?

Utfordringen med vector og tabeller er uforutsigbarhet i lengde, og derfor kan ikke vi være sikre på hvor mye plass vi skal allokere på heap memoriet. Dette betyr at om vi går tom for plass i det vi har allokert kan det være at vi kommer bort i noe som er allokert til noe annet. Med lenket liste kan vi gjøre slik at slutten på hvert liste eller element peker til et nytt sted i heap memory hvor vi kan fortsette på listen, slik vil vi alltid kunne fortsette listen der det er plass i heap. Ulempen med dette er at om du skal ha tak i det siste elementet i listen må du gjennom alle verdiene før du kommer fram. Og endringer i rekkefølger og slikt er litt vanskeligere ettersom du må ha logikk for endring av pekere.

> **4.** Forklar kort de største risikoene ved å bruke pekere.

Pekere har en adresse til et sted på heap memory, hvor det ligger en verdi. Dette betyr at om flere variabler har samme adresse vil endring av `a` påvrike `b`. Dette kan føre til feil ved at man endrer en variabel uten at man mener det. I tillegg er det større risiko for å "miste" verdier i minnet dersom man mister adressen, dette er ekstra kritisk i lenkede lister da tap av en peker vil gjøre at vi mister adressene til resten av listen. Du kan også få en "dangling pointer" dersom man frigjør minnet som denne pekeren peker til, men pekeren eksisterer fortsatt.

> **5.** Forklar kort hvorfor heltallstypene `char` og `int` har ulike intervaller som verdiene de kan inneholde må være innenfor.

Fordi de bruker et forskjellig antall bits/bytes til a holde sin verdi da de er laget for ˚
forskjellige formal. ˚ char beskrivere en enkelt ASCII karakter og bruker derfor bare en byte mens ´
en int (som oftest) er definert som et 4-bytes heltall.

> **6.** Forklar med egne ord hva funksjonen under gjør.

```c++
char function(char var) {
    if (tolower(var) > 'f' - 1) return var;
    return function(var + 1);
}
```

Denne funksjonen aksepterer en `char var` som input. Ved å bruke `tolower(var)`, sikrer den at sammenligningen skjer i lowercase, sjekker om karakteren er større enn `'e'`. Hvis dette stemmer, returneres var i sin opprinnelige form, enten det er uppercase eller lowercase. Hvis ikke, kaller funksjonen seg selv rekursivt med `var + 1`, og prøver med neste bokstav. Dersom var opprinnelig er mindre enn eller lik `'e'`, vil funksjonen alltid returnere `'f'`. Ellers returnerer den den innsendte karakteren.


> **7.** Forklar med egne ord hva funkjsonen `mysteryFunction` gjør.

```c++
class Node {
    int nodeNumber;
    int nodeValue;
    Node* nextNode;

public:
    Node(int nodeNumber = 0, int nodeValue = 0, Node* next = nullptr) :
        nodeNumber{nodeNumber}, nodeValue{nodeValue}, nextNode{next} {}

    Node* addNode() {
        Node* oldNextNode = nextNode;
        return nextNode = new Node(nodeNumber + 1, 0, oldNextNode);
    }

    int value() { return nodeValue; }

    ~Node() {
        if (nextNode) delete nextNode;
    }

    Node* mysteryFunction(Node& inputNode) {
        if (!nextNode) return this;
        else if (nextNode != &inputNode) return nextNode->mysteryFunction(inputNode);
        else {
            delete nextNode;
            nextNode = nullptr;
            return this;
        }
    }
};
```

Det første vi ser er at `mysteryFunction` er en metode i klassen `Node`. Den returnerer en peker til et objekt av klassen `Node` (`Node*`). Den eneste parameteren er en pass-by-reference til en `inputNode`. Funksjonen starter med å sjekke om det finnes en neste node. Hvis det ikke finnes en neste node (dvs. `nextNode` er `nullptr`), returnerer den pekeren til den gjeldende noden, som indikerer slutten på listen. Hvis det finnes en neste node, sjekker den om denne neste noden er identisk med `inputNode`. Hvis de ikke er like, fortsetter funksjonen rekursivt med `nextNode->mysteryFunction(inputNode)`, og leter videre nedover i listen. Hvis `nextNode` er lik `inputNode`, sletter funksjonen `nextNode`, setter pekeren til `nullptr` og returnerer pekeren til den gjeldende noden. 

Kort sagt vil denne funksjonen lete etter en node i den lenkede listen som matcher `inputNode`, og hvis den finner en slik node, slette den fra listen.


> **8.** a) Hva er problemet med koden? b) Hvilke to ulike måter kan man løse problemet på? c) Hvorfor gir koden likevel ut riktig resultat i noen tilfeller?

```c++
double position(double initialPosition, double initialVelocity, int time, int acceleration) {
    return initialPosition + initialVelocity * time + acceleration / 2 * time * time
}
```

**a)**
Problemet med koden er at vi utfører regne operasjoner med forskjellige datatyper, altså `int` og `double`. Dette fører til tap av presisisjon slik at vi mister desimalene i `acceleration / 2` som gir et upresist svar.

**b)** Vi kan løse det ved å tvinge input parameterene til alle å være `double` eller vi kan kjøre `static_cast<double>` på time og acceleration i regneoperasjonen.

**c)** Noen ganger vil koden gi ut rikitg resultat fordi acceleration er et partall, og da vil `2*n / 2 = n`, altså vi får et heltall uansett, og mister derfor ingen presisjon.


> **9.** Koden kompilerer ikke. På hvilke to ulike måter kan problemet i koden enkelt løses?

```c++
#include <iostream>
using namespace std;

int sumAndSquare(int a, int b) {
    return sum(a,b)*sum(a,b);
}

int sum(int a, int b){
    return a+b;
}

int main(){
    cout << sumAndSquare(4,1);
    return 0;
}
```

Funksjonen `int sum(int a, int b)` er ikke deklarert før bruk. Vi kan løse dette på to måter:

```c++
#include <iostream>
using namespace std;

int sum(int a, int b){
    return a+b;
}

int sumAndSquare(int a, int b) {
    return sum(a,b)*sum(a,b);
}

int main(){
    cout << sumAndSquare(4,1);
    return 0;
}
```

eller:

```c++
#include <iostream>
using namespace std;

int sum(int a, int b);

int sumAndSquare(int a, int b) {
    return sum(a,b)*sum(a,b);
}

int sum(int a, int b){
    return a+b;
}

int main(){
    cout << sumAndSquare(4,1);
    return 0;
}
```