//
//  pizza.hpp
//  PIZZA
//
//  Created by Hlynur HA3lm Hauksson on 28/11/2017.
//  Copyright A(C) 2017 Hlynur HA3lm Hauksson. All rights reserved.
//

#ifndef pizza_h
#define pizza_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "MainUI.h"
using namespace std;

char get_type();
void open_menu();
void open_afhending_menu();
void open_bakara_menu();
void open_sala_menu();
void open_admin_menu();
void skra_pontun();
void print_foodmenu();
string get_menuitem(int i);

class Pizza{
public:
    //eftirfarandi breytur geyma: A?LEGG, TEGUND AF BOTNI, STA?RA?, HEITI A?ESS A? MATSEA?LI EF PA?TSAN ER A? MATSEA?LI, STAA?A PA?TSUNAR A? BA?KUNARFERLINU, HVORT HA?N SA? GREIDD, ID NA?MER
    vector<char> alegg;
    char botn;
    char size;
    string menu_name = "";
    char status;
    bool greitt = false;
    int id;
    
    void panta();
    void get_info();

private:
    MainUI mainui;
};
#endif /* pizza_h */
