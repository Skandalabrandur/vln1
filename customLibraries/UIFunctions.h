#ifndef uifunctions_h
#define uifunctions_h

#include <cstring>
#include <iostream>
#include <string>
#include "logoService.h"

using namespace std;

class UIFunctions {
public:
  bool goodInput(char userChoice, const char legalChoices[]);
  void clearScreen();
  void pressEnter();
  void rawPressEnter();
  string prompt();
  void printLogo();

private:
  string _prompt = ">>>";
  logoService logo_service;
};

#endif
