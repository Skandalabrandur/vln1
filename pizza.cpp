//
//  pizza.cpp
//  PIZZA
//
//  Created by Hlynur Hólm Hauksson on 28/11/2017.
//  Copyright © 2017 Hlynur Hólm Hauksson. All rights reserved.
//

#include "pizza.hpp"
#include <iostream>
#include <fstream>
using namespace std;

char get_type(){
    char type;
    cin >> type;
    return type;
}

void open_menu(){
    //Tjékka hvort bakari, sala, afhending eða admin
    cout << "b - BAKARI" << endl;
    cout << "s - SALA" << endl;
    cout << "a - AFHENDING" << endl;
    cout << "x - ADMIN" << endl;
    char type = get_type();
    cout << endl;
    if(type == 'a')
        open_afhending_menu();
    if(type == 'b')
        open_bakara_menu();
    if(type == 's')
        open_sala_menu();
    if(type == 'x')
        open_admin_menu();
}

void open_afhending_menu(){
    cout << "g - MERKJA GREITT" << "\t" << "f - MERKJA FARIÐ" << "\t" << "b - TIL BAKA" << endl;
    char input;
    cin >> input;
    if(input == 'b'){
        open_menu();
    }
}

void open_bakara_menu(){
    //SÝNA PÍTSUR Í RÉTTRI TÍMARÖÐ, ELST EFST ÁSAMT TÍMA
    cout << "k - MERKJA KLÁRAÐ" << "\t\t" << "b - TIL BAKA"  << endl;
    char input;
    cin >> input;
    if(input == 'b'){
        open_menu();
    }
}

void open_sala_menu(){
    char input;
    cout << "s - SKRÁ PÖNTUN" << "\t\t" << "b - TIL BAKA"  << endl;
    cin >> input;
    if(input == 's'){
        Pizza pizza;
        pizza.panta();
    }
    if(input == 'b'){
        open_menu();
    }
}

void open_admin_menu(){
    cout << "s - SJÁ VIRKAR PANTANIR" << "\t\t" << "b - TIL BAKA" << endl;
    char input;
    cin >> input;
    if(input == 'b'){
        open_menu();
    }
}

void skra_pontun(){
    ofstream fout;
    fout.open("pontun.txt");
    fout << "Pizza með engum ananas" << endl;
    fout.close();
}

void print_foodmenu(){
    string menu[5] = {"MEAT 'N CHEESE", "CHAMPION", "TOKYO", "SURPRISE", "PRINSESSAN"};
    for(int i = 0; i < 5; i++){
        cout << i+1 << " - " << menu[i] << endl;
    }
}

string get_menuitem(int i){
    string menu[5] = {"MEAT 'N CHEESE", "CHAMPION", "TOKYO", "SURPRISE", "PRINSESSAN"};
    return menu[i];
}

void Pizza::panta(){
    cout << endl << "x - STAÐFESTA" << "\t\t" << "q - ENDURGERA" << endl;
    char yn;
    cout << "PIZZA AF MATSEÐLI? ";
    cin  >> yn;
    
    if(yn == 'y'){
        print_foodmenu();
        int input;
        cin >> input;
        menu_name = get_menuitem(input-1);
        cout << endl << get_menuitem(input-1) << endl;;
        cout << "BOTN: ";
        cin >> botn;
        while(botn != 'k' && botn != 'l' && botn != 'p'){
            cout << "ERROR" << endl << "BOTN: ";
            cin >> botn;
        }
        if(botn != 'p'){
            cout << "STÆRÐ: ";
            cin >> size;
            while(size != 'l' && size != 'm' && size != 's'){
                cout << "ERROR" << endl << "SIZE: ";
                cin >> size;
            }
        }
    }else{
        cout << endl;
        cout << "BOTN: ";
        cin >> botn;
        while(botn != 'k' && botn != 'l' && botn != 'p'){
            cout << "ERROR" << endl << "BOTN: ";
            cin >> botn;
        }
        if(botn != 'p'){
            cout << "STÆRÐ: ";
            cin >> size;
            while(size != 'l' && size != 'm' && size != 's'){
                cout << "ERROR" << endl << "SIZE: ";
                cin >> size;
            }
        }
        cout << "ÁLEGG: ";
        while(true){
            char input;
            cin >> input;
            if(input == 'x')
                break;
            alegg.push_back(input);
        }
    }
    char greida;
    cout << "GREIÐA NÚNA? ";
    cin >> greida;
    if(greida == 'y'){
        greitt = true;
    }
    get_info();
}

void Pizza::get_info(){
    if(size == 's'){
        cout << "STÓR";
    }
    if(size == 'm'){
        cout << "MIÐLUNGS";
    }
    if(size == 'l'){
        cout << "LÍTIL";
    }
    
    cout << "\t-\t";
    
    if(botn == 'k'){
        cout << "KLASSÍK";
    }
    if(botn == 'l'){
        cout << "LÉTTUR";
    }
    if(botn == 'p'){
        cout << "PÖNNU";
    }
    
    cout << "\t-\t";
    
    if(menu_name != ""){
        cout << menu_name;
        cout << "\t-\t";
    }
    
    if(greitt == true){
        cout << "GREITT";
    }else{
        cout << "ÓGREITT";
    }
    
    cout << endl;
}

