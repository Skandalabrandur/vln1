#ifndef locationservice_h
#define locationservice_h

#include "UIFunctions.h"
#include "fileOperations.h"
#include "stringFunctions.h"
#include <iostream>
#include <fstream>
using namespace std;

class locationService {
public:
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
