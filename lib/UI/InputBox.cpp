/* 
 * File:   InputBox.cpp
 * Author: sei
 * 
 * Created on 20. August 2014, 20:01
 */

#include "InputBox.h"
#include <GEM_u8g2.h>

template <class T>
InputBox<T>::InputBox(Widget *parent, const String label, T min, T max, T step)
    : Widget(parent) 
{
    this->label = label;
    this->min = min;
    this->max = max;
    this->value = 0;
    this->step = step;
    this->height = 10;
}

template <class T>
void InputBox<T>::claim_input() 
{
    Widget::claim_input();  
}

template <class T>
void InputBox<T>::set_value(T val) {
    value = val;
}

template <class T>
T InputBox<T>::get_value() {
    return value;
}

template <class T>
void InputBox<T>::input(void) 
{
    if (buttons->right.risingEdge()) value+=step;
    if (buttons->left.risingEdge()) value-=step;
    
    //if (value < 0) value = max;
    //value %= (max+1);    
    if (value < min) value = min;
    if (value > max) value = max;
    
    if (buttons->press.risingEdge()) {
        release_input(); 
    }    
}

template <class T>
void InputBox<T>::draw(void) 
{    
    u8g2->setCursor(x+dx, y+dy);
        
    u8g2->setFont(u8g2font);
    
    u8g2->print("Overwrite Draw Method!");
}

template class InputBox<int>;
template class InputBox<float>;
