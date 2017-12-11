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
  order.setLocationID(stringfunc.stringToInt(input[2]));

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

  cout << "Select location: " << endl;
  location_service.listLocationsWithIndex();
  if(location_service.howManyLocations() == 0) {
    cout << "No locations exist. Contact administrator!" << endl;
    uf.pressEnter();
    return;
  }
  int location;
  cin >> location;

  //Pick up or delivery
  bool pickUp;
  char choice = ' ';
  do{
      cout << "Select:" << endl;
      cout << "1 - Pick up" << endl;
      cout << "2 - Delivery" << endl;
      cin >> choice;
  }while(choice != '1' && choice != '2');

  if(choice == '1'){
    pickUp = true;
  }
  else{
    pickUp = false;
  }
  //Make the order
  Order order(customer, orderID, location, pickUp);

  string comment = "";
  cout << "Comment <enter for blank> " << endl;
  cin >> ws;
  getline(cin, comment);

  order.setComment(comment);

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

      char size;
      char bottomType;
      do {
        uf.clearScreen();
        cout << "For pizza " << (i+1) << " of " << numberOfPizzas << endl;

        cout << "Select Bottom (p)an/(l)ight/(c)lassic: ";
        cin >> bottomType;
        bottomType = tolower(bottomType);

        //g.r.f. að pönnupizza sé bara af einni stærð
        if(!(bottomType == 'p')) {
          cout << "Select Size (l)arge/(m)edium/(s)mall: ";
          cin >> size;
          size = tolower(size);
        } else {
          size = 'm';
        }
      } while(!(size == 'l' || size == 'm' || size == 's') &&
              !(bottomType == 'p' || bottomType == 'c' || bottomType == 'l'));

      pizza.setStoreID(location);
      pizza.setSize(size);
      pizza.setBottomType(bottomType);
      pizza.setOrderID(orderID);

      //Generate price for pizza on menu
      if(yn == 'y'){
        pizza.setPrice(generatePizzaPrice(pizza, true));
      }
      //Generate price for custom pizza
      else{
        pizza.setPrice(generatePizzaPrice(pizza, false));
      }

      pizza_service.storeOrderPizza(pizza);
  }

  //Additional products
  char addProducts;
  cout << "Do you want to add any products to your order? (y/n): ";
  cin >> addProducts;
  if(addProducts == 'y'){
    //TO DO: generate price for additional products
    cout << "Select products, press 0 to confirm: " << endl;
    additionalProduct_service.saveAdditionalProducts(orderID);
  }

  fo.appendLineToFile(order.toString(), "data/orders.txt");

  //if comment is not empty
  if( !(( order.getComment().getCommentString()).empty() ) ) {
    comment_service.writeComment(order.getComment());
  }

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

void orderService::listOrderOverviewWithIndicesForLocation(int locationID) {
  vector<string> orderLines = fo.getLinesFromFile("data/orders.txt");
  int nol = fo.countLines("data/orders.txt");
  int counter = 1;
  for(int i = 0; i < nol; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/orders.txt");
    if(stringfunc.stringToInt(words[2]) == locationID) {
      Order order = convertVector(words);
      cout << counter << " -\t" << order.getCustomer() << endl;
      counter++;
    }
  }
}

void orderService::listOrderFromLocationWithID(int locationID, bool isReady) {
  vector<string> orderLines = fo.getLinesFromFile("data/orders.txt");
  int nol = fo.countLines("data/orders.txt");
  for(int i = 0; i < nol; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/orders.txt");
    Order order = convertVector(words);
    if(order.getLocationID() == locationID){
        //If we only want show ready orders
        if(isReady){
            bool ready = true;
            vector<Pizza> orderPizzas = getPizzasFromOrderId(i + 1);
            for(int i = 0; i < orderPizzas.size(); i++) {
                if(!(orderPizzas[i].isBaked() && orderPizzas[i].isPaid())){
                    ready = false;
                }
            }
            if(ready){
                    cout << orderPizzas[i].getOrderID() << " -\t" << order.getCustomer() << endl;
            }
        }
        //Show all orders
        else{
            cout << order.getOrderID() << " -\t" << order.getCustomer() << endl;
        }
    }
  }
}

