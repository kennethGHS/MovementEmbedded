#include <gpio.h>
#include <stdio.h>
#include <unistd.h> //usleep
int main(){
	// Set GPIOs
	gpioInitPtrs();
	gpioSetMode(2, 1);
	gpioSetMode(3, 1);
	gpioSetMode(4, 1);
	gpioSetMode(5, 1);
	gpioSetMode(6, 1);
	gpioSetMode(7, 1);
	gpioSetMode(8, 1);
	
	while(1){
		sevenSegmentWrite('5');
		usleep(1000);
		sevenSegmentWrite('0');
		usleep(1000);
		sevenSegmentWrite('5');
		usleep(1000);
	}
	
	
	return 0;
}
