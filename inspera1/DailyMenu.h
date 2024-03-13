#pragma once
#include "utilities.h"

extern const map<string, double> mainDishPrices;
extern const map<string, double> sideDishPrices;


struct DailyMenu {

    string adjective;
    string mainDish;
    string sideDish;
    double price;

    friend ostream &operator<<(ostream &os, DailyMenu d);

};

DailyMenu createDailyMenu(string adjective, string mainDish, string sideDish);
DailyMenu getRandomMenu();