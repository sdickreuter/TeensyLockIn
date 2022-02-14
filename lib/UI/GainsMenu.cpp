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
    inputgainbox = new InputBox(this, "Input", 0, 100, red);
    inputgainbox->set_pos(x+20,y+10+i*(inputgainbox->get_height()+4)-2);
    i++;
    lockingainbox = new InputBox(this, "Lockin", 0, 100, green);
    lockingainbox->set_pos(x+20,y+10+i*(lockingainbox->get_height()+4)-2);
    i++;
    outputgainbox = new InputBox(this, "Gain", 0, 100, blue);
    outputgainbox->set_pos(x+20,y+10+i*(outputgainbox->get_height()+4)-2);
    i++;
    done = new MenuItem("Done", this);     
    done->set_pos(x+20,y+10+i*(done->get_height()+4)-2);
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
    
    if (this->buttons->press.risingEdge()) {
        switch(active_item) {
            case 0:
                inputgainbox->claim_input();
                break;
            case 1:
                lockingainbox->claim_input();
                break;
            case 2:
                outputgainbox->claim_input();
                break;
            case 3:
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

    u8g2->setFont(u8g2_font_cu12_h_symbols);
    switch(active_item) {
        case 0:
            u8g2->setCursor(5,inputgainbox->get_y()+3);            
            break;
        case 1:
            u8g2->setCursor(5,lockingainbox->get_y()+3);            
            break;
        case 2:
            u8g2->setCursor(5,outputgainbox->get_y()+3);            
            break;
        case 3:
            u8g2->setCursor(5,done->get_y()+3);            
            break;            
    }
    u8g2->print( (char) 104 );
    
    red = inputgainbox->get_value() ;
    green = lockingainbox->get_value();
    blue = outputgainbox->get_value();   
}
