/* 
 * File:   GainsMenu.h
 * Author: sei
 *
 */

#ifndef GAINS_MENU_H
#define	GAINS_MENU_H

#include <Arduino.h>
#include "Widget.h"
#include "IntInputBox.h"
#include "FloatInputBox.h"
#include "MenuItem.h"


class Gains_Menu : public Widget {
public:
    Gains_Menu(Widget *parent);
    void draw();
    void input();
    
protected:
    
    IntInputBox *inputgainbox;
    IntInputBox *lockingainbox;
    FloatInputBox *outputgainbox;
    MenuItem *done;    
        
    int red,green,blue;
    int active_item;     
};


#endif	/* GAINS_MENU_H */
