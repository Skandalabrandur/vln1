#include "bakerUI.h"

using namespace std;

void bakerUI::displayBakerMenu() {
    //DO DO: choose location
    uf.clearScreen();
    chooseLocation();

    char userInput;
    while (userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "HOME/BAKER" << endl;
            cout << "L - LIST PIZZAS FOR YOUR PLACE" << endl;
            cout << "O - LIST PIZZAS BY ORDERS" << endl;
            cout << "M - MARK PIZZA AS BAKED" << endl;
            cout << "U - MARK PIZZA AS UNBAKED" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "mblou"));

        userInput = tolower(userInput);

        if(userInput == 'l') {
          if(vs.pizzasExistForLocationID(_locationID)) {
            uf.clearScreen();
            cout << "HOME/BAKER/LIST PIZZAS" << endl;
            viewPizzas();
          } else {
            cout << "No pizzas exist for your location!" << endl;
            cout << "A good opportunity to relax :)" << endl;
            uf.pressEnter();
          }
        }

        if(userInput == 'o') {
          if(vs.pizzasExistForLocationID(_locationID)) {
            uf.clearScreen();
            cout << "HOME/BAKER/LIST PIZZAS BY ORDERS" << endl;
            listByOrders();
          } else {
            cout << "No pizzas exist for your location!" << endl;
            cout << "A good opportunity to relax :)" << endl;
          }
          uf.pressEnter();
        }

        if(userInput == 'm') {
          if(vs.pizzasExistForLocationID(_locationID)) {
            cout << "HOME/BAKER/MARK BAKED" << endl;
            uf.clearScreen();
            selectAndMarkPizzaAsBaked();
          } else {
            cout << "No pizzas exist for your location!" << endl;
            cout << "A good opportunity to relax :)" << endl;
            uf.pressEnter();
          }
        }

        if(userInput == 'u') {
          if(vs.pizzasExistForLocationID(_locationID)) {
            cout << "HOME/BAKER/MARK UNBAKED" << endl;
            uf.clearScreen();
            selectAndMarkPizzaAsUnbaked();
          } else {
            cout << "No pizzas exist for your location!" << endl;
            cout << "A good opportunity to relax :)" << endl;
            uf.pressEnter();
          }
        }

    }
}

void bakerUI::chooseLocation(){
    //lists locations from file, user inputs their location
    location_service.listLocationsWithIndex();
    int numLocations = location_service.howManyLocations();
    int choice;
    do{
        cout << "Select your location: ";
        cin >> choice;

        if(cin.fail()) {
          cin.clear();    //reset error flags
          cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
          choice = 0;     //set choice to continue loop
        }
    }while(choice <= 0 || choice > numLocations);
    //If changed so admin can delete locations then this does probably not work
    //Could make a function getLocationID(choice)
    _locationID = choice;
}

void bakerUI::viewPizzas() {
  pizza_service.listFromLocationActivePizzas(_locationID);
  uf.pressEnter();
}

void bakerUI::selectAndMarkPizzaAsBaked() {
  int index = -1;
  while(index < 0 || index > pizza_service.howManyActivePizzas()) {
    pizza_service.listActiveWithIndicesForBakeryAndLocation(false, _locationID);
    cout << "Please select a pizza to mark as BAKED (0 to cancel): ";
    cin >> index;
  }
  if(index != 0) {
  int adjustedIndex = pizza_service.adjustBakerIndexForBaked(false, _locationID, index);
    pizza_service.setActivePizzaStatus((adjustedIndex), "baked", true);
    uf.pressEnter();
  }
}

void bakerUI::selectAndMarkPizzaAsUnbaked() {
  int index = -1;
  while(index < 0 || index > pizza_service.howManyActivePizzas()) {
    pizza_service.listActiveWithIndicesForBakeryAndLocation(true, _locationID);
    cout << "Please select a pizza to mark as UNBAKED (0 to cancel): ";
    cin >> index;
  }
  if(index != 0) {
    int adjustedIndex = pizza_service.adjustBakerIndexForBaked(true, _locationID, index);
    pizza_service.setActivePizzaStatus(adjustedIndex, "baked", false);
    uf.pressEnter();
  }
}

void bakerUI::listByOrders() {
  order_service.listOrderOverviewWithIndicesForLocation(_locationID);

  int selection;
  cout << "Select an order for more info: ";
  cin >> selection;

  int adjustedSelection = order_service.getOrderIdFromIndexSelectionForLocation(selection, _locationID);
  uf.clearScreen();
  order_service.listSpecificOrderWithInfo(adjustedSelection);
}
