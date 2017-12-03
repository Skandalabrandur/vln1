//
//  UIsales.cpp
//
//
//  Created by Hlynur Hólm Hauksson on 30/11/2017.
//

#include "UIsales.h"
#include "SalesPizza.h"
#include <iostream>
#include <fstream>
using namespace std;

void UIsales::salesUI(){
    char choice;
    ui.clearScreen();
    cout << "What do?" << endl << endl;
    cout << "N - New Order" << endl;
    cout << "C - Change Order" << endl;
    cout << "L - List Orders" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
    if(choice == 'n' || choice == 'N'){
        orderPizza();
    }
    ui.pressEnter();
}

void UIsales::orderPizza(){
    SalesPizza pizza;
    cin >> pizza;
    ofstream fout;
    fout.open("files/virkarPantanir.txt", ios::app);
    fout << pizza;
    fout.close();
}

void UIsales::showActive(){
    SalesPizza pizza;
    ifstream fin;
    fin.open("files/virkarPantanir.txt", ios::app);
    if(fin.is_open()){
        while(!fin.eof()){
            fin >> pizza;
            cout << pizza.ID << " - " << pizza.menuIndex << endl;
        }
        fin.close();
    }else{
        cout << "Ekki hægt að lesa úr skrá" << endl;
    }
}
