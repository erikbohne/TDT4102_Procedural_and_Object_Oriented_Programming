# Del 1

> **1.** Hvilke (en eller flere) funksjonsdeklarasjoner er ekvivalente?
```c++
void f(int* a);
```

1. **void f(int a[]);**
2. ~~void f(int a[2048]);~~
3. ~~void f(std::array<int, 2048> a);~~
4. ~~void f(int** a);~~

> **2.** Hvilke (en eller flere) av parameteroverføringene krever at en funksjon må ha en returverdi hvis man skal se en endring utenfor funksjonsskopet?

1. ~~pass-by-value~~
2. **pass-by-reference**
3. ~~pass-by-const-reference~~
4. **pass-by-pointer**

> **3.** Hvilke (en eller flere) av følgende utsagn er korrekt?

1. ~~En konstant (const) variabel kan endres.~~
2. **En konstant (const) referansevariabel kun kan leses.**
3. ~~Man kan endre hva en referansevariabel refererer til så mange ganger man ønsker.~~
4. **Funksjonsparametere som er konstante referansevariabler signaliserer at funksjonen ikke kommer til å endre parameterverdiene.**

> **4.** Velg riktig alternativ fra nedtrekksmenyen for hvert utsagn.
   - prices er i (**klassens skop**/globalt skop/lokalt skop/skopet til for-løkken).
   - sum er i (klassens skop/globalt skop/**lokalt skop**/skopet til for-løkken).

> **5.** Hvilke (en eller flere) av følgende utsagn er korrekt om typekonvertering?

```c++
float floatValue = 3.5f;
int intValue = floatValue;
```

1. ~~Konverteringen er eksplisitt.~~
2. **Konverteringen medfører tap av presisjon.**
3. ~~Man kan bruke static_cast<int>(floatValue) eller int(floatValue) for å unngå tap av presisjon i konverteringen.~~
4. **Man vil tape presisjon selv om man bruker static_cast<int>(floatValue) eller int(floatValue), men man burde likevel bruke dem.**

> **6.** Hvilke (en eller flere) av følgende utsagn om templates er korrekt?

1. **Templates muliggjør generisk programmering i C++.**
2. ~~Templates blir instansiert ved kjøretid.~~
3. ~~Polymorfisme er ikke et konsept i objektorientert programmering.~~
4. **Templates blir instansiert ved kompileringstid.**

> **7.** Hvilke (en eller flere) av følgende utsagn om overlasting er korrekt?

1. **Konstruktører kan overlastes.**
2. **Overlastning kan være et alternativ til å bruke standard (default) argument.**
3. ~~En medlemsfunksjon som er definert med virtual kan ikke overlastes.~~
4. **Det er valgfritt å overlaste en medlemsfunksjon som er definert med override.**


> **8.** Koden under er et eksempel på...

```c++
for (int i = 0; i < 3; i++) {
    int* values = new int[3] {1, 2, 3};
}
```

1. **Minnelekkasje**
2. ~~Hengende referanse (dangling reference)~~
3. ~~Dobbel frigjøring (double free)~~
4. ~~Dereferering av nullpeker~~

> **9.** Hvilke (en eller flere) av funksjonene kan føre til at vektorens minneavtrykk øker?

1. ~~size()~~
2. **resize()**
3. **reserve()**
4. **push_back()**

> **10.** Hvilke (en eller flere) av de følgende klassedeklarasjonene har en standard (default) konstruktør?

1. ~~class Class { public: int number; Class(int number) : number{number} {} };~~
2. **class Class { int number; public: Class() = default; };**
3. ~~class Class { int number; public: Class(const Class&) = delete; };~~
4. **class Class { int number; };**

> **11.** Hvilke (en eller flere) av følgende utsagn er korrekt?

1. **Hvis ImmutableSet::elements-variablen hadde vært public hadde friend vært unødvendig i ImmutableSet-klassen.**
2. ~~Koden kompilerer ikke fordi ImmutableSet::elements er private.~~
3. **Hvis operator+ hadde vært en medlemsoperator ville friend vært unødvendig i ImmutableSet-klassen.**
4. ~~Det går ikke an å lage tomme ImmutableSet-objekter.~~

> **12.** Hva er tilgangsnivået til medlemsfunksjonene og medlemsvariablene i Child-klassen?

- firstName - `ikke i skop`
- surname - `ikke i skop`
- address - `ikke i skop`
- getFirstName() - `public`
- getSurname() - `public`

# Del 2: Kortsvarsoppgaver (60p)

## 1. Forklar kort hovedforskjellen mellom prosedyreorientert programmering og objektorientert programmering.
Hovedforskjellen på prosedyre- og objektorientert programmering er bruk av klasser. Klasser gjør at vi kan ha mange objekter som følger ett sett med regler, metoder osv, som er enkel å reprodusere. Prosedyre handler mer om å utføre funksjoner mer sekvensielt.

## 2. Forklar kort hvilke fordeler det er med objektorientert programmering.
Fordelene med objektorientert programmering inkluderer modularitet, gjenbrukbarhet og fleksibilitet. Ved å definere klassemodeller som inneholder både data (attributter) og operasjoner (metoder), kan man kapsle inn kompleks funksjonalitet og skjule implementasjonsdetaljer. Dette gir bedre kontroll over dataintegritet og tilgang. Videre tillater objektorientert programmering arv, som muliggjør gjenbruk av kode ved å utvide eksisterende klasser med nye funksjonaliteter, og polymorfisme, som støtter dynamisk beslutning av hvilken metode som skal utføres, basert på objekttypen. Dette gjør systemene lettere å utvide og vedlikeholde.

