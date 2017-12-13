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

void locationService::deleteLocation() {
  int howManyLocationsExist = howManyLocations();
  int selection = -1;

  while(selection < 0 || selection > howManyLocationsExist) {
    uf.clearScreen();
    listLocationsWithIndex();
    cout << endl << "Select a location to delete or 0 to cancel: ";
    cin >> selection;
    if(cin.fail()) {
      cin.clear();      //reset error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      selection = -1;   //set selection to continue
    }
  }
    if(selection > 0){
  //Get this info before delete to show user later
  Location selectedLocation = getLocationAt(selection-1);  //selection is 1-based

  vector<string> locationFile = fo.getLinesFromFile("data/locations.txt");

  //erase selection from the vector representing the file
  //file is 0-indexed, selection is 1-indexed
  locationFile.erase(locationFile.begin() + (selection-1));

  //todo: write to legacy file what that id meant previously

  //reset location ids
  for(int i = (selection-1); i < locationFile.size(); i++) {
    Location wrongIndexLocation = convertLocationVector(stringfunc.split(locationFile.at(i)));
    wrongIndexLocation.setID(i+1);
    locationFile.at(i) = wrongIndexLocation.toString();
  }

  //overwrite
  fo.writeFile(locationFile, "data/locations.txt");

  cout << "Deleted: " << selectedLocation.getLocationName() << endl;
    }
}
