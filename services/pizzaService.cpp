#include "pizzaService.h"
#include "toppingService.h"
using namespace std;

Pizza pizzaService::convertActivePizzaVector(vector<string> pizzaWords) {
  int numberOfLines = fo.countLines("data/menuPizzas.txt");
  vector<Topping> toppings;
  Pizza pizza;
  for(int i = 0; i < numberOfLines; i++) {
    Pizza potential = getMenuPizza(i);

    if(potential.getName() == pizzaWords[1]) {
      toppings = potential.getToppings();
    }
  }

  pizza.setToppings(toppings);
  pizza.setOrderID(stringfunc.stringToInt(pizzaWords[0]));
  pizza.setName(pizzaWords[1]);
  pizza.setBottomType(pizzaWords[2][0]);
  pizza.setSize(pizzaWords[3][0]);
  pizza.setPrice(stringfunc.stringToInt(pizzaWords[4]));
  pizza.setStoreID(stringfunc.stringToInt(pizzaWords[5]));

  pizza.setBaked((pizzaWords[6] == "baked"));
  pizza.setPaid((pizzaWords[7] == "paid"));
  pizza.setDelivered((pizzaWords[8] == "delivered"));

  return pizza;
}

void pizzaService::createAndAppendMenuPizza() {
  string builder = "";
  string name;
  int numberOfToppings;
  vector<Topping> toppings;

  cout << "Enter name of pizza: ";
  cin >> name;

  do {
    uf.clearScreen();
    cout << "Enter number of toppings: ";
    cin >> numberOfToppings;

    if(cin.fail()) {
      cin.clear();              //reset error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      numberOfToppings = -1;    //continue selection
    }
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

void pizzaService::listFromLocationActivePizzas(int locationID){
    int numPizzas = howManyActivePizzas();
    string location = stringfunc.intToString(locationID);

    for(unsigned int i = 0; i < numPizzas; i++){
        vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");
            if(words[5] == location){
                for(unsigned int i = 0; i < words.size(); i++){
                    cout << words.at(i) << " ";
                }
                cout << endl;
            }
    }
}

void pizzaService::saveCustomToppings(Pizza pizza){
    string ID = stringfunc.intToString(pizza.getOrderID());
    vector<Topping> toppings = pizza.getToppings();
    for(unsigned int i = 0; i < toppings.size(); i++){
        string price = stringfunc.intToString(toppings[i].getPrice());
        string builder = ID + " " + toppings[i].getName() + " " + price;
        fo.appendLineToFile(builder, "data/customPizzaToppings.txt");
    }
}

vector<Topping> pizzaService::getCustomToppings(Pizza pizza){
    int numProducts = fo.countLines("data/customPizzaToppings.txt");
    vector<Topping> toppings;
    for(unsigned int i = 0; i < numProducts; i++){
        vector<string> toppingFromFile = fo.getWordsFromLine(i, "data/customPizzaToppings.txt");
        int pizzaOrderID = pizza.getOrderID();
        int ID = stringfunc.stringToInt(toppingFromFile[0]);
        if(ID == pizzaOrderID){
          Topping topping(toppingFromFile[1], stringfunc.stringToInt(toppingFromFile[2]));
          toppings.push_back(topping);
        }
    }
    return toppings;
}

void pizzaService::listMenuPizzasWithIndices() {
  //we could use:
  //fo.printLinesWithIndices("data/menuPizzas.txt");
  //but that would also display the number of toppings
  //inside the selection which isn't all that exciting.
  //Let's customize this a bit more
  int lineCount = fo.countLines("data/menuPizzas.txt");

  //let's sacrifice speed for beauty
  int longestPizzaNameLength = 0;
  for(int i = 0; i < lineCount; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/menuPizzas.txt");
    if(words[0].length() > longestPizzaNameLength) {
      longestPizzaNameLength = words[0].length();
    }
  }

  for(int i = 0; i < lineCount; i++) {
      vector<string> words = fo.getWordsFromLine(i, "data/menuPizzas.txt");

      //padding for equal display length
      string extraSpaces = " ";
      for(int j = 0; j < (longestPizzaNameLength - words[0].length()); j++) {
        extraSpaces += " ";
      }

      cout << (i+1) << " -\t" << "| " << words[0] << extraSpaces << "|\t";
      for(int j = 2; j < words.size(); j++) {
        cout << words[j] << " ";
      }
      cout << endl;
  }
}

void pizzaService::listActiveWithIndicesForBakeryAndLocation(bool baked, int locationID) {
  int lineCount = fo.countLines("data/activePizzas.txt");
  int nof;    //number of fields/words per line

  //let's sacrifice speed for beauty
  int longestPizzaNameLength = 0;
  for(int i = 0; i < lineCount; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");
    if((words[1].length() > longestPizzaNameLength) && stringfunc.stringToInt(words[5]) == locationID) {
      longestPizzaNameLength = words[1].length();
      nof = words.size();
    }
  }

  int counter = 1;
  for(int i = 0; i < lineCount; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");

    //we know that baked is in 3rd position from right
    //so words.count - 3 is the index for baked

    //padding for equal display length
    string extraSpaces = " ";
    if(stringfunc.stringToInt(words[5]) == locationID) {
      for(int j = 0; j < (longestPizzaNameLength - words[1].length()); j++) {
        extraSpaces += " ";
      }
      if((baked && words[nof - 3] == "baked") || (!baked && words[nof - 3] == "unbaked")) {
        cout << counter << " -\t" << "| " << words[0] << "-";
        cout << words[1] << extraSpaces << "|\t";
        for(int j = 2; j < words.size(); j++) {
          cout << words[j] << " ";
        }
        cout << endl;
        counter++;
      }
    }
  }
}

int pizzaService::adjustBakerIndexForBaked(bool baked, int locationID, int pseudoIndex) {
  int lineCount = fo.countLines("data/activePizzas.txt");
  int adjustedIndex = 0;

  for(int i = 0; i < lineCount; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");
    if((baked && words[(words.size()) - 3] == "baked") || (!baked && words[(words.size()) -3] == "unbaked") ) {
      if(stringfunc.stringToInt(words[5]) == locationID) {
        pseudoIndex--;

        if(pseudoIndex == 0) {
          return adjustedIndex;
        }
      }
    }
    adjustedIndex++;
  }
}

void pizzaService::deleteMenuPizza() {

  int menuSize = howManyPizzasOnMenu();
  int selection = -1;

  while(selection < 1 || selection > menuSize) {
    listMenuPizzasWithIndices();
    cout << endl << "Select a pizza to delete from menu: ";
    cin >> selection;
    if(cin.fail()) {
      cin.clear();      //reset error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      selection = -1;   //set selection to continue
    }
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

int pizzaService::howManyActivePizzas() {
  return fo.countLines("data/activePizzas.txt");
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

//IMPORTANT!!!
//For this function to work the activePizzas.txt must have the
//last three fields be: baked, paid, delivered.
void pizzaService::setActivePizzaStatus(int index, string field, bool truthValue) {
  vector<string> words = fo.getWordsFromLine(index, "data/activePizzas.txt");
  int nof = words.size();     //number of fields


  if(field == "baked") {
    if(truthValue) {
      words[nof-3] = "baked";
    } else {
      words[nof-3] = "unbaked";
    }
  }

  if(field == "paid") {
    if(truthValue) {
      words[nof-2] = "paid";
    } else {
      words[nof-2] = "unpaid";
    }
  }

  if(field == "delivered") {
    if(truthValue && words[nof-3] == "baked" && words[nof-2] == "paid") {
      words[nof-1] = "delivered";
      //TODO make sure active pizza is stored in legacy file now!
    } else {
      cout << "ERROR: You cannot deliver a pizza that hasn't been ";

      if(words[nof-2] == "unpaid") {
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
