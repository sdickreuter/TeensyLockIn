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
    Menu(Widget *parent, LinkedList<String*> *labels);
           
    void draw();
    void input();
    
    void claim_input();
    
    void add_target(int item, Widget *target);
    
private:
    int num_items;
    int active_item; 
    
    LinkedList<MenuItem*> children; 

};

#endif	/* MENU_H */

