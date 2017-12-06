#include "toppingService.h"
using namespace std;

Topping toppingService::getToppingAt(int index) {
  vector<string> toppingFromFile = fo.getWordsFromLine(index, "data/toppings.txt");
  Topping topping(toppingFromFile[0], stringfunc.stringToInt(toppingFromFile[1]));

  return topping;
}

void toppingService::listToppings() {
  fo.printLines("data/toppings.txt");
}

void toppingService::listToppingsWithIndex() {
  fo.printLinesWithIndices("data/toppings.txt");
}

void toppingService::createNewTopping() {
  string name;
  int price;

  uf.clearScreen();
  cout << "Enter topping name: ";
  cin >> name;

  uf.clearScreen();
  cout << "Enter topping price: ";
  cin >> price;

  Topping topping(name, price);
  fo.appendLineToFile(topping.toString(), "data/toppings.txt");

  uf.clearScreen();
  cout << "Topping: \"" << topping.toString() << "\" created!" << endl;
  uf.pressEnter();
}

Topping toppingService::lookupTopping(string name) {
  int lineCount = fo.countLines("data/toppings.txt");

  for(int i = 0; i < lineCount; i++) {
    vector<string> words;
    words = fo.getWordsFromLine(i, "data/toppings.txt");

    if(words[0] == name) {
      Topping topping(words[0], stringfunc.stringToInt(words[1]));
      return topping;
    }
  }
}
