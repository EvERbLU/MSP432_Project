#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/BIOS.h>
#include "LCD.h"

class Button {
  private:
    Event_Handle _event;
    uint8_t _pin;
    int buttonState;
    int lastButtonState;
    long lastDebounceTime;
    long debounceDelay;

  public:
    Button(uint8_t pin);
    void begin();
    bool waitForPress();
    bool read();
};
