#include "orderService.h"
using namespace std;

void orderService::createNewOrder() {
  string customer;
  int orderID = 1 + fo.countLines("data/orders.txt");

  uf.clearScreen();
  cout << "Creating order number " << orderID << endl << endl;
  cout << "Enter customer name: ";
  cin >> customer;

  Order order(customer, orderID);

  int numberOfPizzas;
  cout << "Number of pizzas for order: " << endl;

  cin >> numberOfPizzas;

  int numberOfMenuPizzas = pizza_service.howManyPizzasOnMenu();
  for(int i = 0; i < numberOfPizzas; i++) {
    int selection;

    do {
      uf.clearScreen();
      selection = -1;
      cout << "Select Pizza " << (i+1) << " of " << numberOfPizzas << endl;
      pizza_service.listMenuPizzasWithIndices();
      cin >> selection;
    } while(selection < 1 || selection > numberOfMenuPizzas);

      Pizza pizza = pizza_service.getMenuPizza(selection - 1);

      pizza.setOrderID(orderID);

      pizza_service.storeOrderPizza(pizza);
  }
  fo.appendLineToFile(order.toString(), "data/orders.txt");
  cout << "Placed an order of " << numberOfPizzas << " pizzas for customer ";
  cout << customer << endl;
  uf.pressEnter();
}
