#include "UI.h"


void donothing() {

}

/*
 * Constructor
 */
UI::UI(NavButtons *buttons, U8G2 *u8g2) 
{   
    this->buttons = buttons;
    this->u8g2 = u8g2;

    splash = new Splash(buttons, u8g2); 

    // create Main Menus       
    main = new Menu(splash);
    settings = new Menu(splash);

    gains_menu = new Gains_Menu(settings);
    ref_menu = new Ref_Menu(settings); 

    // Set targets
    splash->set_target(main);

    //populate menu
    ToggleButton* runbutton = new ToggleButton("Run", main, &donothing);
    main->add_Widget(runbutton);
    main->add_MenuItem("Settings",settings);
    main->add_MenuItem("Test Mode",splash);
    main->add_MenuItem("Splash",splash);

    settings->add_MenuItem("Set Gains",gains_menu);
    settings->add_MenuItem("Set Reference",ref_menu);
    settings->add_Widget(new Button("Save Settings", settings, &donothing));
    settings->add_MenuItem("Back",main);


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
