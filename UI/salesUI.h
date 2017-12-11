#ifndef salesui_h
#define salesui_h
#include "UIFunctions.h"
#include "orderService.h"

class salesUI {
    public:
        void displaySalesMenu();
        void selectAndMarkOrderAsDelivered();
    private:
        UIFunctions uf;
        orderService order_service;
};

#endif
