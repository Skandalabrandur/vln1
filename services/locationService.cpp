#include "locationService.h"
#include "Location.h"
using namespace std;

//Lists all toppings without indices
void locationService::listLocations() {
    fo.printLines("data/locations.txt");
}

//Useful for selections
//Note... this is not zero-based but one-based indexing.
void locationService::listLocationsWithIndex() {
    fo.printLinesWithIndices("data/locations.txt");
}

//Creates a new topping from the admin menu.
//Not inteded for use out of admin menu.
void locationService::createNewLocation() {
    string name;
    int id;
    
    uf.clearScreen();
    cout << "Enter location name: ";
    cin >> name;
    
    uf.clearScreen();
    cout << "Enter location ID: ";
    cin >> id;
    
    Location location(name, id);
    fo.appendLineToFile(location.toString(), "data/locations.txt");
    
    uf.clearScreen();
    cout << "Location: \"" << location.toString() << "\" created!" << endl;
    uf.pressEnter();
}
