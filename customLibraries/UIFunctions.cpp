#include "UIFunctions.h"

//Solution taken from:
//http://www.cplusplus.com/articles/4z18T05o/
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;

//legalChoices is a string of characters that are viable choices for the
//char userChoice.
//
//Example structure for function:
//
//    do {
//    ...                     //prompt user
//    cin >> userChoice       //get user input
//    ...                     //maybe something more
//    } while( !goodInput(userChoice, "aAbBcC"))
//
bool UIFunctions::goodInput(char userChoice, const char legalChoices[]) {
  for(int i = 0; i < strlen(legalChoices); i++) {
    if(tolower(legalChoices[i]) == tolower(userChoice)) {   //good input from user?
      return true;    //functions stops when it reaches a return statement
    }
  }
  //We make it through the for-loop which indicates
  //that the user hasn't made any good input
  return false;
}

void UIFunctions::clearScreen() {
  //Solution from:
  //http://www.cplusplus.com/articles/4z18T05o/
  if (system("CLS")) system("clear");
}

//Works for cases where cin buffer has something
void UIFunctions::pressEnter() {
  cout << "Press enter to continue" << endl;
  cin.ignore();     //ignore cin buffer (for instance if it contains '\n')
  cin.get();        //Halts program until user presses the Enter key
}

//If nothing is in the cin buffer then this one will work
//as intented
void UIFunctions::rawPressEnter() {
  cout << "Press enter to continue" << endl;
  cin.get();
}

string UIFunctions::prompt() {
  return _prompt;
}
