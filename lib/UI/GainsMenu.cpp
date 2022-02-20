/* 
 * File:   GainsMenu.cpp
 * Author: sei
 * 
 */

#include "GainsMenu.h"

Gains_Menu::Gains_Menu(Widget *parent): Widget(parent)
{
    ingain = 1.0;
    lockingain = 1.0;
    outgain = 1.0;

    x = 0;
    y = 5;
            
    active_item = 0;
    int i = 0;    
    inputgainbox = new AccFloatInputBox(this, "Input", 0.0, 100, 0.1);
    inputgainbox->set_value(ingain);
    inputgainbox->set_pos(x+14,y+10+i*(inputgainbox->get_height()+4)-2);
    i++;
    lockingainbox = new AccFloatInputBox(this, "Lockin", 0.0, 100, 0.1);
    lockingainbox->set_value(lockingain);
    lockingainbox->set_pos(x+14,y+10+i*(lockingainbox->get_height()+4)-2);
    i++;
    outputgainbox = new AccFloatInputBox(this, "Output", 0.0, 100, 0.1);
    outputgainbox->set_value(outgain);
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
   
    if (this->buttons->up.fallingEdge()) active_item--;
    if (this->buttons->down.fallingEdge()) active_item++;

    if (active_item < 0) active_item = 3;
    active_item %= 4;    
    

    switch(active_item) {
        case 0:
            inputgainbox->input();
            ingain = inputgainbox->get_value() ; 
            break;
        case 1:
            lockingainbox->input();
            lockingain = lockingainbox->get_value() ; 
            break;
        case 2:
            outputgainbox->input();
            outgain = outputgainbox->get_value() ; 
            break;
        case 3:
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
}
