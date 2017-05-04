#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/BIOS.h>
#include "LCD.h"

class PushButton {
  private:
    Event_Handle _event;
    uint8_t _pin;
    int buttonState;
    int lastButtonState;
    long lastDebounceTime;
    long debounceDelay;

  public:
    PushButton(uint8_t pin2);
    void begin();
    bool waitForPress();
    bool read();
};
