# Del 1

> **1.** Hva må minimum presiseres ved variabeldeklarasjon?
1. **Navn**
2. ~~Verdi~~
3. **Datatype**
4. ~~Navnerom (Namespace)~~

> **2.** Hvilke (en eller flere) av følgende utsagn er korrekt?
1. ~~Variabelen v4 vil evalueres ved kjøretid.~~
2. **Kallet til funksjonen incrementValue() i linje 8 vil evalueres ved kompileringstid.**
3. ~~Kallet til funksjonen incrementValue() i linje 7 vil evalueres ved kompileringstid.~~
4. **Funksjonen incrementValue() har ingen bivirkninger (side effects).**

> **3.** Hvilke (en eller flere) av de følgende deklarasjonene og definisjonene av operator << i klassen Date vil tillate oss å printe feltene i klassen?
1. ~~Alternativ 1~~
2. ~~Alternativ 2~~
3. ~~Alternativ 3~~
4. **Alternativ 4** (Vi må ha en operator overlastning som friend fordi den har en annen operator på venstre siden enn klassen selv, men trenger tilgang til klassens medlemsvariabler.)

> **4.** Hvilke (en eller flere) alternativ er en egendefinert type?
1. **En struct**
2. **En enum-klasse**
3. **En abstrakt klasse**
4. **En enum**

> **5.** Hvilke (en eller flere) av sammenligningene vil IKKE gi feil?
1. ~~Alternativ 1~~
2. **Alternativ 2**
3. ~~Alternativ 3~~
4. ~~Alternativ 4~~

> **6.** Koden under er et eksempel på...
1. **Dobbel tom (double free)**
2. ~~Minnelekkasje~~
3. ~~Dinglende referanse (dangling reference)~~
4. ~~Dereferering av nullpeker~~

> **7.** Hvilke (en eller flere) av følgende utsagn er korrekt?
1. ~~book er allokert i heap, mens cppBook er allokert på stack.~~
2. **Når func() returnerer er minnet som ble allokert til cppBook deallokert.**
3. ~~Både book og cppBook er allokert på stack.~~
4. ~~Koden inneholder en minnelekkasje.~~

> **8.** Hvilke (en eller flere) av følgende utsagn er korrekt?
1. ~~book er allokert i heap, mens cppBook er allokert på stack.~~
2. ~~Når func() returnerer er minnet som ble allokert til cppBook deallokert.~~
3. **Koden inneholder en minnelekkasje.**
4. ~~Både book og cppBook er allokert på stack.~~

> **9.** Hvilke (en eller flere) av følgende utsagn er korrekt?
1. ~~Man kan ikke endre på adressen som er lagret i en peker.~~
2. ~~En peker kan ikke referere til en verdi som ikke eksisterer.~~
3. **Man kan endre på verdien en peker refererer til, men ikke uten å dereferere pekeren først.**
4. **&-operatoren kan brukes til å finne adressen til en variabel.**

> **10.** Hvilke (en eller flere) av følgende utsagn er korrekt?
1. **Å lage en instans av klassen vil allokere minne.**
2. ~~Klassen har ikke en kopikonstruktør.~~
3. ~~Klassen har ikke en standard (default) konstruktør.~~
4. ~~Klassen mangler en destruktør.~~

> **11.** Hvilke (en eller flere) av følgende utsagn er korrekt?
1. ~~Et predikat (boolsk objekt) kan ikke deklareres som en friend.~~
2. ~~Terminalen kan ikke skrive ut egendefinerte datatyper som er deklarert med friend.~~
3. **friend-deklarasjoner kan brukes til å overlaste output-operatoren.**
4. **friend-deklarasjoner gir tilgang til private klassemedlemmer.**

> **12.** Hva er tilgangsnivået til medlemsfunksjonene og medlemsvariablene i Child-klassen? (Kryss av i riktig boks for hver variabel eller funksjon.)
- firstname - `ikke i skop`
- getFirstName() - `protected`
- getSurname() - `protected`
- address - `protected`
- surname - `protected`

# Del 2

> **13.** Forklar kort hva en kompilator er.

En kompilator er noe som omgjør menneskeskrevet kode til maskinkode som kan utføres på CPU-en.

> **14.** Forklar kort hvorfor teknikken fremoverdeklarasjon brukes på linje 1 i koden under.

For å bruke en klasse må den være deklarert. I eksempelet øsnker vi å bruke klasse A før den er definert, og derfor må vi slenge på en deklarasjon av A før vi bruker den i B.

