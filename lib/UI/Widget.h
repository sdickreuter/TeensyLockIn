/* 
 * File:   Widget.h
 * Author: sei
 *
 * Created on 20. August 2014, 20:00
 */

#ifndef WIDGET_H
#define	WIDGET_H

#include <U8g2lib.h>
#include <Arduino.h>
#include <LinkedList.h>
#include "NavButtons.h"

class Widget {
public:
    Widget(NavButtons *buttons, U8G2 *u8g2);
    Widget(Widget *parent);
    
    virtual void draw();
    virtual void input();
    
    virtual void claim_input();
    void claim_draw();
    
    void release_input(boolean pass_down = false);   
    
    void set_width(int width);

    void set_pos(int x, int y);
    void set_dx(int dx);
    void set_dy(int dy);

    int get_x();
    int get_y();    
    
    int get_height();    
    
    void set_font(uint8_t u8g2font, int font_height, int font_width);

    //function has to be called in main programm at a period of 500ms
    //it is used to let stuff on the display blink
    static void switch_blink();
    //function has to be called in main programm at a period of 200ms
    //it is used to let stuff on the display blink fast
    static void switch_blinkfast();

    static boolean blink;
    static boolean blinkfast;    
    
    static Widget *has_input;
    static Widget *is_drawn;      

    Widget *parent;   

    void (*draw_callback)();
    

protected:
    NavButtons *buttons;
    U8G2 *u8g2; 
       
    int x,y;
    int dx = 0,dy = 0;
    int height,width;
    const uint8_t* u8g2font;
    int fontheight, fontwidth;

    int ID;
    static int num_widgets;

private:
    void init();
};


#endif	/* WIDGET_H */

