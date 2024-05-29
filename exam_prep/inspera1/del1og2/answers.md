# Del 1

## Oppgave 1
> Hvilken verdi vil funksjonen test() returnere?
```c++
int test() {
    int a{0};
    if (a%2 == 0){
        int a = 1;
        a += 10;
    }
    else {
        int a = 20;
    }
    return a;
}
```

Programmet setter `a = 0`og så sjekker den `a%2 == 0`, siden a er 0 vil dette være sant og vi redefinerer definerer `int a = 1`. Siden dette er inne i et annet scope er dette en annen `a` enn den vi satte til `0` i starten. Derfor vil koden printe `0`.

## Oppgave 2
> Hva er verdien til `d`?
```c++
enum class Meny {Toast, Muffins = 17, Omelett, Iste=34, Kaffe}

int main() {
    int a = static_cast<int>(Meny::Toast);
    int b = static_cast<int>(Meny::Omelett);
    int c = a+b;
    c += static_cast<int>(Meny::Kaffe);
    int d = c + static_cast<int>(Meny::Iste);

    return 0;
}
```

Toast vil ha verdien 0, muffins vil ha verdien 17, omelett 18, iste 34 og kaffe 35. Derfor vil vi få `Toast + Omelett + Kaffe + Iste = 0 + 18 + 34 + 35 = 87`

## Oppgave 3
> Hvilke (en eller flere) av følgende utsagn er korrekt?
```c++
double doubleVal = 3.14159;
int convertedDouble = static_cast<int>(doubleVal);
```

1. **Konverteringen er eksplisistt**
2. ~~doubleVal er double så vi vil ikke kunne gjøre denne til en int~~
3. ~~Siden man bruker static_cast(doubleVal) så taper man ikke presisjon~~
4. **Konverteringen medfører tap av presisjon**

## Oppgave 4
> Hva blir utskriften av koden nedenfor?
```c++
int n = 4;

std::cout << ++n << n << n++ <<n << std::endl;
```

```bash
5556
```

# Del 2

> **1.** Forklar kort hva forskjellen på `constexpr` og `const` er.

Forskjellen på `constexpr` og `const` er at `constexpr` evalueres når koden kompileres som betyr at den er fast for alle kjøringer. I motsetning er `const` ikke evaluert i kompilering som betyr at den kan ha forskjellig verdi for forskjellige kjøringer. Det som er felles er at det er verdier som ikke kan endres etter de er definert.

> **2.** Tolk følgende feilmelding. Hva er problemet og hva er mulige løsninger?

```zsh
..main/cpp::33:2: error: use of undeclared identifier 'testCallByValue'
```

Dette er en kompileringsfeil fordi her er det brukt en funksjon som ikke er deklarert før. En slik feil løses ved å sørge for at funksjonen er deklarert før den blir nevnt, og selve definisjonen kan være elsewhere.

> **3a.** Forklar kort korskjellen på disse to utskriftene og hvilken en burde bruke og hvorfor.
```c++
std::vector<int> myVector {1, 4, 70, 5};

std::cout << myVector[4] << std::endl;
std::cout << myVector.at(4) << std::endl;
```

Her er det brukt `[]`-operatoren og metoden `.at()`. Begge vil fungere likt i dette tilfelle, men generelt er det et tryggere alternativ å bruke `.at()` fordi denne tar hensyn til om den indeksen du spør om faktisk er en del av listen. Dette gjør ikke `[]` som betyr at vi kan få feil verdi uten varsel om vi når en verdi utenfor vektorens lengde. I verste fall kan man endre på noe som ikke skal endres og alt krasjer.

> **3b.** Forklar kort forskjellen på en vector og en array, og i hvilke tilfeller man burde bruke dem.

En `vector` og `array` er ikke så ulik, men `array` er en liste med en endelig lengde som ikke er mulig å endre på, mens vector er en liste med muligheter for å endre lengde, og legge til nye elementer. I scenarioer der du ikke vet hvor lang listen skal være, som f eks en handleliste, er det best å bruke `vector`, mens i tilfeller der du har en bestemt lengde som ikke endrer seg, f eks lagene i Eliteserien, er `array` det beste alternativet.

> **4.** Hva er koden et eksempel på? Hvorfor fungerer denne? Og hvordan hadde det vært om vi hadde `double increaseVal(int a)` i stedet?

```c++
int increaseVal(int a) {
    a++;
    return a;
}

double increaseVal(double a) {
    a++;
    return a;
}
```

Dette er et eksempel på **function overloading** som betyr at vi har flere forskjellige funksjoner med samme navn. Forskjellen er parameterne i funksjonen er av andre datatyper og eller flere, eller til og med forskjellig rekkefølge. Men om vi hadde endret koden til `double increaseVal(int a)` hadde plutselig funksjonene vært den samme, og vi hadde fått feilmelding. Det er altså parameterene som lar oss overloade en funksjon, ikke retur-typen til funksjonen.

> **5a.** Burde konstruktøren som regel settes til å være `private` eller `public`?

Konstruktøren brukes utenfor klassen og må derfor være `public` slik at vi faktisk kan bruke den. Hadde den vært i `private` hadde vi fått feilmelding når vi prøver å lage klassen.

> **5a.** Hva er galt med denne konstruktøren?
```c++
class Student {
    private:
        string name;
        int studnr;
    public:
        Student(string name, int number);
}

Student::Student(string name, int number) {
    name = name;
    studnr = number;
}
```

Feilen er at `name = name;` referer til samme variabel from parameteren, det samme gjør `studnr`. En enkel måte å rett opp i dette er `this->name = name;` og `this->studnr = number;`, men det mest effektive er `Student(string name, int number) : name(name), studnr(number) {}`.

