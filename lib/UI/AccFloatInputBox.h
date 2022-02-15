/* 
 * File:   FloatInputBox.h
 * Author: sei
 *
 */

#ifndef ACCFLOATINPUTBOX_H
#define	ACCFLOATINPUTBOX_H

#include <FloatInputBox.h>

class AccFloatInputBox : public FloatInputBox {
public:   
    AccFloatInputBox(Widget *parent, const String label, float min, float max, float step);

    void input();

protected:

};

#endif	/* ACCFLOATINPUTBOX_H */