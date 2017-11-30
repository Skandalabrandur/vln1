#ifndef mainui_h
#define mainui_h
#include <string>

using namespace std;

class MainUI {

public:
  bool good_choice(char chosen, string legitChoices, int numOfChoices);
  void clearScreen();
  void pressEnter();
  void startUI();
  void managementUI();
  void salesUI();
  void bakersUI();
  void deliveryUI();
  void manage_pizzas();
  void manage_toppings();

private:

};

#endif
