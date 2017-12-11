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

//Creates a new location from the admin menu.
//Not intended for use out of admin menu.
void locationService::createNewLocation() {
    string name;

    uf.clearScreen();
    cout << "Enter location name: ";
    cin >> name;

    //Find location id
    int id = howManyLocations() + 1;
    cout << name << " ID is " << id << endl;

    Location location(name, id);
    fo.appendLineToFile(location.toString(), "data/locations.txt");

    cout << "Location: \"" << location.toString() << "\" created!" << endl;
    uf.pressEnter();
}

int locationService::howManyLocations() {
  return fo.countLines("data/locations.txt");
}
