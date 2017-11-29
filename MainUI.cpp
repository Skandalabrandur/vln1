#include "MainUI.h"
#include "Pizza.cpp"
#include <string>

using namespace std;


//checks if character is found in the availableChoices string
bool MainUI::good_choice(char chosen, string legitChoices, int numOfChoices) {
  bool legit = false; //initialize return to false

  for(int i = 0; i < numOfChoices; i++) {
    if(chosen == legitChoices[i]) {
      legit = true;   //the function will now return true
      break;
    }
  }

  return legit;
}

void MainUI::create_pizza() {

  char choice;
  do {
    cout << "What do?" << endl << endl;
    cout << "p - Create Pizza" << endl;
    cout << "q - Quit" << endl;
    cin >> choice;
  } while ( !good_choice(choice, "pq", 2) );
  if(choice == 'p') {
    Pizza pizza;
    cin >> pizza;
  } else {
    //quit
  }

}
