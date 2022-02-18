/* 
 * File:   GainsMenu.cpp
 * Author: sei
 * 
 */

#include "RefMenu.h"

Ref_Menu::Ref_Menu(Widget *parent): Widget(parent)
{
    amp = 0.5;
    freq = 2000.0;

    x = 0;
    y = 5;
            
    active_item = 0;
    int i = 0;    
    ampbox = new AccFloatInputBox(this, "Amp", 0.0, 1.0, 0.1);
    ampbox->set_value(amp);
    ampbox->set_pos(x+14,y+10+i*(ampbox->get_height()+4)-2);
    i++;
    freqbox = new FloatInputBox(this, "Freq", 500.0, 5000.0, 100);
    freqbox->set_value(freq);
    freqbox->set_pos(x+14,y+10+i*(freqbox->get_height()+4)-2);
    i++;
    done = new MenuItem("Done", this);     
    done->set_pos(x+14,y+10+i*(done->get_height()+4)-2);
    //done->set_target(parent);
}



void Ref_Menu::input(void) {
   
    if (this->buttons->up.fallingEdge()) active_item--;
    if (this->buttons->down.fallingEdge()) active_item++;

    if (active_item < 0) active_item = 2;
    active_item %= 3;    
    

    switch(active_item) {
        case 0:
            ampbox->input();
            amp = ampbox->get_value() ; 
            break;
        case 1:
            freqbox->input();
            freq = freqbox->get_value() ; 
            break;
        case 2:
            if (this->buttons->press.fallingEdge()) {
                active_item = 0;
                this->parent->claim_input();
                this->parent->claim_draw();
                break;            
             }
    }

}

/*
 * function draw_clock()
 *
 * function for drawing the clock-face
 */
void Ref_Menu::draw(void) {
    
    ampbox->draw();
    freqbox->draw();
    done->draw();

    u8g2->setFont(u8g2_font_twelvedings_t_all);
    switch(active_item) {
        case 0:
            u8g2->setCursor(0,ampbox->get_y()+1);            
            break;
        case 1:
            u8g2->setCursor(0,freqbox->get_y()+1);            
            break;
        case 2:
            u8g2->setCursor(0,done->get_y()+1);            
            break;            
    }
    u8g2->print( (char) 46 );
}
