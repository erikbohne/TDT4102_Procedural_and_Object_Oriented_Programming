#include "Cafeteria.h"

Cafeteria::Cafeteria(string n, Location l) : name{n}, location{l} {
    for(auto p : mainDishPrices) {
        stock.insert({p.first, 0});
    }
    for(auto p : sideDishPrices) {
        stock.insert({p.first, 0});
    }
}

vector<DailyMenu> Cafeteria::getWeeklyMenu() {
    return weeklyMenu;
}

void Cafeteria::setWeeklyMenu(vector<DailyMenu> menu) {
    weeklyMenu = menu;
}

int Cafeteria::getStock (string item) {
    return stock.at(item);
}

void Cafeteria::setStock(string item, int amount) {
    stock.at(item) = amount;
}

void Cafeteria::removeStock(string item) {
    stock.at(item)--;
}

//------------------------------------------------------------------------------------------------

DailyMenu Cafeteria::getDailyMenu(Weekday w) {
    // BEGIN: 1c
    
    int index = static_cast<int>(w);
    DailyMenu menu = weeklyMenu.at(index);
    return menu;

    // END: 1c
}

bool Cafeteria::isInStock(DailyMenu menu) {
    // BEGIN: 1d

    if(stock.at(menu.mainDish) > 0 && stock.at(menu.sideDish) > 0) {
        return true;
    }
    else {
        return false;
    }

    // END: 1d
}

void Cafeteria::saveToFile(string fileName) {
    // BEGIN: 1e
    
    ofstream file;
    file.open(fileName);
    for(auto m : weeklyMenu) {
        file << m.adjective << " " << m.mainDish << " " << m.sideDish << " " << m.price << endl;
    }
    file.close();

    // END: 1e
}


void Cafeteria::importStock(string fileName) {
    // BEGIN: 2a

    ifstream file;
    file.open(fileName);
    string line;
    while(getline(file, line)) {
        istringstream iss{line};
        string item;
        int count;
        iss >> item >> count;
        item.pop_back();
        stock[item] = count;
    }
    file.close();

    // END: 2a
}


vector<DailyMenu> generateWeeklyMenu() {
    // BEGIN: 2c

    vector<DailyMenu> menu;
    for (int i = 0; i < 7; i++) {
        menu.push_back(getRandomMenu());
    }
    return menu;

    // END: 2c
}