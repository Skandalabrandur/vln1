#ifndef DELIVERYUI_H
#define DELIVERYUI_H
#include "UIFunctions.h"
#include "orderService.h"
#include "locationService.h"
#include <iostream>
using namespace std;

class deliveryUI
{
    public:
        void displayDeliveryMenu();
        void chooseLocation();
        void viewOrders();
        void selectAndMarkOrderAsPaid();
        void selectAndMarkOrderAsDelivered();

    private:
        UIFunctions uf;
        orderService order_service;
        locationService location_service;
};

#endif // DELIVERYUI_H
