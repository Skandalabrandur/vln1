#include "Location.h"

Location::Location() {
  _name  = "Unnamed";
  _id = 1;
}

Location::Location(string name, int id) {
  _name  = name;
  _id = id;
}

//Most if not all toString() methods are the ones who will ultimately get written
//out to a file
string Location::toString() {
  return _name + " " + stringfunc.intToString(_id);
}

int Location::getID(){
    return _id;
}

void Location::setID(int id) {
  _id = id;
}

string Location::getLocationName(){
    return _name;
}
