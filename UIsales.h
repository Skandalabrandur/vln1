//
//  UIsales.hpp
//  
//
//  Created by Hlynur Hólm Hauksson on 30/11/2017.
//

#ifndef UIsales_h
#define UIsales_h

#include <stdio.h>
#include "MainUI.h"
using namespace std;

class UIsales {
    
public:
    void orderPizza();
    void orderPizzaMenu();
    
private:
    MainUI ui;
};

#endif /* UIsales_h */
