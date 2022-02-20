/* 
 * File:   FloatInputBox.cpp
 * Author: sei
 * 
 * Created on 20. August 2014, 20:01
 */
#include <FloatInputBox.h>

FloatInputBox::FloatInputBox(Widget *parent, const String label, float min, float max, float step)
    : InputBox<float>(parent, label, min, max, step) 
{
    precision=1;
}

void FloatInputBox::draw(void) 
{    
    u8g2->setCursor(x+dx, y+dy);
        
    u8g2->setFont(u8g2font);
    
    u8g2->print(label);    

    char buf[32];
    for (int i=0;i<32;i++) {
        buf[i] = 0;
    }
    sprintf(buf, "%.*f", precision, value);
    int count = 0;
    for (int i=0;i<32;i++) {
        if (buf[i] == 0) {
            break;
        }
        count++;
    }

    u8g2->setCursor(x+(width - x -(count*fontwidth)),y);
    
    u8g2->print(buf);    
}

void FloatInputBox::set_precision(int precision) 
{
    this->precision = precision;
}

int FloatInputBox::numDigits(float number)
{
    int digits = 1;
    if (number == 0.0) return 2;
    if (number < 0.0) digits++; // remove this line if '-' counts as a digit
    while (number>0.0) {
        number /= 10.0;
        digits++;
    }
    return digits;
}