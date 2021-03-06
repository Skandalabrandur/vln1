#include "pizzaService.h"
#include "toppingService.h"
using namespace std;

//A reverse of a tostring()
//Input : A string vector representing a line from the menuPizza file
//Output: A limited pizza model
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

//Evoked from admin only.
//Menu pizzas are one of the building blocks of orders
void pizzaService::createAndAppendMenuPizza() {
  string builder = "";
  string name;
  int numberOfToppings;
  vector<Topping> toppings;

  cout << "Enter name of pizza (c to cancel): ";
  cin >> name;
  if(name != "c"){
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
          cout << "Select topping " << (i+1) << " of " << numberOfToppings << endl;
          topping_service.listToppingsWithIndex();
          cin >> selection;
        } while(selection < 1 || selection > howManyToppingsExist);

        Topping topping = topping_service.getToppingAt(selection - 1);
        toppings.push_back(topping);
      }

      builder += name + " ";
      builder += stringfunc.intToString(numberOfToppings) + " ";

      for(int i = 0; i < numberOfToppings; i++) {
        if(i == numberOfToppings - 1){
            builder += toppings[i].getName();
        }else{
            builder += toppings[i].getName() + " ";
        }
      }

      fo.appendLineToFile(builder, "data/menuPizzas.txt");
      uf.clearScreen();
      cout << "Menu pizza: \"" << builder << "\" created!" << endl;
    }
    cin.ignore();
    cin.get();
}

void pizzaService::listMenuPizzas() {
  //fo.printLines("data/menuPizzas.txt");
  vector<string> unProcessedlines = fo.getLinesFromFile("data/menuPizzas.txt");
  vector<string> lines;


  for(int i = 0; i < unProcessedlines.size(); i++) {
    vector<string> words = stringfunc.split(unProcessedlines.at(i));
    string builder = words.at(0);
    for(int j = 2; j < words.size(); j++) {
      builder += " " + words.at(j);
    }
    lines.push_back(builder);
  }

  vector<string> headers;
  headers.push_back("Name");
  headers.push_back("Toppings");

  uf.printItNice(lines, headers);
}

void pizzaService::listActivePizzas() {
  //fo.printLines("data/activePizzas.txt");
  vector<string> lines = fo.getLinesFromFile("data/activePizzas.txt");
  vector<string> headers;
  headers.push_back("OrderID");
  headers.push_back("Name");
  headers.push_back("Bottom");
  headers.push_back("BtmSize");
  headers.push_back("Price");
  headers.push_back("NrOfToppings");
  headers.push_back("Status");

  uf.printItNice(lines, headers);
}

