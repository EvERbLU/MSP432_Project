#include "PushButton.h"

PushButton::PushButton(uint8_t pin2)
{
  _pin = pin2;
  lastButtonState = HIGH;
  buttonState = HIGH;
  lastDebounceTime = 0;
  debounceDelay = 50;  
}

void PushButton::begin()
{
  pinMode(_pin, INPUT_PULLUP);
  
  Error_Block eb;
  Error_init(&eb);
  /* Default instance configuration params */
  _event = Event_create(NULL, &eb);
}

bool PushButton::read()
{
  int reading = digitalRead(_pin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
        buttonState = reading;

      if (buttonState == HIGH) {
        Event_post(_event, Event_Id_01);
        delay(5000);
      }
    }
  }
  lastButtonState = reading;
}

bool PushButton::waitForPress()
{
  xdc_UInt events;
  events = Event_pend(_event, Event_Id_NONE,
    Event_Id_01, BIOS_WAIT_FOREVER);    
}
