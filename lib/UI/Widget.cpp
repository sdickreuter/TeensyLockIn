/* 
 * File:   Widget.cpp
 * Author: sei
 * 
 * Created on 20. August 2014, 20:00
 */

#include "Widget.h"

boolean Widget::blink;
boolean  Widget::blinkfast;
Widget *Widget::has_input;
Widget *Widget::is_drawn;  
int Widget::num_widgets;

Widget::Widget(NavButtons *buttons,U8G2 *u8g2) {
    this->draw_callback = nullptr;
    this->buttons = buttons;
    this->u8g2 = u8g2;
    this->parent = this;   
    this->num_widgets +=1;
    this->ID = num_widgets;    
    init();
}

 Widget::Widget(Widget *parent) {
    this->draw_callback = nullptr;
    this->parent = parent;
    this->buttons = parent->buttons;
    this->u8g2 = parent->u8g2;
    this->num_widgets +=1;
    this->ID = num_widgets;
    init();
 }

void Widget::init() {
    this->width = u8g2->getWidth(); 
    this->x = 0;
    this->y = 0;
    this->u8g2font = u8g2_font_6x10_mf;
    this->fontheight = 10;
    this->fontwidth = 6;
    this->height = fontheight;   
}

void Widget::set_width(int width) {
    this->width = width;
}

void Widget::set_dx(int dx) {
    this->dx = dx;
}

void Widget::set_dy(int dy) {
    this->dy = dy;
}

void Widget::set_pos(int x, int y) {
    this->x = x;
    this->y = y;
}

int Widget::get_x() {
    return x+dx;
}

int Widget::get_y() {
    return y+dy;
} 

int Widget::get_height() {
    return height;
}

void Widget::claim_input() {
    Widget::has_input = this;
}   

void Widget::claim_draw() {
    Widget::is_drawn = this;
} 

void Widget::release_input(boolean pass_down = false) {
   if (pass_down) {
       if (! (this == parent)) {
           parent->release_input(true);       
       } else {
           parent->claim_input();
           parent->claim_draw();
       }
    } else parent->claim_input();
}  

void Widget::switch_blink() {
    blink = !blink;
}

void Widget::switch_blinkfast() {
    blinkfast = !blinkfast;
}

void Widget::draw() {
}

void Widget::input() {

}