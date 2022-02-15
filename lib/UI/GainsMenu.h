/* 
 * File:   GainsMenu.h
 * Author: sei
 *
 */

#ifndef GAINS_MENU_H
#define	GAINS_MENU_H

#include <Arduino.h>
#include "Widget.h"
#include "AccFloatInputBox.h"
#include "MenuItem.h"


class Gains_Menu : public Widget {
public:
    Gains_Menu(Widget *parent);
    void draw();
    void input();
    float ingain,lockingain,outgain;

protected:
    
    AccFloatInputBox *inputgainbox;
    AccFloatInputBox *lockingainbox;
    AccFloatInputBox *outputgainbox;
    MenuItem *done;    
        
    int active_item;     
};


#endif	/* GAINS_MENU_H */
