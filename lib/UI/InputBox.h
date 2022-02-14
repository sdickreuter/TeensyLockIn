/* 
 * File:   InputBox.h
 * Author: sei
 *
 * Created on 20. August 2014, 20:01
 */

#ifndef INPUTBOX_H
#define	INPUTBOX_H

#include <Widget.h>

template <class T>
class InputBox : public Widget {
public:
    InputBox(Widget *parent, const String label, T min, T max, T step);
        
    void draw();
    void input();

    void claim_input();
    
    T get_value();
    void set_value(T val);
    
    
protected:
    String label;
    T max;
    T min;    
    T step;
    T value;    
};

#endif	/* INPUTBOX_H */

