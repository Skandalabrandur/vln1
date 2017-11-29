//
//  pizza.cpp
//  PIZZA
//
//  Created by Hlynur HA3lm Hauksson on 28/11/2017.
//  Copyright A(C) 2017 Hlynur HA3lm Hauksson. All rights reserved.
//

#include "pizza.h"
#include <iostream>
#include <fstream>
using namespace std;

char get_type(){
    char type;
    cin >> type;
    return type;
}



void skra_pontun(){
    ofstream fout;
    fout.open("pontun.txt");
    fout << "Pizza meA? engum ananas" << endl;
    fout.close();
}

void Pizza::panta(){
    
    Pizza pizza;
    
    cout << endl << "x - STAA?FESTA" << "\t\t" << "q - ENDURGERA" << endl;
    char yn;
    cout << "PIZZA AF MATSEA?LI? ";
    cin  >> yn;
    
    if(yn == 'y'){
        mainui.print_foodmenu();
        int input;
        cin >> input;
        menu_name = mainui.get_menuitem(input-1);
        cout << endl << mainui.get_menuitem(input-1) << endl;;
        cout << "BOTN: ";
        cin >> pizza.botn;
        while(pizza.botn != 'k' && pizza.botn != 'l' && pizza.botn != 'p'){
            cout << "ERROR" << endl << "BOTN: ";
            cin >> pizza.botn;
        }
        if(pizza.botn != 'p'){
            cout << "STA?RA?: ";
            cin >> pizza.size;
            while(pizza.size != 'l' && pizza.size != 'm' && pizza.size != 's'){
                cout << "ERROR" << endl << "SIZE: ";
                cin >> pizza.size;
            }
        }
    }else{
        cout << endl;
        cout << "BOTN: ";
        cin >> pizza.botn;
        while(pizza.botn != 'k' && pizza.botn != 'l' && pizza.botn != 'p'){
            cout << "ERROR" << endl << "BOTN: ";
            cin >> pizza.botn;
        }
        if(pizza.botn != 'p'){
            cout << "STA?RA?: ";
            cin >> pizza.size;
            while(pizza.size != 'l' && pizza.size != 'm' && pizza.size != 's'){
                cout << "ERROR" << endl << "SIZE: ";
                cin >> pizza.size;
            }
        }
        cout << "A?LEGG: ";
        while(true){
            char input;
            cin >> input;
            if(input == 'x')
                break;
            pizza.alegg.push_back(input);
        }
    }
    char greida;
    cout << "GREIA?A NA?NA? ";
    cin >> greida;
    if(greida == 'y'){
        pizza.greitt = true;
    }
    
    get_info();
    
}

void Pizza::get_info(){
    if(size == 's'){
        cout << "STA?R";
    }
    if(size == 'm'){
        cout << "MIA?LUNGS";
    }
    if(size == 'l'){
        cout << "LA?TIL";
    }
    
    cout << "\t-\t";
    
    if(botn == 'k'){
        cout << "KLASSA?K";
    }
    if(botn == 'l'){
        cout << "LA?TTUR";
    }
    if(botn == 'p'){
        cout << "PA?NNU";
    }
    
    cout << "\t-\t";
    
    if(menu_name != ""){
        cout << menu_name;
        cout << "\t-\t";
    }
    
    if(greitt == true){
        cout << "GREITT";
    }else{
        cout << "A?GREITT";
    }
    
    cout << endl;
}

