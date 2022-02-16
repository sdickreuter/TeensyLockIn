/* 
 * File:   Button.h
 * Author: sei
 *
 * Created on 21. August 2014, 22:35
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "Widget.h"

class Button : public Widget {
public:
    Button(String label, Widget *parent, void (*callback)() );

    void input();
    void draw();
    
    
protected:
    String label;
    void (*callback)();
};

#endif	/* BUTTON_H */

