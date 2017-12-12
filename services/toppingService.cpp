#include "toppingService.h"
using namespace std;

Topping toppingService::getToppingAt(int index) {
  vector<string> toppingFromFile = fo.getWordsFromLine(index, "data/toppings.txt");
  Topping topping(toppingFromFile[0], stringfunc.stringToInt(toppingFromFile[1]));

  return topping;
}

//Lists all toppings without indices
void toppingService::listToppings() {
  fo.printLines("data/toppings.txt");
}

//Useful for selections
//Note... this is not zero-based but one-based indexing.
void toppingService::listToppingsWithIndex() {
  fo.printLinesWithIndices("data/toppings.txt");
}

//Creates a new topping from the admin menu.
//Not inteded for use out of admin menu.
void toppingService::createNewTopping() {
  string name;
  int price;

  uf.clearScreen();
  cout << "Enter topping name: ";
  cin >> name;

  do {
    uf.clearScreen();
    cout << "Enter topping price: ";
    cin >> price;

    if(cin.fail()) {
      cin.clear();    //clear error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      price = -1;     //select price to continue
    }
  } while (price < 0);


  Topping topping(name, price);
  fo.appendLineToFile(topping.toString(), "data/toppings.txt");

  uf.clearScreen();
  cout << "Topping: \"" << topping.toString() << "\" created!" << endl;
  uf.pressEnter();
}

//Returns a topping object that matches name EXACTLY
Topping toppingService::lookupTopping(string name) {
  int lineCount = fo.countLines("data/toppings.txt");

  for(int i = 0; i < lineCount; i++) {
    vector<string> words;
    words = fo.getWordsFromLine(i, "data/toppings.txt");

    if(words[0] == name) {
      //creates the topping with the topping(name, price) constructor
      Topping topping(words[0], stringfunc.stringToInt(words[1]));
      return topping;
    }
  }
}

int toppingService::howManyToppings() {
  return fo.countLines("data/toppings.txt");
}

void toppingService::deleteTopping() {
  int howManyToppingsExist = howManyToppings();
  int selection = -1;

  while(selection < 1 || selection > howManyToppingsExist) {
    uf.clearScreen();
    listToppingsWithIndex();
    cout << endl << "Select a topping to delete: ";
    cin >> selection;
    if(cin.fail()) {
      cin.clear();      //reset error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      selection = -1;   //set selection to continue
    }
  }
  //Get this info before delete to show user later
  Topping selectedTopping = getToppingAt(selection-1);  //selection is 1-based

  vector<string> toppingFile = fo.getLinesFromFile("data/toppings.txt");

  //erase selection from the vector representing the file
  //file is 0-indexed, selection is 1-indexed
  toppingFile.erase(toppingFile.begin() + (selection-1));

  //overwrite
  fo.writeFile(toppingFile, "data/toppings.txt");

  cout << "Deleted: " << selectedTopping.getName() << endl;
}
