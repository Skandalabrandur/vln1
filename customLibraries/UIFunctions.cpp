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

//Confirmed to work for most linux/mac terminal applications
//Works for cmd.exe
//Not sure if powershell supports this
void UIFunctions::clearScreen() {
  //Solution from:
  //http://www.cplusplus.com/articles/4z18T05o/
  if (system("CLS")) system("clear");

  printLogo();
}

//Works for cases where cin buffer is not empty
void UIFunctions::pressEnter() {
  cout << "Press enter to continue" << endl;
  cin.ignore();     //ignore cin buffer (for instance if it contains '\n')
  cin.get();        //Halts program until user presses the Enter key
}

//If nothing is in the cin buffer then this one will work
//as intented
//No real use cases really, unless you're testing in
//main.cpp before any user input happens
void UIFunctions::rawPressEnter() {
  cout << "Press enter to continue" << endl;
  cin.get();
}

//easy to declare a system wide prompt
//if we ever want to change the look
//  declared in UIFunctions.h under private:
string UIFunctions::prompt() {
  return _prompt;
}

void UIFunctions::printLogo() {
  vector<string> logo = logo_service.getLogo();

  for(int i = 0; i < logo.size(); i++) {
    cout << logo.at(i) << endl;
  }
}


void UIFunctions::printItNice(vector<string> lines, vector<string> headers) {
  vector<int> spaceFormatting;
  //Get header string length
  for(int i = 0; i < headers.size(); i++) {
    spaceFormatting.push_back(headers.at(i).size());
  }

  //get longest words in lines
  for(int i = 0; i < lines.size(); i++) {
    vector<string> words = stringfunc.split(lines.at(i));
    for(int j = 0; j < headers.size(); j++) {
      if(words.at(j).size() > spaceFormatting.at(j)) {
        spaceFormatting.at(j) = words.at(j).size();
      }
    }
  }


  for(int i = 0; i < headers.size(); i++) {
    cout << "|";
    cout << " " << headers.at(i) << " ";
    int spaceRemainder = spaceFormatting.at(i) - headers.at(i).size();

    for(int k = spaceRemainder; k > 0; k--) {
      cout << " ";
    }
  }
  cout << "|";
  cout << endl << endl;


  for(int i = 0; i < lines.size(); i++) {
    vector<string> words = stringfunc.split(lines.at(i));
    for(int j = 0; j < words.size(); j++) {
      if(j < headers.size()) {
        cout << "|";
        cout << " " << words.at(j) << " ";
        int spaceRemainder = spaceFormatting.at(j) - words.at(j).size();
        for(int k = spaceRemainder; k > 0; k--) {
          cout << " ";
        }
      } else {
        cout << ", " << words.at(j);
      }
    }
    cout << endl;
  }
}
