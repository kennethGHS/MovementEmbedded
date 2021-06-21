#include <gpio.h>
#include <stdio.h>
#include <unistd.h> //usleep
int main(){
	// Set GPIOs
	gpioInitPtrs();
	initSevenSegmentDisplay(2, 3, 4, 5, 6, 7, 8);
	
	while(1){
		sevenSegmentWrite('5');
		usleep(1000000);
		sevenSegmentWrite('0');
		usleep(1000000);
		sevenSegmentWrite('5');
		usleep(1000000);
	}
	
	return 0;
}
