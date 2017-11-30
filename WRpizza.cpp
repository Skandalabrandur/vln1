#include "WRpizza.h"
#include <iostream>
#include <fstream>


using namespace std;

void WRpizza::saveNewPizza(AdminPizza& pizza) {
  ofstream fout;
  fout.open("files/pizzalist.txt", ios::app);
  fout << pizza;
  fout.close();
}

AdminPizza* WRpizza::retrievePizzas() {
  ifstream fin;
}

WRpizza::~WRpizza() {
  //destructor
}
