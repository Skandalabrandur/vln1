#include "WRtopping.h"
#include <iostream>
#include <fstream>

using namespace std;

void WRtopping::saveNewTopping(Topping topping) {

  ofstream fout;
  fout.open("files/toppinglist.txt");

    fout << topping << endl;

  fout.close();

}

/*
Topping* WRtopping::retriveToppings() {
  Topping* toppings;
  ifstream fin;
  fin.open("files/toppingList.txt");

  if(fin.is_open()) {

  } else {

  }
}
*/

void WRtopping::listToppings() {
  ifstream fin;
  fin.open("files/toppinglist.txt");
  if(fin.is_open()) {
    string line;
    while(!fin.eof()) {
      getline(fin, line);
      cout << line << endl;
    }
    fin.close();
  } else {
    cout << "ERROR: NO TOPPINGS FOUND!" << endl;
    cout << "Possible solution:" << endl;
    cout << "\tHave management create toppings!" << endl;
  }
}


WRtopping::~WRtopping() {
  //destructor
}
