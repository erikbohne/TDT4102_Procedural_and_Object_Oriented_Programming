#pragma once
#include "DailyMenu.h"


class Cafeteria {
    private:
        string name;
        Location location;
        vector<DailyMenu> weeklyMenu;
        map<string, int> stock;

    public:
        Cafeteria(string n, Location l);

        void importStock(string filename);
        bool isInStock(DailyMenu menu);
        vector<DailyMenu> getWeeklyMenu();
        void saveToFile(string filename);
        DailyMenu getDailyMenu(Weekday w);

        void setWeeklyMenu(vector<DailyMenu> menu);
        int getStock(string item);
        void setStock(string item, int amount);
        void removeStock(string item);
};



vector<DailyMenu> generateWeeklyMenu();