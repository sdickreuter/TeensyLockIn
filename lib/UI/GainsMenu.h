/* 
 * File:   GainsMenu.h
 * Author: sei
 *
 */

#ifndef GAINS_MENU_H
#define	GAINS_MENU_H

#include <Arduino.h>
#include "Widget.h"
#include "InputBox.h"
#include "MenuItem.h"


class Gains_Menu : public Widget {
public:
    Gains_Menu(Widget *parent);
    void draw();
    void input();
    
private:
    
    InputBox *inputgainbox;
    InputBox *lockingainbox;
    InputBox *outputgainbox;
    MenuItem *done;    
        
    int red,green,blue;
    int active_item;     
};


#endif	/* GAINS_MENU_H */
