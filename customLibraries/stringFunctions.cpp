#include "stringFunctions.h"

using namespace std;

//splits string on spaces, newlines and string end \0
//Example:
//  vector<string> words = stringfunc.split("dingo bingo gringo thingo");
//  words[0] → "dingo"
// ...
// words[3] → "thingo"
vector<string> stringFunctions::split(string str) {
  vector<string> words;               //initialize vector
  string builder;                     //initialize string for building words
  for(int i = 0; i < str.size(); i++) {
    if(str[i] != ' ' && str[i] != '\n') {
      builder = builder + str[i];  //until delimiter, add character to builder

      //We do this if instead of being crazy and accessing the '\0' out of bounds
      if( i == (str.size() - 1) ) {
        words.push_back(builder);
      }
    } else {
      //we have
      words.push_back(builder);
      builder = "";
    }
  }
  return words;
}

//Some c++11 functions such as "to_string()" are not available for certain
//versions of mingW-gcc on windows so for the sake of cross-platform
//we include this here
string stringFunctions::intToString(int integer) {
  stringstream sout;
  sout << integer;
  string str = sout.str();
  return str;
}

int stringFunctions::stringToInt(string str) {
  int value;
  stringstream sin(str);
  sin >> value;
  return value;
}

string stringFunctions::boolToString(bool ean) {
  if(ean) {
    return "true";
  } else {
    return "false";
  }
}
