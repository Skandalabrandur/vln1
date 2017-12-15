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

//Returns a full Order model from file at the chosen index
Order orderService::getOrderAt(int index) {
  vector<string> orders = fo.getLinesFromFile("data/orders.txt");
  vector<string> orderWords = stringfunc.split(orders.at(index));
  return convertVector(orderWords);
}

//This function is the big one
//When an order is created, everything is funneled into it since
//OrderID is used as a unique identifier
void orderService::createNewOrder() {
  string customer;
  int orderID = 1 + fo.countLines("data/orders.txt");

  //to keep orderID unique, we need to keep tabs of how many orders
  //have been before
  if(vs.legacyFileExists()) {
    vector<string> lines = fo.getLinesFromFile("data/legacy.txt");

    for(int i = 0; i < lines.size(); i++) {
      if(lines.at(i)[0] != '\t') {
        orderID++;
      }
    }
  }

  cout << "Creating order number " << orderID << endl << endl;
    cout << "Enter customer name (c to cancel): ";
  cin >> customer;
    if(customer != "c"){

  cout << endl << "Select location: " << endl;
  location_service.listLocationsWithIndex();

  int location = 0;
  do {
      uf.prompt();
    cin >> location;

    if(cin.fail()) {
      cin.clear();    //reset error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      location = 0;   //set location to continue loop
    }
  } while(location < 1 || location > location_service.howManyLocations());

  //Pick up or delivery
  bool pickUp;
  int choice = 0;
  do{
      cout << endl << "Select:" << endl;
      cout << "1 - Pick up" << endl;
      cout << "2 - Delivery" << endl;
      cin >> choice;

      if(cin.fail()) {
        cin.clear();    //clear error flags
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
        choice = 0;     //set choice to continue loop
      }
  } while(choice != 1 && choice != 2);

  pickUp = (choice == 1);
  //Make the order
  Order order(customer, orderID, location, pickUp);

  cout << endl << "Include comment? (y/n)" << endl;
  char commentSelection = ' ';
  do {
    cin >> commentSelection;
  } while(!uf.goodInput(commentSelection, "yn"));

  commentSelection = tolower(commentSelection);

  if(commentSelection == 'y') {
    string comment = "";
    cout << endl << "Comment: ";
    cin >> ws;  //flush whitespace and \n in cin buffer before getline()
    getline(cin, comment);
    order.setComment(comment);
  }


  int numberOfPizzas;
  cout << endl << "Number of pizzas for order: ";

  do {
    cin >> numberOfPizzas;

    if(cin.fail()) {
      cin.clear();          //reset error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      numberOfPizzas = -1;  //set numberOfPizzas to continue loop
    }
  } while(numberOfPizzas < 1);
  int numberOfMenuPizzas = pizza_service.howManyPizzasOnMenu();
  for(int i = 0; i < numberOfPizzas; i++) {
    Pizza pizza;
    char yn;
    bool legitChoice;
    do {
        uf.clearScreen();
        cout << endl << "Pizza number " << (i  + 1) << " off menu? (y/n) " << endl;
        cin >> yn;
        legitChoice = false;

        pizza.setOrderID(orderID);
        yn = tolower(yn);
        legitChoice = (yn == 'y' && vs.menuPizzasExist()) || (yn == 'n');
        if(!legitChoice) {
            cout << "No menu pizzas exist." << endl;
        }
    } while(!legitChoice);
    if(yn == 'y') {
    int selection;
        do {
            uf.clearScreen();
            selection = -1;
            cout << "Select Pizza " << (i+1) << " of " << numberOfPizzas << endl;
            pizza_service.listMenuPizzasWithIndices();
            cin >> selection;

            if(cin.fail()) {
              cin.clear();      //reset error flags
              cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
              selection = -1;   //set selection to continue loop
            }
        } while(selection < 1 || selection > numberOfMenuPizzas);
        pizza = pizza_service.getMenuPizza(selection - 1);
     } else {
        cout << "Select toppings, press 0 to confirm: " << endl;
        pizza.setCustomToppings();
        pizza_service.saveCustomToppings(pizza);
    }

      char size;
      char bottomType;
      bool legit = false;
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

        legit = (bottomType == 'p') || (bottomType == 'l') || (bottomType == 'c');
        legit = legit && ((size == 'l') || (size == 'm') || (size=='s'));
      } while(!legit);

      pizza.setOrderID(orderID);
      pizza.setStoreID(location);
      pizza.setSize(size);
      pizza.setBottomType(bottomType);

      //Generate price for pizza on menu
      if(yn == 'y') {
        pizza.setPrice(generatePizzaPrice(pizza, true));
      } else {
        //generate custom pizza
        pizza.setPrice(generatePizzaPrice(pizza, false));
      }

      pizza_service.storeOrderPizza(pizza);
  }
  if(vs.addProductsExist()) {
    //Additional products
    char addProducts;
    uf.clearScreen();
    cout << "Do you want to add any products to your order? (y/n): ";
    cin >> addProducts;
    if(addProducts == 'y'){
      //TO DO: generate price for additional products
      cout << "Select products, press 0 to confirm: " << endl;
      additionalProduct_service.saveAdditionalProducts(orderID);
    }
  }

  int orderPrice = getOrderPrice(orderID);

  fo.appendLineToFile(order.toString(), "data/orders.txt");

  //if comment is not empty
  if( !(( order.getComment().getCommentString()).empty() ) ) {
    comment_service.writeComment(order.getComment());
  }

  uf.clearScreen();
  cout << "Placed an order of " << numberOfPizzas << " pizzas for customer ";
  cout << customer << ". Price: " << orderPrice <<  endl;
    }
}

