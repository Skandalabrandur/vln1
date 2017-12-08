#include "orderService.h"
#include "Pizza.h"
#include "locationService.h"
using namespace std;

//Returns an Order model
//Basically the opposite of Order::toString()
Order orderService::convertVector(vector<string> input) {
  //see generated data in orders.txt for reference
  Order order;

  order.setCustomer(input[0]);
  order.setOrderID(stringfunc.stringToInt(input[1]));

  vector<Pizza> pizzas = getPizzasFromOrderId(order.getOrderID());

  for(int i = 0; i < pizzas.size(); i++) {
    order.addPizza(pizzas[i]);
  }
  return order;
}

void orderService::createNewOrder() {
  string customer;
  int orderID = 1 + fo.countLines("data/orders.txt");

  uf.clearScreen();
  cout << "Creating order number " << orderID << endl << endl;
  cout << "Enter customer name: ";
  cin >> customer;

  Order order(customer, orderID);

  int numberOfPizzas;
  cout << "Number of pizzas for order: ";

  cin >> numberOfPizzas;

  int numberOfMenuPizzas = pizza_service.howManyPizzasOnMenu();
  for(int i = 0; i < numberOfPizzas; i++) {
      cout << "Pizza off menu? (y/n) " << endl;
      char yn;
      cin >> yn;
      Pizza pizza;
      if(yn == 'y'){
        int selection;
        do {
            uf.clearScreen();
            selection = -1;
            cout << "Select Pizza " << (i+1) << " of " << numberOfPizzas << endl;
            pizza_service.listMenuPizzasWithIndices();
            cin >> selection;
        } while(selection < 1 || selection > numberOfMenuPizzas);
        pizza = pizza_service.getMenuPizza(selection - 1);
      }else{
          cout << "Select toppings, press 0 to confirm: " << endl;
          pizza.setToppings();
      }

    int selection;

    do {
      uf.clearScreen();
      selection = -1;
      cout << "Select Pizza " << (i+1) << " of " << numberOfPizzas << endl;
      pizza_service.listMenuPizzasWithIndices();
      cin >> selection;
    } while(selection < 1 || selection > numberOfMenuPizzas);

      pizza = pizza_service.getMenuPizza(selection - 1);

      char size;
      char bottomType;
      do {
        uf.clearScreen();
        cout << "For pizza " << (i+1) << " of " << numberOfPizzas << endl;

        cout << "Select Bottom (p)an/(l)ight/(c)lassic: ";
        cin >> bottomType;
        bottomType = tolower(bottomType);

        //g.r.f. að pönnupizza sé bara af einni stærð?
        if(!(bottomType == 'p')) {
          cout << "Select Size (l)arge/(m)edium/(s)mall: ";
          cin >> size;
          size = tolower(size);
        } else {
          size = 'm';
        }
      } while(!(size == 'l' || size == 'm' || size == 's') &&
              !(bottomType == 'p' || bottomType == 'c' || bottomType == 'l'));

      cout << "Select store: " << endl;
      location_service.listLocationsWithIndex();
      int store;
      cin >> store;
      pizza.setStoreID(store);
      pizza.setSize(size);
      pizza.setBottomType(bottomType);
      pizza.setOrderID(orderID);

      //TODO allow a custom pizza to be made
      //  That would result in a call for:
      //    pizza.setPrice(generatePrice(pizza,false));
      pizza.setPrice(generatePrice(pizza, true));

      pizza_service.storeOrderPizza(pizza);
  }
  fo.appendLineToFile(order.toString(), "data/orders.txt");
  uf.clearScreen();
  cout << "Placed an order of " << numberOfPizzas << " pizzas for customer ";
    cout << customer << endl;
  uf.pressEnter();
}

void orderService::listOrderOverviewWithIndices() {
  vector<string> orderLines = fo.getLinesFromFile("data/orders.txt");
  int nol = fo.countLines("data/orders.txt");
  for(int i = 0; i < nol; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/orders.txt");
    Order order = convertVector(words);
    cout << (i+1) << " -\t" << order.getCustomer() << endl;
  }
}

int orderService::howManyOrders() {
  return fo.countLines("data/orders.txt");
}

int orderService::getOrderID(int index){
    int numOrder = howManyOrders();
    vector<string> orderWords;
    orderWords = fo.getWordsFromLine(index - 1, "data/orders.txt");
    //orderID is at index 1 in line
    int orderID;
    orderID = stringfunc.stringToInt(orderWords.at(1));
    return orderID;
}

void orderService::MarkPizzaAsPaidByOrderID(int OrderID){
    int numPizzas = pizza_service.howManyActivePizzas();

    for(int i = 0; i < numPizzas; i++){
        vector<string> orderWords;
        orderWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
        int id = stringfunc.stringToInt(orderWords.at(0));
        if(id == OrderID){
            pizza_service.setActivePizzaStatus(i, "paid", true);
        }
    }
}

//This starts mattering when order numbers get really big
//It is a way to abstract the user from how high the orders are getting
int orderService::getOrderIdFromIndexSelection(int index) {
  vector<string> words = fo.getWordsFromLine(index, "data/orders.txt");
  return stringfunc.stringToInt(words[1]);
}

vector<Pizza> orderService::getPizzasFromOrderId(int order_id) {
  vector<Pizza> pizzas;

  int nol = fo.countLines("data/activePizzas.txt");

  for(int i = 0; i < nol; i++) {
      vector<string> pizzaWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
      Pizza pizza = pizza_service.convertActivePizzaVector(pizzaWords);
      if (pizza.getOrderID() == order_id) {
        pizzas.push_back(pizza);
      }
  }
  return pizzas;
}

void orderService::listSpecificOrderWithInfo(int order_id) {
  vector<Pizza> orderPizzas = getPizzasFromOrderId(order_id);

  for(int i = 0; i < orderPizzas.size(); i++) {
    cout << orderPizzas[i].toString(false) << endl;
  }
}

int orderService::generatePrice(Pizza pizza, bool isMenuPizza){
    char size = pizza.getSize();
    char bottom = pizza.getBottomType();
    vector<Topping> toppings;
    int priceMenuPizza = 500;
    int classicBottomPrice = 600;
    int lightBottomPrice = 500;
    int panBottomPrice = 900;
    double sizeMultiplier = 2;
    int price = 0;

    if(size == 'm'){
        sizeMultiplier = 1.5;
    }
    if(size == 's'){
        sizeMultiplier = 1;
    }

    if(isMenuPizza){
        price += priceMenuPizza;
        if(bottom == 'p'){
            price = priceMenuPizza + panBottomPrice;
        }
        if(bottom == 'c'){
            price += sizeMultiplier * classicBottomPrice;
        }
        if(bottom == 'l'){
            price += sizeMultiplier * lightBottomPrice;
        }
    } else {

    }
    return price;
}
