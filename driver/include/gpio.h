#ifndef _GPIO_H
#define _GPIO_H
void gpioInitPtrs();
void gpioSetMode(int gpioPin, unsigned char mode);
void gpioWrite(int gpioPin, unsigned char bit);
void sevenSegmentWrite(char symbol);
#endif
