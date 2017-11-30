#ifndef UImanagement_h
#define UImanagement_h
#include <string>
#include "MainUI.h"

using namespace std;

class UImanagement {

public:
  void managementUI();
  void manage_pizzas();
  void manage_toppings();
  void manage_places();

private:
  MainUI ui;
};

#endif
