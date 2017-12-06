#ifndef stringfunctions_h
#define stringfunctions_h
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

class stringFunctions {
public:
  vector<string> split(string str);
  string intToString(int integer);
  int stringToInt(string str);
  string boolToString(bool ean);

private:
};

#endif
