#include "locationService.h"
using namespace std;

Location locationService::convertLocationVector(vector<string> locationWords) {
  Location location(locationWords.at(0), stringfunc.stringToInt(locationWords.at(1)));
  return location;
}

Location locationService::getLocationAt(int index) {
  vector<string> lines = fo.getLinesFromFile("data/locations.txt");

  //stringfunc splits string into vector<string>
  return convertLocationVector(stringfunc.split(lines.at(index)));
}

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

    cout << "Enter location name (c to cancel): ";
    cin >> name;
    if(name != "c"){
    //Find location id
    int id = howManyLocations() + 1;
    cout << name << " ID is " << id << endl;

    Location location(name, id);
    fo.appendLineToFile(location.toString(), "data/locations.txt");

    cout << "Location: \"" << location.toString() << "\" created!" << endl;
    }
}

int locationService::howManyLocations() {
  return fo.countLines("data/locations.txt");
}
