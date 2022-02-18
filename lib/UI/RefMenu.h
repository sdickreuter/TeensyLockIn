/* 
 * File:   GainsMenu.h
 * Author: sei
 *
 */

#ifndef REF_MENU_H
#define	REF_MENU_H

#include <Arduino.h>
#include "Widget.h"
#include "AccFloatInputBox.h"
#include "MenuItem.h"


class Ref_Menu : public Widget {
public:
    Ref_Menu(Widget *parent);
    void draw();
    void input();
    float amp;
    float freq;

protected:
    
    AccFloatInputBox *ampbox;
    AccFloatInputBox *freqbox;
    MenuItem *done;    
        
    int active_item;     
};


#endif	/* REF_MENU_H */
