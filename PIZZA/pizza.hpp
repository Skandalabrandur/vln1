//
//  pizza.hpp
//  PIZZA
//
//  Created by Hlynur Hólm Hauksson on 28/11/2017.
//  Copyright © 2017 Hlynur Hólm Hauksson. All rights reserved.
//

#ifndef pizza_hpp
#define pizza_hpp
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
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
    //eftirfarandi breytur geyma: ÁLEGG, TEGUND AF BOTNI, STÆRÐ, HEITI ÞESS Á MATSEÐLI EF PÍTSAN ER Á MATSEÐLI, STAÐA PÍTSUNAR Í BÖKUNARFERLINU, HVORT HÚN SÉ GREIDD, ID NÚMER
    vector<char> alegg;
    char botn;
    char size;
    string menu_name = "";
    char status;
    bool greitt = false;
    int id;
    
    void panta();
    void get_info();
};
#endif /* pizza_hpp */
