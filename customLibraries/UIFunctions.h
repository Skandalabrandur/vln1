#ifndef uifunctions_h
#define uifunctions_h

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "logoService.h"
#include "stringFunctions.h"

using namespace std;

class UIFunctions {
public:
  bool goodInput(char userChoice, const char legalChoices[]);
  void clearScreen();
  void pressEnter();
  void rawPressEnter();
  string prompt();
  void printLogo();
  void printItNice(vector<string> lines, vector<string> headers);

private:
  string _prompt = ">>>";
  stringFunctions stringfunc;
  logoService logo_service;
};

#endif
