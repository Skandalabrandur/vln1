
#include "UIbaker.h"

using namespace std;

void UIbaker::bakerUI() {
  char choice;
  do {
    cout << "Store: " << endl;
    //print list of stores
    cout << endl << "B - Go Back" << endl;
    cin >> choice;
  } while( !ui.good_choice(choice, "pPbBtT"));

}