//For neat interfaces:
//Only displays an abstracted number (instead of OrderID) and a customer name
void orderService::listOrderOverviewWithIndices() {
  vector<string> orderLines = fo.getLinesFromFile("data/orders.txt");
  int nol = fo.countLines("data/orders.txt");
  for(int i = 0; i < nol; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/orders.txt");
    Order order = convertVector(words);
    cout << (i+1) << " -\t" << order.getCustomer() << endl;
  }
}

//Only displays an abstracted number (instead of OrderID) but also has
//the caveat that a locationID be set. This abstracts the database further
//for localized staff
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

//Numbered list of customer names whose orders are ready
void orderService::listOrderFromLocationWithID(int locationID, bool isReady) {
  vector<string> orderLines = fo.getLinesFromFile("data/orders.txt");
  int nol = fo.countLines("data/orders.txt");
  int counter = 0;
  for(int i = 0; i < nol; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/orders.txt");
    Order order = convertVector(words);
    int orderID = order.getOrderID();
    if(order.getLocationID() == locationID){
        counter++;
        //If we only want show ready orders
        if(isReady){
            bool ready = true;
            vector<Pizza> orderPizzas = getPizzasFromOrderId(orderID);
            for(int i = 0; i < orderPizzas.size(); i++) {
                if(!(orderPizzas[i].isBaked())){
                    ready = false;
                }
            }
            if(ready){
                cout << counter << " -\t" << order.getCustomer() << endl;
            }
        }
        //Show all orders
        else{
            cout << counter << " -\t" << order.getCustomer() << endl;
        }
    }
  }
}

//Returns number of active orders from a location (legacy file is always excluded from logic)
//except when generating the unique OrderID
int orderService::countOrdersFromLocationWithID(int locationID) {
  int counter = 0;
  int numLines = fo.countLines("data/orders.txt");
  for(int i = 0; i < numLines; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/orders.txt");
    Order order = convertVector(words);
    if(order.getLocationID() == locationID){
        counter ++;
    }
  }
  return counter;
}

//Brings up a fully detailed view of how data is actually stored in the database for orders
void orderService::listSpecificOrderFromLocationWithInfo(int order_id, int location_ID) {
  vector<Pizza> orderPizzas = getPizzasFromOrderId(order_id);
  string comment = comment_service.getCommentTextFromOrderID(order_id);
  if(!comment.empty()) {
    cout << "Comment: " << comment << endl << endl;
  }
  if(!orderPizzas.empty()){
    cout << "Pizzas: " << endl;
  }
  for(int i = 0; i < orderPizzas.size(); i++) {
    if(orderPizzas[i].getStoreID() == location_ID){
        cout << orderPizzas[i].toString(false) << endl;
    }
  }
}

