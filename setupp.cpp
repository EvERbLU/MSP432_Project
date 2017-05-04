/*
 * setupp.cpp
 *
 *  
 *      Author: Pranav Narayan Matur
 */
 

#include <msp.h>
#include <SPI.h>
#include "LCD.h"
#include "Button.h"
#include "PushButton.h"


#define LCD_CSB 13
#define LCD_RS 12
#define LCD_SI 15
#define LCD_SCL 7

// initialize the library with the numbers of the interface pins
LCD lcd(LCD_SI, LCD_SCL, LCD_RS, LCD_CSB);

Button button(PUSH1);
PushButton push_button(PUSH2);


void ButtonS() {  
  button.begin();
}

void ButtonL() {
  button.read();
}



void PushButtonS() {  
  push_button.begin();
}

void PushButtonL() {
  push_button.read();
}

void lcdS()
{
  lcd.clear();
  lcd.begin(16, 2);
  delay(500);
  lcd.print("Press button!");
}


void lcdL()
{
  if(button.waitForPress())
  {
    lcd.clear();
    lcd.print("Button1 pressed!");
  }
  
  if(push_button.waitForPress())
  {
    lcd.clear();
    lcd.print("Button2 pressed!");
  }
  
}


