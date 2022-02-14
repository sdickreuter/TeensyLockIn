/* 
 * File:   LeftRightBox.h
 * Author: sei
 *
 * Created on 24. August 2014, 19:09
 */

#ifndef LEFTRIGHTBOX_H
#define	LEFTRIGHTBOX_H

#include <Widget.h>

class LeftRightBox : public Widget {
public:
    LeftRightBox(Widget *parent, const String label );
        
    void draw();
    void input();

    void claim_input();
        
    boolean is_increased();
    boolean is_decreased();
        
private:
    String label;
    int direction;
    boolean has_input;
    const char indicators[3] = {193, 173, 183};
};

#endif	/* LEFTRIGHTBOX_H */

