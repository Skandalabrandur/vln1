#include "WRsalespizza.h"

WRsalespizza::WRsalespizza()
{

}

WRsalespizza::~WRsalespizza()
{

}

void saveNewPizza(SalesPizza& pizza){
  ofstream fout;
  fout.open("files/sales_pizzalist.txt", ios::app);
  fout << pizza;
  fout.close();
}

SalesPizza* WRsalespizza::retrievePizzas(){
    SalesPizza* salespizza = 0;

    ifstream fin;
    fin.open("files/sales_pizzalist.txt");

    if(fin.is_open()){
        fin.seekg(0, fin.end);
        int rec_count = fin.tellg() / sizeof(SalesPizza);
        fin.seekg(0, fin.beg);

        fin.read((char*)(salespizza), sizeof(SalesPizza) * rec_count);

        fin.close();

        for(int i = 0; i < rec_count; i++){
            cout << salespizza[i] << endl;
        }
    }
    else{
        cout << "Could not open file" << endl;
    }

    delete[] salespizza;
    return salespizza;
}
