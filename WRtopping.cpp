#include "WRtopping.h"
#include <iostream>
#include <fstream>

using namespace std;

void WRtopping::saveNewTopping(Topping topping) {

  ofstream fout;
  fout.open("files/toppinglist.txt", ios::app);

    fout << topping << endl;

  fout.close();

}

bool WRtopping::toppingsExist() {
  ifstream fin;
  bool exists;

  fin.open("files/toppinglist.txt");
  exists = fin.is_open();
  fin.close();

  return exists;
}

void WRtopping::selectTopping(int index, Topping& topping) {
  ifstream fin;
  index--; //Program is 1-indexed
  fin.open("files/toppinglist.txt");
  if(fin.is_open()) {
    int counter = 0;
    string line;
    while(!fin.eof()) {
      if(counter == index) {
        string name;
        int price;

        fin >> name;
        fin >> price;

        topping.setName(name);
        topping.setPrice(price);
      } else {
        getline(fin, line);
      }
      counter++;
    }
    fin.close();
  }
}

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

//Begs the question if listToppings() is now deprecated
int WRtopping::listAndCountToppings() {
  ifstream fin;
  fin.open("files/toppinglist.txt");
  int counter = 0;
  if(fin.is_open()) {
    string line;
    while(!fin.eof()) {
      getline(fin, line);
      counter++;
      //we need to check eof again after get line so that
      //we don't get a trailing line
      if(!fin.eof()) {
        cout << counter << "-\t" << line << endl;
      }
    }
    return counter;
  } else {
    cout << "ERROR: NO TOPPINGS FOUND!" << endl;
    cout << "Possible solution:" << endl;
    cout << "\tHave management create toppings!" << endl;
    return 0;
  }
}


WRtopping::~WRtopping() {
  //destructor
}
