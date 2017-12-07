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
      
      char size;
      char bottomType;
      cout << "Select Size: " << endl;
      cin >> size;
      cout << "Select Bottom: " << endl;
      cin >> bottomType;
      
      pizza.setSize(size);
      pizza.setBottomType(bottomType);
      pizza.setOrderID(orderID);
      pizza.setPrice(generatePrice(Pizza pizza));
      pizza_service.storeOrderPizza(pizza);
  }
  fo.appendLineToFile(order.toString(), "data/orders.txt");
  cout << "Placed an order of " << numberOfPizzas << " pizzas for customer ";
    cout << customer << endl;
  uf.pressEnter();
}

int orderService::generatePrice(Pizza pizza){
    //ATH Á EFTIR AÐ SETJA VALUE
    char size = pizza.getSize();
    char bottom = pizza.getBottomType();
    vector<char> toppings;
    bool isMenuPizza = true;
    int priceMenuPizza = 500;
    int classicBottomPrice = 600;
    int lightBottomPrice = 500;
    int panBottomPrice = 900;
    double sizeMultiplier = 1;
    int price = 0;

    if(size == 'm'){
        sizeMultiplier = 1.5;
    }
    if(size == 's'){
        sizeMultiplier = 2;
    }
    
    if(isMenuPizza){
        price += priceMenuPizza;
        if(bottom == 'p'){
            price = priceMenuPizza + panBottomPrice;
        }
        if(bottom == 'k'){
            price += sizeMultiplier * classicBottomPrice;
        }
        if(bottom == 'l'){
            price += sizeMultiplier * lightBottomPrice;
        }
        if(bottom == 'p'){
            price +=  panBottomPrice;
        }
    }
    //BÆTA VIÐ VERÐ Á TOPPINGS
    return price;
}