void orderService::listSpecificOrderFromLocationWithInfo(int order_id, int location_ID) {
  vector<Pizza> orderPizzas = getPizzasFromOrderId(order_id);
  string comment = comment_service.getCommentTextFromOrderID(order_id);
  if(!comment.empty()) {
    cout << "Comment: " << comment << endl << endl;
  }
  cout << "Pizzas: " << endl;
  for(int i = 0; i < orderPizzas.size(); i++) {
    if(orderPizzas[i].getStoreID() == location_ID){
        cout << orderPizzas[i].toString(false) << endl;
    }
  }
}

int orderService::howManyOrders() {
  return fo.countLines("data/orders.txt");
}

int orderService::getOrderID(int index){
    vector<string> orderWords;
    orderWords = fo.getWordsFromLine(index - 1, "data/orders.txt");
    //orderID is at index 1 in line
    int orderID;
    orderID = stringfunc.stringToInt(orderWords.at(1));
    return orderID;
}

void orderService::markPizzaAsPaidByOrderID(int orderID){
    int numPizzas = pizza_service.howManyActivePizzas();

    for(int i = 0; i < numPizzas; i++){
        vector<string> orderWords;
        orderWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
        int id = stringfunc.stringToInt(orderWords.at(0));
        if(id == orderID){
            pizza_service.setActivePizzaStatus(i, "paid", true);
        }
    }
}

void orderService::markPizzaAsDeliveredByOrderID(int orderID){
    int numPizzas = pizza_service.howManyActivePizzas();

    for(int i = 0; i < numPizzas; i++){
        vector<string> orderWords;
        orderWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
        int id = stringfunc.stringToInt(orderWords.at(0));
        if(id == orderID){
            pizza_service.setActivePizzaStatus(i, "delivered", true);
        }
    }
}

//This starts mattering when order numbers get really big
//It is a way to abstract the user from how high the orders are getting
int orderService::getOrderIdFromIndexSelection(int index) {
  vector<string> words = fo.getWordsFromLine(index, "data/orders.txt");
  return stringfunc.stringToInt(words[1]);
}

int orderService::getOrderIdFromIndexSelectionForLocation(int index, int locationID) {
  vector<string> lines = fo.getLinesFromFile("data/orders.txt");

  int counter = 0;
  for(int i = 0; i < lines.size(); i++) {
    vector<string> words = stringfunc.split(lines.at(i));
    if(stringfunc.stringToInt(words.at(2)) == locationID) {
      counter++;
    }
    if(counter == index) {
        return stringfunc.stringToInt(words[1]);
    }
  }

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

  string comment = comment_service.getCommentTextFromOrderID(order_id);
  if(!comment.empty()) {
    cout << "Comment: " << comment << endl << endl;
  }

  for(int i = 0; i < orderPizzas.size(); i++) {
    cout << orderPizzas[i].toString(false) << endl;
  }
}

int orderService::generatePizzaPrice(Pizza pizza, bool isMenuPizza){
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
    else if(size == 's'){
        sizeMultiplier = 1;
    }

    if(isMenuPizza){
        price += priceMenuPizza;
        if(bottom == 'p'){
            price = priceMenuPizza + panBottomPrice;
        }
        else if(bottom == 'c'){
            price += sizeMultiplier * classicBottomPrice;
        }
        else if(bottom == 'l'){
            price += sizeMultiplier * lightBottomPrice;
        }
    } else {
        price = 0;
        if(bottom == 'p'){
            price += panBottomPrice;
        }
        else if(bottom == 'c'){
            price += sizeMultiplier * classicBottomPrice;
        }
        else if(bottom == 'l'){
            price += sizeMultiplier * lightBottomPrice;
        }

        toppings = pizza.getToppings();
        for(unsigned int i = 0; i < toppings.size(); i++){
            price += toppings.at(i).getPrice();
        }

    }
    return price;
}

int orderService::getOrderPrice(Order order){
    int price = 0;
    int orderID = order.getOrderID();
    vector<Pizza> pizzas = getPizzasFromOrderId(orderID);
    for(unsigned int i = 0; i < pizzas.size(); i++){
        if(pizzas.at(i).getName() == "custom"){
            price += generatePizzaPrice(pizzas.at(i), false);
        }
        else{
            price += generatePizzaPrice(pizzas.at(i), true);
        }
    }

    vector<AdditionalProduct> products = additionalProduct_service.getSavedProductFromOrderID(orderID);
    for(unsigned int i = 0; i < products.size(); i++){
        price += products.at(i).getPrice();
    }

    return price;
}
