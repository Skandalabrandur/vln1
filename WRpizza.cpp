#include "WRpizza.h"
#include <iostream>
#include <fstream>


using namespace std;

void WRpizza::saveNewPizza(AdminPizza& pizza) {
  ofstream fout;
  fout.open("files/pizzamenu.txt", ios::app);
  fout << pizza.pizzaName << " ";
  fout.close();
}

AdminPizza* WRpizza::retrievePizzas() {
    string pizza;
    ifstream fin;
    fin.open("files/pizzamenu.txt");
    if(fin.is_open()){
        int counter = 1;
        while(!fin.eof()){
            fin >> pizza;
            cout << counter << " - " << pizza << endl;
            counter++;
        }
        fin.close();
    }else{
        cout << "Ekki hægt að lesa úr skrá" << endl;
    }
}

WRpizza::~WRpizza() {
  //destructor
}
