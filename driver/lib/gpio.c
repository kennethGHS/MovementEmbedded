
#include <sys/mman.h> //mmap
#include <err.h> //error handling
#include <fcntl.h> //file ops
#include <unistd.h> //usleep



//Static base
static unsigned GPIO_BASE = 0xfe200000;

//Registers pointers
volatile unsigned int * gpfsel0;
volatile unsigned int * gpset0;
volatile unsigned int * gpclr0;
volatile unsigned int * gplev0;

/*function prototypes*/
void gpioInitPtrs();
void gpioSetMode(int gpioPin, unsigned char mode);
void gpioWrite(int gpioPin, unsigned char bit);
void sevenSegmentWrite(char symbol);


// Initialize pointers: performs memory mapping, exits if mapping fails
void gpioInitPtrs(){
	int fd = -1;
	//Loading /dev/mem into a file
	if ((fd = open("/dev/mem", O_RDWR, 0)) == -1)
            err(1, "Error opening /dev/mem");

    //Mapping GPIO base physical address 
	gpfsel0 = (unsigned int*)mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

	//Check for mapping errors
	if (gpfsel0 == MAP_FAILED)
		errx(1, "Error during mapping GPIO");
	
	//Set registers pointers
	gpset0 = gpfsel0 + 0x7; // offset 0x1C / 4 = 0x7
	gpclr0 = gpfsel0 + 0xA; // offset 0x28 / 4 = 0xA
	gplev0 = gpfsel0 + 0xD;
}

//Sets GPIOs modes
void gpioSetMode(int gpioPin, unsigned char mode){
	mode = mode & 0x7; // remove first bit
	int extendedMode = mode; //make 32 bit
	int shift = gpioPin * 3; //amount to shift according to GPIOn
	
	*gpfsel0 = *gpfsel0 | (extendedMode << shift); //shift to position and add
}

//Writes to GPIO
void gpioWrite(int gpioPin, unsigned char bit){
	int write_value = 0x1;
	if (bit) *gpset0 = *gpset0 | (write_value << gpioPin); //sets bit
	else  *gpset0 = *gpset0 & (~(write_value << gpioPin)); //clears bit
}

//Reads from GPIO
int gpioRead(int gpioPin){
	int x = *gplev0;
	for ( int i = 0; i < gpioPin; x>>=1){} //shift bits
	return x & 0x1;
}


void sevenSegmentWrite(char symbol){
	if ('0' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 1);
		gpioWrite(7, 1);
		gpioWrite(8, 0);
	}else if ('1' == symbol){
		gpioWrite(2, 0);
		gpioWrite(3, 0);
		gpioWrite(4, 0);
		gpioWrite(5, 0);
		gpioWrite(6, 1);
		gpioWrite(7, 1);
		gpioWrite(8, 0);
	}else if ('2' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 1);
		gpioWrite(4, 0);
		gpioWrite(5, 1);
		gpioWrite(6, 1);
		gpioWrite(7, 0);
		gpioWrite(8, 1);
	}else if ('3' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 0);
		gpioWrite(7, 0);
		gpioWrite(8, 1);
	}else if ('4' == symbol){
		gpioWrite(2, 0);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 0);
		gpioWrite(6, 0);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	}else if ('5' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 0);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 0);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	}else if ('6' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 0);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 0);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	}else if ('7' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 0);
		gpioWrite(6, 0);
		gpioWrite(7, 0);
		gpioWrite(8, 0);
	}else if ('8' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 1);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	}else if ('9' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 0);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	}else if ('A' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 0);
		gpioWrite(6, 1);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	}else if ('B' == symbol){
		gpioWrite(2, 0);
		gpioWrite(3, 0);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 1);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	}else if ('C' == symbol){
		gpioWrite(2, 0);
		gpioWrite(3, 0);
		gpioWrite(4, 0);
		gpioWrite(5, 1);
		gpioWrite(6, 1);
		gpioWrite(7, 0);
		gpioWrite(8, 1);
	}else if ('D' == symbol){
		gpioWrite(2, 0);
		gpioWrite(3, 1);
		gpioWrite(4, 1);
		gpioWrite(5, 1);
		gpioWrite(6, 1);
		gpioWrite(7, 0);
		gpioWrite(8, 1);
	
	}else if ('E' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 0);
		gpioWrite(4, 0);
		gpioWrite(5, 1);
		gpioWrite(6, 1);
		gpioWrite(7, 1);
		gpioWrite(8, 1);
	
	}else if ('F' == symbol){
		gpioWrite(2, 1);
		gpioWrite(3, 0);
		gpioWrite(4, 0);
		gpioWrite(5, 0);
		gpioWrite(6, 1);
		gpioWrite(7, 1);
		gpioWrite(8, 1);

	}else{
		gpioWrite(2, 0);
		gpioWrite(3, 0);
		gpioWrite(4, 0);
		gpioWrite(5, 0);
		gpioWrite(6, 0);
		gpioWrite(7, 0);
		gpioWrite(8, 0);
	}
}