/* 
 * File:   FloatInputBox.cpp
 * Author: sei
 * 
 * Created on 20. August 2014, 20:01
 */
#include <AccFloatInputBox.h>

AccFloatInputBox::AccFloatInputBox(Widget *parent, const String label, float min, float max, float step)
    : FloatInputBox(parent, label, min, max, step) 
{
}



void AccFloatInputBox::input() 
{
    if (buttons->right.risingEdge()) {
        if (this->value >= 10.0) {
            this->step = 2.0;
        } else if (this->value >= 1.0) {
            this->step = 1.0;
        } else if (this->value >= 0.0) {
            this->step = 0.1;
        }        
        value+=step;
    }
    if (buttons->left.risingEdge()) {
        if (this->value <= 1.0) {
            this->step = 0.1;
        } else if (this->value <= 10.0) {
            this->step = 1.0;
        } else if (this->value < 100.0) {
            this->step = 2.0;
        }      
            value-=step;

    }
    
    //if (value < 0) value = max;
    //value %= (max+1);    
    if (value < min) value = min;
    if (value > max) value = max;
    
    if (buttons->press.risingEdge()) {
        release_input(); 
    } 
}