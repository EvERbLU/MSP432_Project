/*
 * LCD.h
 *
 *  
 *      Author: Pranav Narayan Matur
 */

#ifndef LCD_H_
#define LCD_H_

#include <msp.h>
#include <Print.h>
#include <Energia.h>

//Commands
#define LCD_2LINE 0x04
#define LCD_1LINE 0x00

#define LCD_5x8DOTS 0x00

#define LCD_DISPLAYON 0x41
#define LCD_DISPLAYOFF 0x42

#define LCD_SETCURSOR 0x45
#define LCD_CURSORHOME 0x46

#define LCD_UNDERLINE_CURSORON 0x47
#define LCD_UNDERLINE_CURSOROFF 0x48



#define LCD_MOVE_CURSORRIGHT 0x49
#define LCD_MOVE_CURSORLEFT 0x4A

#define LCD_BLINKON 0x4B
#define LCD_BLINKOFF 0x4C


#define LCD_BACKSPACE 0x4E
#define LCD_CLEARDISPLAY 0x51

#define LCD_SET_CONTRAST 0x52
#define LCD_SET_BACKLIGHTBRIGHTNESS 0x53

#define LCD_LOADCHARACTER 0x54
#define LCD_MOVE_DISPLAYLEFT 0x55
#define LCD_MOVE_DISPLAYRIGHT 0x56

#define LCD_CHANGE_BAUDRATE 0x61
#define LCD_CHANGE_I2CADDRESS 0x62

#define LCD_DISPLAY_FIRMWARENUMBER 0x70
#define LCD_DISPLAY_BAUDRATE 0x71
#define LCD_DISPLAY_I2CADDRESS 0x72


class LCD : public Print {
public:
	LCD(uint8_t SI, uint8_t SCL, uint8_t RS, uint8_t CSB);
	void begin(uint8_t lines = 16, uint8_t rows = 2, uint8_t dotsize = LCD_5x8DOTS);
	void send(uint8_t mode, uint8_t data);

	void clear();
	void home();
	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void cursorLefttOnePlace();
	void cursorRightOnePlace();
	void setCursor(uint8_t pos);
	void backspace(void);
	virtual size_t write(uint8_t);

	void command(uint8_t);


	using Print::write;
private:
	uint8_t SI;
	uint8_t SCL;
	uint8_t RS;
	uint8_t CSB;
	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;
	uint8_t _numlines,_currline;
};




#endif /* LCD_H_ */
