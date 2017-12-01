#include "UIbaker.h"

using namespace std;

void UIbaker::bakerUI() {
  char choice;
  int numPlaces;
  //int i = choice;
  do {
    cout << "Choose your store: " << endl;
    //print list of stores
    WRplace wrplace;
    numPlaces = wrplace.listAndCountPlaces();
    cout << endl << "B - Go Back" << endl;
    cin >> choice;

  } while(choice != 'b' && choice != 'B' && choice < 49 && choice > numPlaces);

  if(choice != 'b' && choice != 'B'){
      cout << "Active pizzas: " << endl;

      //TO DO: Retrieve and list pizzas from chosen place
      //------ WRSalesPizza class needs to be implemented
      cout << "Not yet implemented." << endl;

      //TO DO: Choose one pizza from list

      //Choose action for chosen pizza
      chooseActionForPizza();
  }

}

void UIbaker::chooseActionForPizza(){
    char choice;
    do {
        cout << endl << "Choose action for pizza: " << endl;
        cout << "P - In progress" << endl;
        cout << "R - Ready" << endl;
        cout << "B - Go Back" << endl;
        cin >> choice;

      } while(!ui.good_choice(choice, "pPrRbB"));

      if(choice == 'p' || choice == 'P'){
        cout << "Not yet implemented." << endl;
        ui.pressEnter();
      }
      if(choice == 'r' || choice == 'R'){
        cout << "Not yet implemented." << endl;
        ui.pressEnter();
      }
}
