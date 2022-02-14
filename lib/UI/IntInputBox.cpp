/* 
 * File:   IntInputBox.cpp
 * Author: sei
 * 
 * Created on 20. August 2014, 20:01
 */
#include <IntInputBox.h>

IntInputBox::IntInputBox(Widget *parent, const String label, int min, int max, int step)
    : InputBox<int>(parent, label, min, max, step) 
{

}

void IntInputBox::draw(void) 
{    
    u8g2->setCursor(x, y);
        
    u8g2->setFont(u8g2font);
    
    u8g2->print(label);    
    
    int offset = numDigits(value);
    
    u8g2->setCursor(x+(128 - x -(offset*fontwidth)),y);
    
    u8g2->printf("%d",value);    
}


int IntInputBox::numDigits(int number)
{
    int digits = 0;
    if (number == 0) return 1;
    if (number < 0) digits++; // remove this line if '-' counts as a digit
    while (number>0) {
        number /= 10;
        digits++;
    }
    return digits;
}