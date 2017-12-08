#include "Location.h"

Location::Location() {
  _name  = "Unnamed";
  _id = 1;
}

Location::Location(string name, int id) {
  _name  = name;
  _id = id;
}

string Location::toString() {
  return _name + " " + stringfunc.intToString(_id);
}
