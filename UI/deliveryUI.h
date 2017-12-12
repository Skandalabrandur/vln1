#ifndef DELIVERYUI_H
#define DELIVERYUI_H
#include "UIFunctions.h"
#include "orderService.h"
#include "locationService.h"
#include "validationService.h"
#include <iostream>
using namespace std;

class deliveryUI
{
    public:
        void displayDeliveryMenu();
        void chooseLocation();
        void viewOrders(bool isReady);
        void selectAndMarkOrderAsPaid();
        void selectAndMarkOrderAsDelivered();
        int getLocationID();

    private:
        int _locationID;
        UIFunctions uf;
        orderService order_service;
        locationService location_service;
        pizzaService pizza_service;
        validationService vs;
};

#endif // DELIVERYUI_H
