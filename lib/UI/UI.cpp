#include "UI.h"

/*
 * Constructor
 */
UI::UI(NavButtons *buttons, U8G2 *u8g2) 
{   
    this->buttons = buttons;
    this->u8g2 = u8g2;

    splash = new Splash(buttons, u8g2); 

        
    // create Main Menu       
    LinkedList<String*> labels = LinkedList<String*>();
    labels.add(new String("Set Gains"));
    labels.add(new String("bla"));
    labels.add(new String("blubb"));
    main = new Menu(splash,&labels);
    
        
    // Create Special Menus
    gains = new Gains_Menu(main);
    
    // Set targets
    splash->set_target(main);
    
    main->add_target(0,gains);  
    main->add_target(1,splash);  
    main->add_target(2,splash);  


    splash->claim_draw(); 
    splash->claim_input();
}


/*
 * function draw()
 *
 * draw() chooses what is drawn on the display, depending on ui_state
 * should be called in loop(), or with a timer
 */
void UI::draw(void) {
    u8g2->clearBuffer();	// clear the internal memory
    Widget::is_drawn->draw();
    u8g2->sendBuffer();
}

void UI::input() {
        Widget::has_input->input();
}
