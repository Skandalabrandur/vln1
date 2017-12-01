#ifndef UIBAKER_H
#define UIBAKER_H
#include <iostream>
#include "MainUI.h"
#include "WRplace.h"
#include "SalesPizza.h"
#include "WRsalespizza.h"

using namespace std;

class UIbaker
{
    private:
        MainUI ui;

    public:
        void bakerUI();
        void chooseActionForPizza();
};

#endif // UIBAKER_H

