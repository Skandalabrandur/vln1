#ifndef WRSALESPIZZA_H
#define WRSALESPIZZA_H

#include "fstream"
#include "SalesPizza.h"

class WRsalespizza
{
    private:

    public:
        WRsalespizza();
        virtual ~WRsalespizza();

        void saveNewPizza(SalesPizza& pizza);
        SalesPizza* retrievePizzas();
};

#endif // WRSALESPIZZA_H
