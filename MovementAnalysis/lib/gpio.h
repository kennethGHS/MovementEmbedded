#ifndef _GPIO_H
#define _GPIO_H
void gpioInitPtrs();
void gpioSetMode(int gpioPin, unsigned char mode);
void gpioWrite(int gpioPin, unsigned char bit);
void sevenSegmentWrite(char symbol);
void initSevenSegmentDisplay(int a, int b, int c, int d, int e, int f, int g);

#endif