//Abstracts the database for localized staff
void pizzaService::listFromLocationActivePizzas(int locationID){
    int lineCount = fo.countLines("data/activePizzas.txt");
    vector<string> lines;
    int counter = 1;

    for(int i = 0; i < lineCount; i++) {
        vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");

        if(stringfunc.stringToInt(words[5]) == locationID) {
          string builder = words[0];
          builder += " " + words[2];
          builder += " " + words[3];
          builder += " " + words[6];
          if(words[1] == "custom") {
            int orderID = stringfunc.stringToInt(words[0]);
            vector<Topping> toppings = getCustomToppings(orderID);

            for(int i = 0; i < toppings.size(); i++) {
              builder += " " + toppings[i].getName();
            }
          } else {
            builder += " " + words[1];
          }
          lines.push_back(builder);
          counter++;
        }
    }

    vector<string> headers;
    headers.push_back("OrderID");
    headers.push_back("Bottom");
    headers.push_back("BtmSize");
    headers.push_back("Bake Status");
    headers.push_back("Pizza Name");

    uf.printItNice(lines, headers);
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
 
 vector<Topping> pizzaService::getCustomToppings(int orderID){
     int numProducts = fo.countLines("data/customPizzaToppings.txt");
     vector<Topping> toppings;
     for(int i = 0; i < numProducts; i++){
         vector<string> toppingFromFile = fo.getWordsFromLine(i, "data/customPizzaToppings.txt");
         int ID = stringfunc.stringToInt(toppingFromFile[0]);
         if(ID == orderID){
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

//Abstracts the database for the bakers
void pizzaService::listActiveWithIndicesForBakeryAndLocation(bool baked, int locationID) {
  int lineCount = fo.countLines("data/activePizzas.txt");
  vector<string> lines;

  int counter = 1;
  for(int i = 0; i < lineCount; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");
      if(stringfunc.stringToInt(words[5]) == locationID) {


      if((baked && words[words.size() - 3] == "baked") || (!baked && words[words.size() - 3] == "unbaked")) {
        string builder = stringfunc.intToString(counter);
        builder += " " + words[0];
        builder += " " + words[2];
        builder += " " + words[3];
        builder += " " + words[6];
        if(words[1] == "custom") {
            int orderID = stringfunc.stringToInt(words[0]);
            vector<Topping> toppings = getCustomToppings(orderID);

            for(int i = 0; i < toppings.size(); i++) {
              builder += " " + toppings[i].getName();
            }
          } else {
            builder += " " + words[1];
          }

        lines.push_back(builder);
        counter++;
      }
    }
  }

  vector<string> headers;
  headers.push_back("SELECTION");
  headers.push_back("OrderID");
  headers.push_back("Bottom");
  headers.push_back("BtmSize");
  headers.push_back("Pizza Name");
  headers.push_back("Status");

  uf.printItNice(lines, headers);
}

//This function corrects a selection from an abstracted view.
//This is so that we can maintain a pleasant 1-indexed operation almost
//throughout the program
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

//A singular pizza is marked as baked by the baker
void pizzaService::markPizzaAsBakedByIndexAndLocation(int index, int locationID){
    int numPizzas = howManyActivePizzas();

    for(int i = 0; i < numPizzas; i++){
        vector<string> orderWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
        int location_id = stringfunc.stringToInt(orderWords.at(5));
        if(i == index && location_id == locationID){
            setActivePizzaStatus(i, "baked", true);
            break;
        }
    }
}

//Mistakes happen and therefore a baker is allowed to revert his changes
void pizzaService::markPizzaAsUNBakedByIndexAndLocation(int index, int locationID){
    int numPizzas = howManyActivePizzas();

    for(int i = 0; i < numPizzas; i++){
        vector<string> orderWords = fo.getWordsFromLine(i, "data/activePizzas.txt");
        int location_id = stringfunc.stringToInt(orderWords.at(5));
        if(i == index && location_id == locationID){
            setActivePizzaStatus(i, "baked", false);
            break;
        }
    }
}

//Returns the order id of a given active pizza
int pizzaService::getOrderIDForPizza(int index){
    vector<string> orderWords = fo.getWordsFromLine(index - 1, "data/activePizzas.txt");
    //orderID is at index 0 in line
    int orderID = stringfunc.stringToInt(orderWords.at(0));
    return orderID;
}


//Administrator
//Note: Will create inconsistencies if used when
//active pizzas still depend on this
//Legacy file does not matter
void pizzaService::deleteMenuPizza() {

  int menuSize = howManyPizzasOnMenu();
  int selection = -1;

  while(selection < 0 || selection > menuSize) {
    uf.clearScreen();
    listMenuPizzasWithIndices();
    cout <<  "Select a pizza to delete from menu (c to cancel): " << endl;
    cin >> selection;
    if(cin.fail()) {    //c er ekki int
      cin.clear();      //reset error flags
      //Don't dump input here
      //The buffer will contain '/n' and skip over the press Enter to continue
      //which is convenient for cancellation
      selection = 0;   //set selection for cancellation
    }
  }
  if(selection > 0){
    //Get this info before delete to show user later
    Pizza selectedPizza = getMenuPizza(selection-1);  //selection is 1-based

    vector<string> menuPizzaFile = fo.getLinesFromFile("data/menuPizzas.txt");

    //erase selection from the vector representing the file
    menuPizzaFile.erase(menuPizzaFile.begin() + (selection-1));

    //overwrite
    fo.writeFile(menuPizzaFile, "data/menuPizzas.txt");

    cout << "Deleted: " << selectedPizza.getName() << endl;
  }
}


int pizzaService::howManyPizzasOnMenu() {
  return fo.countLines("data/menuPizzas.txt");
}

//An active pizza is owned by an order
int pizzaService::howManyActivePizzas() {
  return fo.countLines("data/activePizzas.txt");
}

//Used for indexing purposes
int pizzaService::howManyActivePizzasForLocation(int locationID) {
  int numberOfLines = fo.countLines("data/activePizzas.txt");

  int counter = 0;
  for(int i = 0; i < numberOfLines; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");

    if(stringfunc.stringToInt(words.at(5)) == locationID) {
      counter++;
    }
  }

  return counter;
}

//Used for indexing purposes
int pizzaService::howManyActivePizzasForLocationAndStatus(int locationID, string status) {
  int numberOfLines = fo.countLines("data/activePizzas.txt");

  int counter = 0;
  int reverseIndex = 1;
  if(status == "baked" || status == "unbaked") {
    reverseIndex = 3;
  }
  if(status == "paid" || status == "unpaid") {
    reverseIndex = 2;
  }
  for(int i = 0; i < numberOfLines; i++) {
    vector<string> words = fo.getWordsFromLine(i, "data/activePizzas.txt");
    if(stringfunc.stringToInt(words.at(5)) == locationID) {
      if(status == words.at(words.size() - reverseIndex)) {
        counter++;
      }
    }
  }
  return counter;
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

  cout << "Pizza status: " << lineReplacement << endl;
}

//Checks the delivered status of a particularly chosen active pizza
bool pizzaService::isDelivered(int index) {
  vector<string> words = fo.getWordsFromLine(index, "data/activePizzas.txt");
  return (words[(words.size() - 1)] == "delivered");
}

void pizzaService::deletePizzas(vector<Pizza> pizzas) {
  vector<string> pizzaFile = fo.getLinesFromFile("data/activePizzas.txt");

  for(int i = 0; i < pizzas.size(); i++) {
    for(int j = 0; j < pizzaFile.size(); j++) {
      if(pizzas.at(i).toString(false) == pizzaFile.at(j)) {
        pizzaFile.erase(pizzaFile.begin() + j);
      }
    }
  }
}

//Removes by OrderID
//Note how a reset must take place for every deletion
//Vectors are bound to act up when they have elements deleted from them
void pizzaService::deleteActivePizzasWithOrderID(int orderID) {

  bool reachedEnd = false;
  while(!reachedEnd) {
    vector<string> pizzaFile = fo.getLinesFromFile("data/activePizzas.txt");
    for(int i = 0; i < pizzaFile.size(); i++) {
      if(pizzaFile.size() - 1 == i) {
        reachedEnd = true;
      }
      vector<string> words = stringfunc.split(pizzaFile.at(i));
      if(stringfunc.stringToInt(words.at(0)) == orderID) {
        pizzaFile.erase(pizzaFile.begin() + i);
        fo.writeFile(pizzaFile, "data/activePizzas.txt");
        break;
      }
    }
  }

}
