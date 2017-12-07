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

void pizzaService::listActivePizzas() {
  fo.printLines("data/activePizzas.txt");
}

void pizzaService::listMenuPizzasWithIndices() {
  //we could use:
  //fo.printLinesWithIndices("data/menuPizzas.txt");
  //but that would also display the number of toppings
  //inside the selection which isn't all that
  //exciting.
  //Let's customize this a bit more
  int lineCount = fo.countLines("data/menuPizzas.txt");

  //let's sacrifice speed for beauty
  int longestPizzaNameLength = 0;
  for(int i = 0; i < lineCount; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/menuPizzas.txt");
    if(words[0].size() > longestPizzaNameLength) {
      longestPizzaNameLength = words[0].size();
    }
  }

  for(int i = 0; i < lineCount; i++) {
      vector<string> words = fo.getWordsFromLine(i, "data/menuPizzas.txt");

      //padding for equal display length
      string extraSpaces = " ";
      for(int i = 0; i < (longestPizzaNameLength - words[0].size()); i++) {
        extraSpaces += " ";
      }

      cout << (i+1) << " - " << "| " << words[0] << extraSpaces << "|\t";
      for(int i = 2; i < words.size(); i++) {
        cout << words[i] << " ";
      }
      cout << endl;
  }
}

void pizzaService::listActivePizzasWithIndices() {
  int lineCount = fo.countLines("data/activePizzas.txt");

  //let's sacrifice speed for beauty
  int longestPizzaNameLength = 0;
  for(int i = 0; i < lineCount; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");
    if(words[0].size() > longestPizzaNameLength) {
      longestPizzaNameLength = words[1].size();
    }
  }

  for(int i = 0; i < lineCount; i++) {
      vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");

      //padding for equal display length
      string extraSpaces = " ";
      for(int i = 0; i < (longestPizzaNameLength - words[1].size()); i++) {
        extraSpaces += " ";
      }

      cout << (i+1) << " - " << "| " << words[0] << "-";
      cout << words[1] << extraSpaces << "|\t";
      for(int i = 2; i < words.size(); i++) {
        cout << words[i] << " ";
      }
      cout << endl;
  }
}

void pizzaService::deleteMenuPizza() {

  int menuSize = howManyPizzasOnMenu();
  int selection = -1;

  while(selection < 1 || selection > menuSize) {
    //uf.clearScreen()
    listMenuPizzasWithIndices();
    cout << endl << "Select a pizza to delete from menu: ";
    cin >> selection;
  }
  //Get this info before delete to show user later
  Pizza selectedPizza = getMenuPizza(selection-1);  //selection is 1-based

  vector<string> menuPizzaFile = fo.getLinesFromFile("data/menuPizzas.txt");

  //erase selection from the vector representing the file
  menuPizzaFile.erase(menuPizzaFile.begin() + (selection-1));

  //overwrite
  fo.writeFile(menuPizzaFile, "data/menuPizzas.txt");

  cout << "Deleted: " << selectedPizza.getName() << endl;
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

void pizzaService::setActivePizzaStatus(int index, string field, bool truthValue) {
  vector<string> words = fo.getWordsFromLine(index, "data/activePizzas.txt");

  if(field == "baked") {
    if(truthValue) {
      words[3] = "baked";
    } else {
      words[3] = "unbaked";
    }
  }

  if(field == "paid") {
    if(truthValue) {
      words[4] = "paid";
    } else {
      words[4] = "unpaid";
    }
  }

  if(field == "delivered") {
    if(truthValue && words[3] == "baked" && words[4] == "paid") {
      words[5] = "delivered";
      //TODO make sure active pizza is stored in legacy file now!
    } else {
      cout << "ERROR: You cannot deliver a pizza that hasn't been ";

      if(words[4] == "unpaid") {
        cout << "paid" << endl;
      } else {
        cout << "baked" << endl;
      }
    }
  }

  string lineReplacement = words[0];

  for(int i = 1; i < words.size(); i++) {
    lineReplacement += " " + words[i];    //space first => no trailing spaces
  }

  vector<string> lines = fo.getLinesFromFile("data/activePizzas.txt");

  lines[index] = lineReplacement;

  fo.writeFile(lines, "data/activePizzas.txt");

  cout << "New pizza status: " << lineReplacement << endl;
}
