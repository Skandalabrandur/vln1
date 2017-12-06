#ifndef uifunctions_h
#define uifunctions_h

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class UIFunctions {
public:
  bool goodInput(char userChoice, const char legalChoices[]);
  void clearScreen();
  void pressEnter();
  void rawPressEnter();
  string prompt();

private:
  string _prompt = ">>>";

};

#endif