> **15.** Forklar kort hvorfor man må sjekke om resultatet ligger innenfor et intervall [a, c] når vi skal verifisere at en funksjon som utfører flyttalloperasjoner gir ønsket resultat b i stedet for å sjekke at resultatet er lik b.

I teorien har ett tall som pi uendelig mange desimaler, men siden datamaskiner operer med bits og bytes, har vi bare en endelig antall siffer i hvert tall. Derfor er ikke flyttal (`double`) like nøyaktige, spesielt med mange desimaler. Derfor vil vi kunne få en feilmargin som gjør at vi bær sjekke innenfor et intervall og ikke direkte. F eks vil 3 som flyttal kunne se slik ut: `3.00000000000004`, som ikke er det samme som `3.0`.

> **16.** Forklar kort hvorfor det er god praksis å deklarere en variabel konstant (const) når variabelen ikke skal endres.

Når man bruker `const` vil en variabel eller funksjon ikke endres i kjøretid som sikrer at vi ikke endrer på verdier som ikke skal endres på. Dette gjør koden sikrere og lettere å lese.

> **17.** Forklar kort hvorfor man bruker funksjoner.

Funksjoner lar oss slippe å skrive logikk flere ganger, men heller skrive en gang som kan brukes om igjen. Dette gjør koden modulær og kortere.

> **18.** Konverter følgende for-løkke til en while-løkke.

```c++
int b = 100;
int a = 1
while (a <= b) {
    std::cout << a << " < " << b << std::endl;
    b++;
    a *= 3;
}
```

> **19.** Forklar kort bruksområdene til templates.

Vi bruker templates når vi ønsker å tillate flere typer, og ikke nødvendigvis bare én. F eks vil vi kunne utføre samme operasjoner på `array` og `vector` selv om de ikke er samme type. Samme kan gjelde ulike klasser eller andre objekter som har sammer operatorer eller er lignende. Det gir altså mer fleksibilitet.

> **20.** Forklar kort de fire ulike risikoene man har med pekere.

1. Dangling pointer: Er en pointer hvor minnet har blitt deallokert slik at den ikke peker på noe spesifikt lengre.
2. Wild Pointer: Er en pointer som peker på noe den ikke skal peke på. Hva som ligger på verdien kan tilhøre et annet program eller andre elementer og endringer kan skade kjøring av andre eller dette systemet.
3. Memory Leaks: Om man mister adresser og pointere uten å deallokere minnet vil man ikke ha noe måte å accesse minnet på og det ligger et random sted i heap memoriet. Det er ikke optimalt ifht minneoptimalisering
4. Buffer Overflow: Når vi går utenfor den allokerte plassen til en pointer, da kan vi i likhet med wild pointer få feil verdi og eller røre noe som kan være skadelig for andre programmer.

> **21.** Forklar kort forskjellen mellom grunn kopi (shallow copy) og dyp kopi (deep copy).

Grunn kopi vil si at man kopierer referansen og ikke selve verdien. Dette gjør at om man endrer verdien til en grunnkopi av orginalen, vil også orginalen endres. Deep copy vil lage et helt nytt og identisk objeckt som er uavhengig av orginalen.

> **22.** Forklar kort de to ulike måtene man kan lage en abstrakt klasse.

1. Ved bruk av rene virtuelle funksjoner:
   - En klasse blir abstrakt når den inneholder minst én ren virtuell funksjon deklarert med `= 0`. Dette tvinger avledede klasser til å implementere denne funksjonen.

2. Ved bruk av virtuelle funksjoner uten full implementasjon:
   - En baseklasse kan ha virtuelle funksjoner med minimal eller tom implementasjon, som antyder at avledede klasser bør utvide disse. Klasse blir ikke abstrakt med mindre det inkluderer en ren virtuell funksjon.
 

> **23.** Forklar kort hvorfor man bør markere redefinisjonen av virtuelle superklasse-funksjoner med nøkkelordet override i subklassen.

Ved bruk av override tydeliggjør vi at det er en virtuel funksjon som defineres eller redefineres. Dette forsikrer at det er en virtuel funksjon og gjør det tydeligere for andre å lese koden.

> **24.** Forklar kort hvorfor man må bruke funksjonen emplace_back() i stedet for funksjonen push_back() på en unique_ptr for å legge til en ny verdi.
Skriv ditt svar her.

`emplace_back()` vil plassere pointeren bakerst i listen uten å kopiere selve objektet slik `push_back()` i en vektor vil gjøre. Siden Objektet i seg selv ikke er en pointer kan vi ikke bruke `push_back()` på en `unique_ptr`, men må bruke `emplace_back()`.
