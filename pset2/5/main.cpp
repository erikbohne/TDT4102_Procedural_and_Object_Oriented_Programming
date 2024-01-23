#include "std_lib_facilities.h"

// a)
vector<int> calculateBalance(int deposit, int rate, int years) {
    vector<int> balance;
    double d_rate = static_cast<double>(rate) / 100;
    for(int i = 0; i < years; i++) {
        int new_balance = deposit * pow((1 + d_rate), i);
        balance.push_back(new_balance);
    }

    return balance;
}

// b)
void printBalance(vector<int> balance) {
    cout << setw(2) << "År" << setw(12) << "Saldo" << endl;
    for (int i = 0; i < balance.size(); i++) {
        cout << setw(2) << i << setw(12) << balance.at(i) << endl;
    }
}

int main() {

    vector<int> balance = calculateBalance(5000, 3, 10);
    printBalance(balance);

    return 0;
}

// c)
// no operator "<<" matches these operands -- operand types are:
// std::ostream << std::vector<int, std::allocator<int>>
//
// Denne feilmeldingen får du om du prøver en vektor som argument i en cout strøm.
// Det man må gjøre, er å iterer gjennom vektoren og cout på hvert av elementene i stedet.

// d)
// vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//     for (int i = 0; i <= v.size(); i++) {
//     cout << v.at(i) << endl;
//     }
// 
// I forløkken blir den bedt om å iterer helt til i er like lengden av v, og om lengden av vektoren er x vil
// indekseringen være x-1, som betyr at når vi når den faktiske lengden av vektoren har vi nådd alle indeksene og vi
// prøve å nå en plass som ikke er der. Derfor skulle det eller stått i < v.size()