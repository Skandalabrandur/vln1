#ifndef location_h
#define location_h
#include <iostream>
#include <string>
#include "stringFunctions.h"
using namespace std;

class Location {

public:
  Location();
    Location(string name, int price);
  string toString();
private:
  string _name;
  int _id;

  stringFunctions stringfunc;
};

#endif
