#ifndef DELIVERYUI_H
#define DELIVERYUI_H
#include "UIFunctions.h"
#include "orderService.h"
#include <iostream>
using namespace std;

class deliveryUI
{
    public:
        void displayDeliveryMenu();
        void viewOrders();
        void selectAndMarkOrderAsPaid();
        void selectAndMarkOrderAsDelivered();

    private:
        UIFunctions uf;
        orderService order_service;
};

#endif // DELIVERYUI_H
