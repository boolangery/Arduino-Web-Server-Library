#ifndef MENU_ITEM_HEADER
#define MENU_ITEM_HEADER
#include "HtmlPage.h"

class MenuItem
{
    public:
        MenuItem(String menuName, HtmlPage* page): _menuName(menuName), _page(page) {};
        HtmlPage* getPage() {return _page;}
        String getName() {return _menuName;}
  
    private:
        String _menuName;
        HtmlPage* _page;
};

#endif
