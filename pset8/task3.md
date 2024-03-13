## 3 a) Gitt følgende kode, hva forventer du at skrives ut når dummyTest kjører?

```c++
#pragma once
#include <iostream>
#include <utility>

class Dummy {
public:
    int *num;
    Dummy() {
        num = new int{0};
    }
    ~Dummy() {
        delete num;
    }
};
```

og 

```c++
#include "dummy.h"

void dummyTest() {
    Dummy a;
    *a.num = 4;
    Dummy b{a};
    Dummy c;
    c = a;
    std::cout << "a: " << *a.num << '\n';
    std::cout << "b: " << *b.num << '\n';
    std::cout << "c: " << *c.num << '\n';
    *b.num = 3;
    *c.num = 5;
    std::cout << "a: " << *a.num << '\n';
    std::cout << "b: " << *b.num << '\n';
    std::cout << "c: " << *c.num << '\n';
}
```

### Svar:
Forventet resultat i terminalen:
```plaintext
a: 4
b: 4
c: 4
a: 5
b: 5
c: 5
```

Forklaring:
- `a` blir opprettet og peker på en minneadresse med verdien 4.
- `b` blir opprettet og peker på samme minneadresse som `a`.
- `c` blir opprettet og peker på samme minneadresse som `a`.
- Når `b` endres, endres også `a` og `c` fordi de peker på samme minneadresse.
- Når `c` endres, endres også `a` og `b` fordi de peker på samme minneadresse.
- Derfor vil alle tre ha verdien 5 når `*c.num = 5;`.


## 3 b) Hva skjedde?

### Svar:

Programmet skriver ut som forventet i terminalen, men vi får malloc error når programmet avsluttes. Dette er fordi vi har en memory leak i programmet.

## 3 c) Hvordan kan vi fikse dette?

### Svar:

```c++
Dummy& operator=(const Dummy& otherDummy) {
        if (this != &otherDummy) {
            delete num;
            num = new int;
            *num = *otherDummy.num;
        }
        return *this;
    }
```

Dette gjør at vi sletter minneadressen til `num` før vi oppretter en ny minneadresse og kopierer verdien fra `otherDummy.num` over til `num`.