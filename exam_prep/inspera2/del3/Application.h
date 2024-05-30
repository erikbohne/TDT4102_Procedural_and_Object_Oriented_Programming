#pragma once

#include "std_lib_facilities.h"
#include <filesystem>
#include <fstream>
#include "AnimationWindow.h"
#include "widgets/DropdownList.h"
#include "Simulator.h"

// ---------------------------------
// ---------- APPLICATION ----------
// ---------------------------------

class Application
{
public:
    Application ();
    
    string currentConfigFile;

    void run();
    void loadAndApplyConfiguration(filesystem::path filepath);
private:
    AnimationWindow window;
    Simulator sim;
    
    const int dashboardSize = 50;
    
    void drawBackground();
    void drawDashboard();
};

// ---------------------------------
// -------------- GUI --------------
// ---------------------------------
class ConfigList : public DropdownList {
public:
    ConfigList (vector<string> configFiles);
    ~ConfigList ();

    void callback();
    static void setApplication(Application* const _app);
private:
    static Application *app;

    vector<string> configFiles;
};

class ConfigButton : public Button {
public:
    ConfigButton ();
    ~ConfigButton ();

    void callback();
    static void setApplication(Application* const _app);
private:
    static Application *app;
};
