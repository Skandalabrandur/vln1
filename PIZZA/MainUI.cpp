#include <stdio.h>
#include <iostream>
#include "MainUI.h"

using namespace std;

void MainUI::open_menu(){
    //TjA(C)kka hvort bakari, sala, afhending eA?a admin
    cout << "b - BAKER" << endl;
    cout << "s - SALE" << endl;
    cout << "d - DELIVERY" << endl;
    cout << "x - ADMIN" << endl;
    char type = get_type();
    cout << endl;
    if(type == 'd') {
        open_afhending_menu();
    }
    if(type == 'b') {
        open_bakara_menu();
    }
    if(type == 's') {
        open_sala_menu();
    }
    if(type == 'x') {
        open_admin_menu();
    }
}

void MainUI::open_afhending_menu(){
    cout << "g - MERKJA GREITT" << "\t" << "f - MERKJA FARIA?" << "\t" << "b - TIL BAKA" << endl;
    char input;
    cin >> input;
    if(input == 'b'){
        open_menu();
    }
}

void MainUI::open_bakara_menu(){
    //SA?NA PA?TSUR A? RA?TTRI TA?MARA?A?, ELST EFST A?SAMT TA?MA
    cout << "k - MERKJA KLA?RAA?" << "\t\t" << "b - TIL BAKA"  << endl;
    char input;
    cin >> input;
    if(input == 'b'){
        open_menu();
    }
}

void MainUI::open_sala_menu(){
    char input;
    cout << "s - SKRA? PA?NTUN" << "\t\t" << "b - TIL BAKA"  << endl;
    cin >> input;
    if(input == 's'){
        Pizza pizza;
        pizza.panta();
    }
    if(input == 'b'){
        open_menu();
    }
}

void MainUI::open_admin_menu(){
    cout << "s - SJA? VIRKAR PANTANIR" << "\t\t" << "b - TIL BAKA" << endl;
    char input;
    cin >> input;
    if(input == 'b'){
        open_menu();
    }
}



void MainUI::print_foodmenu(){
    string menu[5] = {"MEAT 'N CHEESE", "CHAMPION", "TOKYO", "SURPRISE", "PRINSESSAN"};
    for(int i = 0; i < 5; i++){
        cout << i+1 << " - " << menu[i] << endl;
    }
}

string MainUI::get_menuitem(int i){
    string menu[5] = {"MEAT 'N CHEESE", "CHAMPION", "TOKYO", "SURPRISE", "PRINSESSAN"};
    return menu[i];
}

