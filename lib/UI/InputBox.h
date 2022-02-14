/* 
 * File:   InputBox.h
 * Author: sei
 *
 * Created on 20. August 2014, 20:01
 */

#ifndef INPUTBOX_H
#define	INPUTBOX_H

#include <Widget.h>

class InputBox : public Widget {
public:
    InputBox(Widget *parent, const String label, int min, int max, int startvalue);
        
    void draw();
    void input();

    void claim_input();
    
    int get_value();
    void set_value(int val);
    
    static int numDigits(int number);
    
private:
    String label;
    int max;
    int min;    
    int startvalue;
    int value;    
};

#endif	/* INPUTBOX_H */

