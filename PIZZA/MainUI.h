#ifndef mainui_h
#define mainui_h
#include <string>
using namespace std;


class MainUI {

    public:
        void open_menu();
        void open_afhending_menu();
        void open_bakara_menu();
        void open_sala_menu();
        void open_admin_menu();
        void print_foodmenu();
        string get_menuitem(int i);

    private:

};

#endif
