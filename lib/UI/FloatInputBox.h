/* 
 * File:   FloatInputBox.h
 * Author: sei
 *
 */

#ifndef FLOATINPUTBOX_H
#define	FLOATINPUTBOX_H

#include <InputBox.h>

class FloatInputBox : public InputBox<float> {
public:   
    FloatInputBox(Widget *parent, const String label, float min, float max, float step);

    void draw();
    void set_precision(int precision);

protected:
    int precision;
    static int numDigits(float number);


};

#endif	/* FLOATINPUTBOX_H */