## 3. Forklar kort i hvilke ulike tilfeller man bør bruke de ulike parameteroverføringene pass-by-value, pass-by-reference, og pass-by-const-reference.
Pass-by-value brukes når vi ønsker å jobbe med en kopi av dataene for å unngå endringer på den originale verdien utenfor funksjonens skop. Dette er nyttig for små datastrukturer der kopieringskostnaden er lav. Pass-by-reference benyttes når vi ønsker å endre den originale dataen direkte eller arbeide med store datastrukturer uten overhead av kopiering. Dette gjør det mulig å gjennomføre endringer på den faktiske variabelen som varer utover funksjonens levetid. Pass-by-const-reference brukes når vi trenger effektiviteten av pass-by-reference, altså å unngå kopiering, men ikke ønsker å tillate noen endring av dataene. Dette er ideelt for store, komplekse objekter der vi ønsker å sikre dataintegritet og samtidig minimere ressursbruk.

## 4. Forklar kort hvordan inn/ut datahåndtering (input/output handling) foregår med strømmodellen (I/O stream model).
Inn/ut datahåndtering fungerer som en strøm der vi kan accesse neste element med riktig operator. F eks vil vi bruke >> operator for å skrive til, altså data ut til en fil, og << for å motta data fra en fil.

## 5. Konverter følgende while-løkke til en for-løkke:
```cpp
#include <iostream>
using namespace std;

int a = 1;
int b;
while (a <= b){
    b++;
    cout << a << endl;
    a *= 2;
}
```

Min konvertering:

```c++
int b = 0;
for (int a = 1; a <= b; a *= 2) {
    b++;
    cout << a << endl;
}
```

## 6. Forklar kort fremgangsmåten for å opprette et grafisk brukergrensesnitt.
Først trenger vi et vindu som vi kan f eks bruke AnimationWindow biblioteket til, her trenger vi bredde og høyde på vinduet. Dette er da et objekt vi kan utføre operasjoner på. F eks er en av disse operasjonene å tegne rektangler, tekst eller sirkler. I vinduet er det et koordinatsystem som har origo oppe til venstre. Det betyr at nederst til høyre er {MAX_WIDTH, MAX_HEIGTH}. 

## 7. Forklar kort hovedforskjellen mellom kompileringsfeil, kjøretidsfeil og logiske feil.
Kompileringsfeil er feil som oppstår når vi prøver å kompilere programmet. Dette er feil som gjør at kompilatoren ikke skjønner hva den skal gjøre, som for eksempel om det mangler deklarasjon av variabel, mangler semi-kolon eller andre syntax-feil. Kjøretidsfeil er feil som oppstår når vi kjører selve programmet. For eksempel om vi prøver å hente ut data fra en dangling pointer. Logiske feil er feil som ikke vil gi oss feilmelding men heller produsere feile resultater. Disse er kanskje vanskeligst å oppdage da det ikke kommer noe feilmelding. Et eksempel er om du bygger en kalkulator og prøver 2+2 og ikke får 4. 

## 8. Se på koden under:
```cpp
#include <iostream>
using namespace std;

enum class PaintColour {Red, Yellow, Blue};

void printNumber(PaintColour colour) {
    cout << static_cast<int>(colour) << endl;
}

int main() {
    PaintColour paint = 1;
    printNumber(paint);
    return 0;
}
```

**a) Hvorfor kompilerer ikke koden?**
Ved å sette verdien til en enum er det ikke direkte overføring fra int til verdi, derfor vil `PaintColour paint = 1;` være problematisk.

**b) Hva må endres for å løse problemet**
Vi kan løse dette ved å kjøre en eksplisitt omgjøreing med `static_cast<PaintColor>(1)` i stedet for bare 1.

## 9. Forklar kort i hvilke ulike tilfeller man bør bruke de ulike tilgangsnivåene public, private og protected når man implementerer en klasse.

Private er det strengeste tilgangsnivået som bare tillater medlemsfunksjoner tilgang. Dette er for å sikre dataintegritet og at verdiene i private bare håndteres av intern, korrekt logikk.

Public er et åpent tilgangsnivå som kan brukes utenfor klassen. Her er f eks konstruktøren, destruktøren osv. Dette gjør at man kan bruke metoder, variabler osv utenfor klassen.

Protected er en slagsmellomting som er relevant når det kommer til arv. Den tillater arveklasser å få tilgang til disse verdiene og metodene, men ikke utenfor klassen selv.

## 10. Se på koden under:
```cpp
using namespace std;

class A {
    int numberOfA;
public:
    A(int numberOfA=0) : numberOfA{numberOfA} {}
    A(const A& a);
};

class B : public A {
    int numberOfB;
public:
    B(int numberOfB=0) : numberOfB{numberOfB} {}
};

int main() {
    B b(5);
    B b2 = b;
    return 0;
}
```

**a) Hvorfor kompilerer ikke koden?**
`B b2 = b;` vil ikke kompilere fordi kopikonstruktøren for `A` er deklarert, men ikke definert. Når du lager en kopi av et `B` objekt, forsøker den å bruke kopikonstruktøren fra `A` som ikke er definert.

**b) Hva må endres for å løse problemet**
```c++
class A {
    int numberOfA;
public:
    A(int numberOfA=0) : numberOfA{numberOfA} {}
    A(const A& a) : numberOfA{a.numberOfA} {} // Definisjon av kopikonstruktøren
};

class B : public A {
    int numberOfB;
public:
    B(int numberOfB=0) : A(), numberOfB{numberOfB} {}
    B(const B& b) : A(b), numberOfB{b.numberOfB} {} // Definisjon av kopikonstruktøren for B om nødvendig
};

int main() {
    B b(5);
    B b2 = b;
    return 0;
}
```



