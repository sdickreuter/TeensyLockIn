/* 
 * File:   ToggleButton.h
 * Author: sei
 *
 * Created on 21. August 2014, 22:35
 */

#ifndef TOGGLEBUTTON_H
#define	TOGGLEBUTTON_H

#include "Button.h"

class ToggleButton : public Button {
public:
    ToggleButton(String label, Widget *parent, void (*callback)() );

    void input();
    void draw();
    
    
protected:
    boolean state;
};

#endif	/* TOGGLEBUTTON_H */

