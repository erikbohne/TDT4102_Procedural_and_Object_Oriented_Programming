#include "DailyMenu.h"
#include "Cafeteria.h"

int main() {
  
    // Kode for å teste funksjonene
    // NB: 1a) og 1e) skriver ikke ut noe til skjerm
    
    // 1a
    cout << '\n' << "Oppgave 1.a):" << endl;
    DailyMenu testMenu = createDailyMenu("Vegan", "Beef", "Pasta");

    // 1b
    cout << '\n' << "Oppgave 1.b):" << endl;
    cout << testMenu << endl;

    // 1c
    cout << '\n' << "Oppgave 1.c):" << endl;
    Cafeteria Rapido{"Rapido", Location::Stripa};
    vector<DailyMenu> testVector{testMenu};
    Rapido.setWeeklyMenu(testVector);
    cout << Rapido.getDailyMenu(Weekday::Monday);

    // 1d
    cout << '\n' << "Oppgave 1.d):" << endl;
    if(Rapido.isInStock(testMenu)) {
        cout << "Test menu is in stock!" << endl;
    }
    else {
        cout << "Test menu is NOT in stock!" << endl;
    }

    // 1e
    cout << '\n' << "Oppgave 1.e):" << endl;
    testVector.push_back(createDailyMenu("Organic", "Burger", "Rice"));
    Rapido.setWeeklyMenu(testVector);
    Rapido.saveToFile("weeklyMenu.txt");


    // 2a
    cout << '\n' << "Oppgave 2.a):" << endl;
    Rapido.importStock("stock.txt");
    if(Rapido.isInStock(testMenu)) {
        cout << "Test menu is now in stock!" << endl;
    }
    else {
        cout << "Test menu is still not in stock!" << endl;
    }


    // 2b
    cout << '\n' << "Oppgave 2.b):" << endl;
    cout << getRandomMenu() << endl;


    // 2c
    cout << '\n' << "Oppgave 2.c):" << endl;
    Rapido.setWeeklyMenu(generateWeeklyMenu());
    for(auto m : Rapido.getWeeklyMenu()) {
        cout << m << endl;
    }


    return 0;
}