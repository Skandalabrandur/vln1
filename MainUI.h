#ifndef mainui_h
#define mainui_h
#include <string>

using namespace std;

class MainUI {

public:
  bool good_choice(char chosen, string legitChoices);
  void clearScreen();
  void pressEnter();
  void startUI();
  void deliveryUI();

private:

};

#endif
