/*
 * LCD.cpp
 *
 *  
 *      Author: Pranav Narayan Matur
 */


#include "LCD.h"
#include <SPI.h>

#define LCD_COMMAND 0
#define LCD_DATA 1

LCD::LCD(uint8_t SI, uint8_t SCL, uint8_t RS, uint8_t CSB)
{
	this->SI = SI;
	this->SCL = SCL;
	this->RS = RS;
	this->CSB = CSB;
}

void LCD::begin(uint8_t cols, uint8_t lines, uint8_t dotsize)
{
	if (lines > 1) {
	_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;
	_currline = 0;

  // for some 1 line displays you can select a 8 pixel high font
  if ((dotsize != 0) && (lines == 1)) {
  _displayfunction |= LCD_5x8DOTS;
  }


	SPI.begin();
	SPI.setBitOrder(MSBFIRST);

	pinMode(CSB, OUTPUT);
	digitalWrite(CSB, HIGH);

	delay(1);

	pinMode(RS, OUTPUT);

	/* Wakeup */
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, 0x41);
	delay(2);

	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, 0x4B);
	delay(2);

	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, 0x41);
	delay(2);


	/* Clear */
	clear();
	/* Display on */
	display();
	/* Line 1 column 0 */
	home();
}

void LCD::send(uint8_t mode, uint8_t data)
{
	digitalWrite(CSB, LOW);
	digitalWrite(RS, mode);
	SPI.transfer(data);
	digitalWrite(CSB, HIGH);
	delay(1);
}

inline size_t LCD::write(uint8_t value) {
	send(LCD_DATA, value);
}

void LCD::clear()
{
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void LCD::home()
{
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_CURSORHOME);  // set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

// Turn the display off
void LCD::noDisplay() {
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_DISPLAYOFF);
}

// Turn the display on
void LCD::display() {
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_DISPLAYON);
}

// Turns the underline cursor on/off
void LCD::noCursor() {
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_UNDERLINE_CURSOROFF);
}
void LCD::cursor() {
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_UNDERLINE_CURSORON);
}

// Turn on and off the blinking cursor
void LCD::noBlink() {
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_BLINKOFF);
}
void LCD::blink() {
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_BLINKON);
}



// This is for text that flows Left to Right
void LCD::cursorLefttOnePlace(void) {
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_MOVE_CURSORLEFT);
}

// This is for text that flows Right to Left
void LCD::cursorRightOnePlace(void) {

	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_MOVE_CURSORRIGHT);
}

void LCD::backspace(void) {

	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_BACKSPACE);
}

void LCD::setCursor(uint8_t pos)
{
	send(LCD_COMMAND, 0xFE);
	send(LCD_COMMAND, LCD_SETCURSOR);
	send(LCD_COMMAND, pos);
}

