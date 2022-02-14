/* 
 * File:   GainsMenu.cpp
 * Author: sei
 * 
 */

#include "GainsMenu.h"

Gains_Menu::Gains_Menu(Widget *parent): Widget(parent)
{
    x = 0;
    y = 5;
            
    active_item = 0;
    int i = 0;    
    inputgainbox = new IntInputBox(this, "Input", 0, 100, 1);
    inputgainbox->set_value(red);
    inputgainbox->set_pos(x+14,y+10+i*(inputgainbox->get_height()+4)-2);
    i++;
    lockingainbox = new IntInputBox(this, "Lockin", 0, 100, 1);
    lockingainbox->set_value(green);
    lockingainbox->set_pos(x+14,y+10+i*(lockingainbox->get_height()+4)-2);
    i++;
    outputgainbox = new FloatInputBox(this, "Gain", 0, 100, 1);
    outputgainbox->set_value(blue);
    outputgainbox->set_pos(x+14,y+10+i*(outputgainbox->get_height()+4)-2);
    i++;
    done = new MenuItem("Done", this);     
    done->set_pos(x+14,y+10+i*(done->get_height()+4)-2);
    //done->set_target(parent);
}


/*
 * function enc_clock()
 *
 * encoder assignment for clock-face
 */
void Gains_Menu::input(void) {
   
    if (this->buttons->up.risingEdge()) active_item--;
    if (this->buttons->down.risingEdge()) active_item++;

    if (active_item < 0) active_item = 3;
    active_item %= 4;    
    

    switch(active_item) {
        case 0:
            inputgainbox->input();
            break;
        case 1:
            lockingainbox->input();
            break;
        case 2:
            outputgainbox->input();
            break;
        case 3:
            if (this->buttons->press.risingEdge()) {
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
void Gains_Menu::draw(void) {
    
    inputgainbox->draw();
    lockingainbox->draw();
    outputgainbox->draw();
    done->draw();

    u8g2->setFont(u8g2_font_twelvedings_t_all);
    switch(active_item) {
        case 0:
            u8g2->setCursor(0,inputgainbox->get_y()+1);            
            break;
        case 1:
            u8g2->setCursor(0,lockingainbox->get_y()+1);            
            break;
        case 2:
            u8g2->setCursor(0,outputgainbox->get_y()+1);            
            break;
        case 3:
            u8g2->setCursor(0,done->get_y()+1);            
            break;            
    }
    u8g2->print( (char) 46 );
    
    red = inputgainbox->get_value() ;
    green = lockingainbox->get_value();
    blue = outputgainbox->get_value();   
}