//Brings up full details of an order, but makes it nice looking
void orderService::deliveryListSpecificOrderFromLocationWithInfo(int order_id, int location_ID) {
    string comment = comment_service.getCommentTextFromOrderID(order_id);
    if(!comment.empty()) {
        cout << "Comment: " << comment << endl << endl;
    }

    vector<Pizza> orderPizzas = getPizzasFromOrderId(order_id);
    vector<string> pizzas;
    for(int i = 0; i < orderPizzas.size(); i++) {
        //if(orderPizzas[i].getStoreID() == location_ID){
            pizzas.push_back(orderPizzas[i].toString(false));
        //}
    }

    vector<string> pizzasHeaders;
    pizzasHeaders.push_back("OrderID");
    pizzasHeaders.push_back("Pizza Name");
    pizzasHeaders.push_back("Bottom");
    pizzasHeaders.push_back("Size");
    pizzasHeaders.push_back("Price");
    pizzasHeaders.push_back("LocationID");
    pizzasHeaders.push_back("Status...");
    uf.printItNice(pizzas, pizzasHeaders);
    cout << endl << endl << "------------------------------" << endl << endl;

    vector<AdditionalProduct> orderProducts = additionalProduct_service.getSavedProductFromOrderID(order_id);
    vector<string> products;
    for(int i = 0; i < orderProducts.size(); i++) {
        products.push_back(orderProducts.at(i).toString());
    }

    vector<string> productsHeaders;
    productsHeaders.push_back("Name");
    productsHeaders.push_back("Price");
    uf.printItNice(products, productsHeaders);

    cout << endl << "|Total Price  | " << getOrderPrice(order_id) << endl;
}

//Caution: Does not count inactive orders.
int orderService::howManyOrders() {
  return fo.countLines("data/orders.txt");
}

//Counts how many orders are for a specific LocationID
//Caution: Does not count inactive orders.
int orderService::howManyOrdersForLocation(int locationID) {
  int numberOfLines = fo.countLines("data/orders.txt");
  int counter = 0;
  for(int i = 1; i <= numberOfLines; i++) {
    if(locationID == getOrderLocationID(i)) {
      counter++;
    }
  }
  return counter;
}

//A 1-indexed getter for retrieving the unique OrderID
int orderService::getOrderID(int index){
    vector<string> orderWords = fo.getWordsFromLine(index - 1, "data/orders.txt");
    //orderID is at index 1 in line
    int orderID = stringfunc.stringToInt(orderWords.at(1));
    return orderID;
}

//A 1-indexed getter for retrieving a locationID
int orderService::getOrderLocationID(int index){
    vector<string> orderWords;
    orderWords = fo.getWordsFromLine(index - 1, "data/orders.txt");
    //orderID is at index 1 in line
    int locationID;
    locationID = stringfunc.stringToInt(orderWords.at(2));
    return locationID;
}

