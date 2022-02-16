/* 
 * File:   Menu.h
 * Author: sei
 *
 * Created on 21. August 2014, 23:30
 */

#ifndef MENU_H
#define	MENU_H

#include <Widget.h>
#include <MenuItem.h>
#include <LinkedList.h>

class Menu : public Widget {
public:
    Menu(Widget *parent);
    Menu(Widget *parent, LinkedList<Widget*> *widgets);
       
    void draw();
    void input();
    
    void claim_input();
    
    void add_MenuItem(String label, Widget *target);
    void add_Widget(Widget *widget);
 

private:
    int num_items;
    int active_item; 
    
    LinkedList<Widget*> children; 

};

#endif	/* MENU_H */

