/* 
 * File:   MenuItem.h
 * Author: sei
 *
 * Created on 21. August 2014, 22:35
 */

#ifndef MENUITEM_H
#define	MENUITEM_H

#include "Widget.h"

class MenuItem : public Widget {
public:
    MenuItem(Widget *target, String label, Widget *parent);
    MenuItem(String label, Widget *parent);

    void input();
    void draw();
    
    void set_target(Widget *target);
    
protected:
    String label;
    Widget *target;
};

#endif	/* MENUITEM_H */

