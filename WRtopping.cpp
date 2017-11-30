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

WRtopping::~WRtopping() {
  //destructor
}
