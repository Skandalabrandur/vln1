#include "pizzaService.h"
#include "toppingService.h"
using namespace std;

void pizzaService::createAndAppendMenuPizza() {
  string builder = "";
  string name;
  int numberOfToppings;
  vector<Topping> toppings;


  uf.clearScreen();
  cout << "Enter name of pizza: ";
  cin >> name;

  do {
    uf.clearScreen();
    cout << "Enter number of toppings: ";
    cin >> numberOfToppings;
  } while(numberOfToppings <= 0);

  int howManyToppingsExist = fo.countLines("data/toppings.txt");

  for(int i = 0; i < numberOfToppings; i++) {
    int selection;

    do {
      uf.clearScreen();
      selection = -1;
      cout << "Select topping!" << endl;
      topping_service.listToppingsWithIndex();
      cin >> selection;
    } while(selection < 1 || selection > howManyToppingsExist);

    Topping topping = topping_service.getToppingAt(selection - 1);
    toppings.push_back(topping);
  }

  builder += name + " ";
  builder += stringfunc.intToString(numberOfToppings) + " ";

  int totalPrice = 0;
  for(int i = 0; i < numberOfToppings; i++) {
    builder += toppings[i].getName() + " ";
    totalPrice += toppings[i].getPrice();
  }

  builder += stringfunc.intToString(totalPrice);

  fo.appendLineToFile(builder, "data/menuPizzas.txt");
  uf.clearScreen();
  cout << "Menu pizza: \"" << builder << "\" created!" << endl;
  uf.pressEnter();
}

void pizzaService::listMenuPizzas() {
  fo.printLines("data/menuPizzas.txt");
}

void pizzaService::listMenuPizzasWithIndices() {
  //we could use:
  //fo.printLinesWithIndices("data/menuPizzas.txt");
  //but that would also display the number of toppings
  //inside the selection which isn't all that
  //exciting.
  //Let's customize this a bit more
  int lineCount = fo.countLines("data/menuPizzas.txt");

  for(int i = 0; i < lineCount; i++) {
      vector<string> words = fo.getWordsFromLine(i, "data/menuPizzas.txt");
      cout << (i+1) << " - " << "██ " << words[0] << " ██\t";
      for(int i = 2; i < words.size(); i++) {
        cout << words[i] << " ";
      }
      cout << endl;
  }
}

int pizzaService::howManyPizzasOnMenu() {
  return fo.countLines("data/menuPizzas.txt");
}

Pizza pizzaService::getMenuPizza(int index) {
  vector<string> words = fo.getWordsFromLine(index, "data/menuPizzas.txt");

  string name = words[0];
  int numberOfToppings = stringfunc.stringToInt(words[1]);

  vector<Topping> toppings;

  for(int i = 0; i < numberOfToppings; i ++) {
    string name = words[i+2];
    Topping topping = topping_service.lookupTopping(name);
    toppings.push_back(topping);
  }

  Pizza pizza(name, toppings, stringfunc.stringToInt(words[words.size() - 1]));

  return pizza;

}

void pizzaService::storeOrderPizza(Pizza pizza) {
  fo.appendLineToFile(pizza.toString(false), "data/activePizzas.txt");
}
