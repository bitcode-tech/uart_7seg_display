/******************************************************************************
*  led_disp_example.ino
*  BC759x 7-segment LED Display Library Example Code
*
*  This code uses Serial1 to drive a BC7595 or BC7591 to display a 3
*  digits counter on DIG0-2 which will increase at an interval of 10ms.
*  The SoftwareSerial uses digital I/O pin 2 as Rx and pin 3 as Tx.
*  The SoftwareSerial can be replaced by hardware serial such as Serial,
*  Serial1, or Serial2.
*  This code runs on any Arduino compatible boards.
*
*  Dependencies:
*     This code depends on the following libraries:
*        Arduino Software Serial Library
*        UART_7seg_Display Library
*
*  Author:
*     This software is written by BitCode. https://bitcode.com.cn
*
*  Version:
*     V1.0 March 2021
*
*  License:
*     MIT license. It can be used for both open source and commercial projects.
******************************************************************************/
#include <UART_7Seg_Display.h>

#define	LED_SERIAL	Serial1		// By default this code uses Serial1 as LED display port
// If you are using Arduino with only 1 Serial (such as UNO), you may want to disable 
// the above line and use the following setting:
// #include <SoftwareSerial.h>
// #define LED_SERIAL	swSerial
// SoftwareSerial swSerial(11, 12);          // creating SoftwareSerial instance, using pin 11 as Rx, 12 as Tx (Rx not used in this example)

UART_7Seg_Display      Disp(LED_SERIAL);        // creating display driver instance


uint16_t cnt=0;
float x=1.23;

void setup()
{
	Serial.begin(115200);		 // Initializing printing serial port
    LED_SERIAL.begin(9600);      // Initializing LED display serial port
    Disp.clear();                // Clear any display contents
}

void loop()
{
    Serial.print("Disaplying in decimal : ");
    Serial.println(cnt, DEC);
    Disp.displayDec(cnt, 0, 3);        // Display cnt as decimal number on DIG0-DIG2 (3 digits wide)
    delay(1000);
    Serial.print("Disaplying in hexdecimal : ");
    Serial.println(cnt, HEX);
    Disp.displayHex(cnt, 0, 4);			// Display cnt as hexdecimal on DIG0-DIG3 (4 digits wide)
    delay(1000);
    Serial.print("Disaplying in float : ");
    Serial.println(x,2);
    Disp.displayFloat(x, 0, 3, 2);		// Display x as float number on DIG0-DIG2, 2 digits after decimal point
    Disp.sendCmd(SEG_ON, 0x17);			// Turn on the decimal point on DIG2 (segment address 0x17, see datasheets)
    delay(1000);
    Disp.sendCmd(SEG_OFF, 0x17);		// Turn off the decimal point on DIG2
    cnt = cnt + 1;
    if (cnt == 1000)
    {
        cnt = 0;
    }
    x = x+0.01;
}
