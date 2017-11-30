#include "WRpizza.h"
#include <iostream>
#include <fstream>


using namespace std;

void WRpizza::saveNewPizza(Pizza& pizza) {
  ofstream fout;
  fout.open("files/pizzalist.txt", ios::app);
  fout << pizza;
  fout.close();
}

Pizza* WRpizza::retrievePizzas() {
  ifstream fin;
}

WRpizza::~WRpizza() {
  //destructor
}
