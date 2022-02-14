#include <Arduino.h>
#include "NavButtons.h"

NavButtons::NavButtons() 
{
  pinMode(pinup, INPUT_PULLUP);
  pinMode(pindown, INPUT_PULLUP);
  pinMode(pinleft, INPUT_PULLUP);
  pinMode(pinright, INPUT_PULLUP);
  pinMode(pinpress, INPUT_PULLUP);
  pinMode(pinblue, INPUT_PULLUP);
  pinMode(pinred, INPUT_PULLUP);
}

void NavButtons::update()
{
    this->up.update();
    this->down.update();
    this->left.update();
    this->right.update();
    this->press.update();
    this->blue.update();
    this->red.update();
}