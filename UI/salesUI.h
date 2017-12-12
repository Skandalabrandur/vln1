#ifndef salesui_h
#define salesui_h
#include "UIFunctions.h"
#include "orderService.h"
#include "validationService.h"

class salesUI {
    public:
        void displaySalesMenu();
        void selectAndMarkOrderAsPaid();
        void listOrders();
    private:
        UIFunctions uf;
        orderService order_service;
        validationService vs;
};

#endif
