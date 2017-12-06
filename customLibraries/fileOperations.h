#ifndef fileoperations_h
#define fileoperations_h
#include "stringFunctions.h"
#include <vector>
#include <string>

using namespace std;

class fileOperations {

public:
  vector<string> getLinesFromFile(const char file[]);
  vector<string> getWordsFromLine(int index, const char file[]);
  void appendLineToFile(string line, const char file[]);
  void printLines(const char file[]);
  void printLinesWithIndices(const char file[]);
  string getLineAt(int index, const char file[]);
  int countLines(const char file[]);
private:
  stringFunctions stringFunc;
};

#endif
