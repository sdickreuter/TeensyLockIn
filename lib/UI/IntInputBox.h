/* 
 * File:   IntInputBox.h
 * Author: sei
 *
 */

#ifndef INTINPUTBOX_H
#define	INTINPUTBOX_H

#include <InputBox.h>

class IntInputBox : public InputBox<int> {
public:   
    IntInputBox(Widget *parent, const String label, int min, int max, int step);

    void draw();

protected:
    static int numDigits(int number);

};

#endif	/* INTINPUTBOX_H */