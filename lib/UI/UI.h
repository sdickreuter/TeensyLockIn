/*
 *	Library for the ui of the alarmclock
 *
 *
 */

#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <U8g2lib.h>

#include "Widget.h"
#include "Menu.h"
#include "NavButtons.h"
#include "splash.h"
#include "GainsMenu.h"

class UI {
  public:

    UI(NavButtons *buttons, U8G2 *u8g2);
    void draw();
    void input();
       
  private:

    Splash *splash;
    Menu *main; 
    Gains_Menu *gains; 
      
    U8G2 *u8g2;
    
    NavButtons *buttons;
};

#endif // UI_H