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
            cout << "HOME/BAKER" << endl << endl;
            cout << "1 - LIST PIZZAS FOR YOUR PLACE" << endl;
            cout << "2 - LIST PIZZAS BY ORDERS" << endl;
            cout << "3 - MARK PIZZA AS BAKED" << endl;
            cout << "4 - MARK PIZZA AS UNBAKED" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "1234b"));

        userInput = tolower(userInput);

        if(userInput == '1') {
          if(vs.pizzasExistForLocationID(_locationID)) {
            uf.clearScreen();
            cout << "HOME/BAKER/LIST PIZZAS" << endl << endl;
            viewPizzas();
          } else {
            cout << "No pizzas exist for your location!" << endl;
            cout << "A good opportunity to relax :)" << endl;
            uf.pressEnter();
          }
        }

        if(userInput == '2') {
          if(vs.pizzasExistForLocationID(_locationID)) {
            uf.clearScreen();
            cout << "HOME/BAKER/LIST PIZZAS BY ORDERS" << endl << endl;
            //false to show all orders
            listByOrders(false);
          } else {
            cout << "No pizzas exist for your location!" << endl;
            cout << "A good opportunity to relax :)" << endl;
          }
          uf.pressEnter();
        }

        if(userInput == '3') {
          if(vs.pizzasExistForLocationID(_locationID)) {
              uf.clearScreen();
            cout << "HOME/BAKER/MARK BAKED" << endl << endl;
            selectAndMarkPizzaAsBaked();
          } else {
            cout << "No pizzas exist for your location!" << endl;
            cout << "A good opportunity to relax :)" << endl;
            uf.pressEnter();
          }
        }

        if(userInput == '4') {
          if(vs.pizzasExistForLocationID(_locationID)) {
              uf.clearScreen();
            cout << "HOME/BAKER/MARK UNBAKED" << endl << endl;
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
    cout << "Please select a pizza to mark as BAKED (c to cancel): ";
    cin >> index;

      if(cin.fail()) {
          cin.clear();    //clear error flags
          cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
          index = 0;     //select price to continue
      }
  }
  if(index != 0) {
  int orderID = pizza_service.getOrderIDForPizza(index);
    pizza_service.markPizzaAsBakedByOrderIDAndLocation(orderID, _locationID);
    uf.pressEnter();
  }
}

void bakerUI::selectAndMarkPizzaAsUnbaked() {
  int index = -1;
  while(index < 0 || index > pizza_service.howManyActivePizzas()) {
    pizza_service.listActiveWithIndicesForBakeryAndLocation(true, _locationID);
    cout << "Please select a pizza to mark as UNBAKED (c to cancel): ";
    cin >> index;

    if(cin.fail()) {
        cin.clear(); //clear error flags
        index = 0;   //appropriate quit condition
    }
  }
  if(index != 0) {
    //int adjustedIndex = pizza_service.adjustBakerIndexForBaked(true, _locationID, index);
    int orderID = pizza_service.getOrderIDForPizza(index);
    pizza_service.markPizzaAsUNBakedByOrderIDAndLocation(orderID, _locationID);
    uf.pressEnter();
  }
}

void bakerUI::listByOrders(bool isReady) {
    int choice = -1; //So the value is not 0
    int numOrders = order_service.howManyOrders();
    do{
        uf.clearScreen();
        order_service.listOrderFromLocationWithID(_locationID, isReady);
        cout << "Select an order for more info (c to cancel): ";
        cin >> choice;

        if(cin.fail()) {
            cin.clear();  //clear error flags
            choice = 0;   //appropriate quit condition
        }
        if(choice >= 1 && choice <= numOrders){
            uf.clearScreen();
            int orderID = order_service.getOrderID(choice);
            order_service.listSpecificOrderFromLocationWithInfo(orderID, _locationID);
            uf.pressEnter();
            uf.clearScreen();
        }
    }while((choice < 0) || (choice > numOrders));
}
