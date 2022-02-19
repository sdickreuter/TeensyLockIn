/* 
 * File:   Menu.cpp
 * Author: sei
 * 
 * Created on 21. August 2014, 23:30
 */

#include "Menu.h"

Menu::Menu(Widget *parent) 
    : Widget(parent) 
{
    children = LinkedList<Widget*>();
    x = 0;
    y = 5;
    active_item = 0;
    num_items = 0;
}

Menu::Menu(Widget *parent, LinkedList<Widget*> *widgets) 
    : Widget(parent) 
{
    children = LinkedList<Widget*>();
    x = 0;
    y = 5;
    Widget *item;
    for (int i = 0; i<widgets->size(); i++) {
        item = widgets->get(i);
        item->parent = this;
        item->set_pos(x+14,y+10+i*(item->get_height()+4)-2);
        children.add(item);
        item = 0;
    }    
    num_items = children.size();
    active_item = 0;    
}

void Menu::add_MenuItem(String label, Widget *target)
{
    MenuItem *item;
    item = new MenuItem(label, this); 
    item->set_pos(x+14,y+10+num_items*(item->get_height()+4)-2);
    item->set_target(target);
    children.add(item);
    num_items = children.size();
}

void Menu::add_Widget(Widget *widget)
{
    widget->set_pos(x+14,y+10+num_items*(widget->get_height()+4)-2);
    //widget->parent = this;
    children.add(widget);
    num_items = children.size();
}

void Menu::claim_input() {
    Widget::claim_input();
    active_item = 0;
}

void Menu::input(void) {
    
    if (buttons->up.risingEdge()) active_item--;
    if (buttons->down.risingEdge()) active_item++;
    
    if (active_item < 0) active_item = num_items-1;
    active_item %= num_items;
  
    children.get(active_item)->input();        
}

void Menu::draw(void) {
    for (int i = 0; i<num_items; i++) {
        children.get(i)->draw();
    } 

    u8g2->setFont(u8g2_font_twelvedings_t_all);
    u8g2->setCursor(0,children.get(active_item)->get_y()+1);
    u8g2->print((char) 46);    

    if (this->draw_callback) this->draw_callback();
}

