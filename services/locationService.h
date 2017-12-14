#ifndef locationservice_h
#define locationservice_h

#include "UIFunctions.h"
#include "fileOperations.h"
#include "stringFunctions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "Location.h"
using namespace std;

class locationService {
public:
    Location convertLocationVector(vector<string> locationWords);
    Location getLocationAt(int index);
    void listLocations();
    void listLocationsWithIndex();
    void createNewLocation();
    int howManyLocations();
private:
    fileOperations fo;
    stringFunctions stringfunc;
    UIFunctions uf;
};

#endif
