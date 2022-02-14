/* 
 * File:   InputBox.cpp
 * Author: sei
 * 
 * Created on 20. August 2014, 20:01
 */

#include "InputBox.h"
#include <GEM_u8g2.h>


InputBox::InputBox(Widget *parent, const String label, int min, int max, int startvalue)
    : Widget(parent) 
{
    this->label = label;
    this->min = min;
    this->max = max;
    this->value = startvalue;
    this->height = 10;
}

void InputBox::claim_input() 
{
    Widget::claim_input();  
}

void InputBox::set_value(int val) {
    value = val;
}

int InputBox::get_value() {
    return value;
}


void InputBox::input(void) 
{
    if (buttons->right.risingEdge()) value++;
    if (buttons->left.risingEdge()) value--;
    
    //if (value < 0) value = max;
    //value %= (max+1);    
    if (value < min) value = min;
    if (value > max) value = max;
    
    if (buttons->press.risingEdge()) {
        release_input(); 
    }    
}


void InputBox::draw(void) 
{    
    u8g2->setCursor(x, y);
        
    u8g2->setFont(u8g2_font_6x10_mf);
    
    u8g2->print(label);    
    
    int offset = numDigits(value);
    
    u8g2->setCursor(x+(64 -(offset*6)),y);
    
    u8g2->print(value);    
}

int InputBox::numDigits(int number)
{
    int digits = 0;
    if (number == 0) return 1;
    if (number < 0) digits = 1; // remove this line if '-' counts as a digit
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}