//Caution: Marks multiple pizzas
void orderService::markPizzaAsPaidByOrderID(int orderID) {
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

//Caution: Marks multiple pizzas
void orderService::markPizzaAsPaidByOrderIDAndLocation(int orderID, int locationID){
    int numPizzas = pizza_service.howManyActivePizzas();

    for(int i = 0; i < numPizzas; i++){
        vector<string> orderWords;
        orderWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
        int id = stringfunc.stringToInt(orderWords.at(0));
        int location_id = stringfunc.stringToInt(orderWords.at(5));
        if(id == orderID && location_id == locationID){
            pizza_service.setActivePizzaStatus(i, "paid", true);
        }
    }
}

//Caution: marks multiple pizzas
void orderService::markPizzaAsDeliveredByOrderIDAndLocation(int orderID, int locationID){
    int numPizzas = pizza_service.howManyActivePizzas();
    int customerPizzas = 0;
    int customerPizzasDelivered = 0;
    for(int i = 0; i < numPizzas; i++){
        vector<string> orderWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
        int id = stringfunc.stringToInt(orderWords.at(0));
        int location_id = stringfunc.stringToInt(orderWords.at(5));
        if(id == orderID && location_id == locationID){
            customerPizzas++;
            pizza_service.setActivePizzaStatus(i, "delivered", true);
            if(pizza_service.isDelivered(i)) {
              customerPizzasDelivered++;
            }
        }
    }
    if((customerPizzas == customerPizzasDelivered) && (customerPizzas > 0)) {
      moveToLegacyFile(orderID);
    }
}

//This starts mattering when order numbers get really big
//It is a way to abstract the user from how high the orders are getting
int orderService::getOrderIdFromIndexSelection(int index) {
  vector<string> words = fo.getWordsFromLine(index, "data/orders.txt");
  return stringfunc.stringToInt(words[1]);
}

//Adjusts an abstracted selection with regards to location.
//This is so that we can keep selections 1-indexed and correctly numbered, no matter
//the order ID.
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

//Returns a list of pizzas for a given unique orderID
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

//A detailed nice-i-fied printing of how data is stored in the database
void orderService::listSpecificOrderWithInfo(int order_id) {
  vector<Pizza> orderPizzas = getPizzasFromOrderId(order_id);

  string comment = comment_service.getCommentTextFromOrderID(order_id);
  if(!comment.empty()) {
    cout << "Comment: " << comment << endl;
    cout << endl << "------------------------------" << endl << endl;
  }
  vector<string> pizzas;
  for(int i = 0; i < orderPizzas.size(); i++) {
    pizzas.push_back(orderPizzas[i].toString(false));
  }
  vector<string> pizzasHeaders;
  pizzasHeaders.push_back("OrderID");
  pizzasHeaders.push_back("Pizza Name");
  pizzasHeaders.push_back("Bottom");
  pizzasHeaders.push_back("Size");
  pizzasHeaders.push_back("Price");
  pizzasHeaders.push_back("LocationID");
  pizzasHeaders.push_back("Status...");
  uf.printItNice(pizzas, pizzasHeaders);
  cout << endl << endl << "------------------------------" << endl << endl;


  vector<AdditionalProduct> orderProducts = additionalProduct_service.getSavedProductFromOrderID(order_id);
  vector<string> products;
  if(orderProducts.size() > 0) {
    for(int i = 0; i < orderProducts.size(); i++) {
      products.push_back(orderProducts.at(i).toString());
    }

    vector<string> productsHeaders;
    productsHeaders.push_back("Name");
    productsHeaders.push_back("Price");
    uf.printItNice(products, productsHeaders);

    cout << endl << "|Total Price  | " << getOrderPrice(order_id) << endl;
  }
}

//TODO: implement toppings
int orderService::generatePizzaPrice(Pizza pizza, bool isMenuPizza){
    char size = pizza.getSize();
    char bottom = pizza.getBottomType();
    int orderID = pizza.getOrderID();
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

    if(isMenuPizza) {
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
        if(bottom == 'p') {
            price += panBottomPrice;
        } else if (bottom == 'c') {
            price += sizeMultiplier * classicBottomPrice;
        } else if (bottom == 'l') {
            price += sizeMultiplier * lightBottomPrice;
        }

        toppings = pizza_service.getCustomToppings(orderID);
        for(unsigned int i = 0; i < toppings.size(); i++) {
            price += toppings.at(i).getPrice();
        }
    }
    return price;
}

int orderService::getOrderPrice(int orderID){
    int price = 0;
    //int orderID = order.getOrderID();
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

//removes a specific order from the order database
void orderService::deleteOrderWithOrderID(int orderID) {
  vector<string> ordersFile = fo.getLinesFromFile("data/orders.txt");
  for(int i = 0; i < ordersFile.size(); i++) {
      if(getOrderID(i+1) == orderID) {
        ordersFile.erase(ordersFile.begin() + i);
      }
      vector<Pizza> pizzas = getPizzasFromOrderId(orderID);
      pizza_service.deletePizzas(pizzas);
  }

  fo.writeFile(ordersFile, "data/orders.txt");
}

//Gathers and moves all relevant orderID files to a legacyFile when an
//order is delivered
void orderService::moveToLegacyFile(int orderID) {
  vector<string> ordersFile = fo.getLinesFromFile("data/orders.txt");
  for(int i = 0; i < ordersFile.size(); i++) {

    if(getOrderID(i+1) == orderID) {
      fo.appendLineToFile(ordersFile.at(i) + ": " + comment_service.getCommentTextFromOrderID(orderID), "data/legacy.txt");
      vector<Pizza> pizzas = getPizzasFromOrderId(orderID);

      for(int j = 0; j < pizzas.size(); j++) {
        fo.appendLineToFile("\t" + pizzas.at(j).toString(true), "data/legacy.txt");
      }

      fo.appendLineToFile("", "data/legacy.txt"); //make order line separated
    }
  }

  //once moved, delete from relevant files
  deleteOrderWithOrderID(orderID);
  pizza_service.deleteActivePizzasWithOrderID(orderID);

}

void orderService::printLegacyFile() {
  fo.printLines("data/legacy.txt");
}
