/* 
 * File:   MenuItem.h
 * Author: sei
 *
 * Created on 21. August 2014, 22:35
 */

#ifndef MENUITEM_H
#define	MENUITEM_H

#include "Button.h"

class MenuItem : public Button {
public:
    MenuItem(Widget *target, String label, Widget *parent);
    MenuItem(String label, Widget *parent);

    void input();
    
    void set_target(Widget *target);
    
protected:
    Widget *target;
};

#endif	/* MENUITEM_H */

