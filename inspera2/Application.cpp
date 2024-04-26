#include "Application.h"
#include "fstream"

// ---------------------------------
// ------------ HELPERS ------------
// ---------------------------------
vector<string> getConfigurationFiles(string directory)
{
    vector<string> filenames;
    
    for (const auto& file : filesystem::directory_iterator(directory)) {
        filesystem::path filepath = file.path();
        string filename = filepath.string();
        filenames.push_back(filename);
    }

    std::sort(filenames.begin(), filenames.end());

    return filenames;
}

// ---------------------------------
// ---------- APPLICATION ----------
// ---------------------------------
Application::Application ()
    : window(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "Boid simulator"), sim(window) {}

void Application::run()
{
    // ------------- CONFIG ------------
    vector<string> configFiles = getConfigurationFiles("configurations");
    ConfigList configList{configFiles};
    ConfigList::setApplication(this);
    window.add(configList);
    
    // -------------- GUI --------------
    ConfigButton configButton{};
    ConfigButton::setApplication(this);
    window.add(configButton);
    
    ToggleButton toggleButton{};
    ToggleButton::setSimulator(&sim);
    window.add(toggleButton);

    ResetButton resetButton{};
    ResetButton::setSimulator(&sim);

// Task T3: Add a Reset button for the simulation to the AnimationWindow.
// BEGIN: T3
    window.add(resetButton);
// END: T3

    // -------- SIMULATION LOOP --------

    while (!window.should_close()) {
        drawBackground();
        if (sim.simulationEnabled) {
            sim.simulate();
            sim.drawUniverse();
        } else {
            sim.drawUniverse();
        }
        drawDashboard();

        window.next_frame();
    } 
}

// Task T5: I/O - Load and apply the configuration given by the
// configuration file at filepath.
void Application::loadAndApplyConfiguration(filesystem::path filepath)
{
// BEGIN: T5
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filepath << endl;
        return;
    }
    // First line is doves and second is hawks
    int doves, hawks;
    file >> doves >> hawks;
    sim.applyConfiguration(doves, hawks);
// END: T5
}

void Application::drawBackground()
{
    window.draw_rectangle({0, dashboardSize}, window.width(), window.height() - dashboardSize, Color::light_cyan);
}

void Application::drawDashboard()
{
    window.draw_rectangle({0, 0}, window.width(), dashboardSize, Color::light_gray);
}

// ---------------------------------
// -------------- GUI --------------
// ---------------------------------
ConfigList::ConfigList (vector<string> configFiles)
    : DropdownList({420, 5}, 400, 50, configFiles),
    configFiles{configFiles}
{
    setCallback(bind(&ConfigList::callback, this));
}

ConfigList::~ConfigList() {}

void ConfigList::callback()
{
    ConfigList::app->currentConfigFile = this->getValue();
}

void ConfigList::setApplication(Application* const _app)
{
    app = _app;
}

Application* ConfigList::app = nullptr;

ConfigButton::ConfigButton () : Button({820, 5}, 200, 50, "Load and Apply")
{
    setCallback(bind(&ConfigButton::callback, this));
}

ConfigButton::~ConfigButton() {}

void ConfigButton::callback()
{
    string configFile = ConfigButton::app->currentConfigFile;
    if (!configFile.empty()) {
        ConfigButton::app->loadAndApplyConfiguration(configFile);
    }
}

void ConfigButton::setApplication(Application* const _app)
{
    app = _app;
}

Application* ConfigButton::app = nullptr;
