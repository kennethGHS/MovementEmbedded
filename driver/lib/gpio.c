
#include <sys/mman.h> //mmap
#include <err.h> //error handling
#include <fcntl.h> //file ops
#include <unistd.h> //usleep
#include <stdio.h>


//Static base
static unsigned GPIO_BASE = 0x3f200000;

//Registers pointers
volatile unsigned int * gpset0;
volatile unsigned int * gpclr0;
volatile unsigned int * gplev0;

//----0:9 pin GPIO'S-------
volatile unsigned int * gpfsel0;
//----10:19 pin GPIO'S-----
volatile unsigned int * gpfsel1;
//----20:29 pin GPIO's-----
volatile unsigned int * gpfsel2;

/*function prototypes*/
void gpioInitPtrs();
void gpioSetMode(int gpioPin, unsigned char mode);
void gpioWrite(int gpioPin, unsigned char bit);
void sevenSegmentWrite(char symbol);
void initSevenSegmentDisplay(int a, int b, int c, int d, int e, int f, int g);

int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;
int F = 0;
int G = 0;

void initSevenSegmentDisplay(int a, int b, int c, int d, int e, int f, int g){
	A=a;
	B=b;
	C=c;
	D=d;
	E=e;
	F=f;
	G=g;

	gpioSetMode(A, 1);
	gpioSetMode(B, 1);
	gpioSetMode(C, 1);
	gpioSetMode(D, 1);
	gpioSetMode(E, 1);
	gpioSetMode(F, 1);
	gpioSetMode(G, 1);
}

// Initialize pointers: performs memory mapping, exits if mapping fails
void gpioInitPtrs(){
	int fd = -1;
	//Loading /dev/mem into a file
	if ((fd = open("/dev/mem", O_RDWR, 0)) == -1)
            err(1, "Error opening /dev/mem");

    //Mapping GPIO base physical address 
	gpfsel0 = (unsigned int*)mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

	gpfsel1 = gpfsel0 + 0x1;
    gpfsel2 = gpfsel0 + 0x2;

    if (gpfsel0 == MAP_FAILED || gpfsel1 == MAP_FAILED || gpfsel2 == MAP_FAILED){
        errx(1, "Error during mapping GPIO");
    }
	
	//Set registers pointers
	gpset0 = gpfsel0 + 0x7; // offset 0x1C / 4 = 0x7
	gpclr0 = gpfsel0 + 0xA; // offset 0x28 / 4 = 0xA
	gplev0 = gpfsel0 + 0xD;
}

//Sets GPIOs modes
void gpioSetMode(int gpioPin, unsigned char mode){
	mode = mode & 0x7; // remove first bit
	int extendedMode = mode; //make 32 bit
	int shift = 0; //amount to shift according to GPIOn
	if (gpioPin >= 2 && gpioPin <= 9){
		shift = gpioPin * 3;
		*gpfsel0 = *gpfsel0 | (extendedMode << shift); //shift to position and add
	}else if (gpioPin >= 10 && gpioPin <= 19){
		gpioPin = gpioPin - 10;
		shift = gpioPin * 3;
		*gpfsel1 = *gpfsel1 | (extendedMode << shift);
	}else if (gpioPin >= 20 && gpioPin <= 27){
		gpioPin = gpioPin - 20;
		shift = gpioPin * 3;
		*gpfsel2 = *gpfsel2 | (extendedMode << shift);
	}
}

//Writes to GPIO
void gpioWrite(int gpioPin, unsigned char bit){
	int write_value = 0x1;
	if (bit) {
		*gpset0 = write_value << gpioPin;
} //sets bit
	else  {
		*gpclr0 = write_value << gpioPin;
} //clears bit

}


void sevenSegmentWrite(char symbol){
	if ('0' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 1);
		gpioWrite(F, 1);
		gpioWrite(G, 0);
	}else if ('1' == symbol){
		gpioWrite(A, 0);
		gpioWrite(B, 0);
		gpioWrite(C, 0);
		gpioWrite(D, 0);
		gpioWrite(E, 1);
		gpioWrite(F, 1);
		gpioWrite(G, 0);
	}else if ('2' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 1);
		gpioWrite(C, 0);
		gpioWrite(D, 1);
		gpioWrite(E, 1);
		gpioWrite(F, 0);
		gpioWrite(G, 1);
	}else if ('3' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 0);
		gpioWrite(F, 0);
		gpioWrite(G, 1);
	}else if ('4' == symbol){
		gpioWrite(A, 0);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 0);
		gpioWrite(E, 0);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('5' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 0);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 0);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('6' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 0);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 0);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('7' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 0);
		gpioWrite(E, 0);
		gpioWrite(F, 0);
		gpioWrite(G, 0);
	}else if ('8' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 1);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('9' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 0);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('A' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 0);
		gpioWrite(E, 1);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('B' == symbol){
		gpioWrite(A, 0);
		gpioWrite(B, 0);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 1);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('C' == symbol){
		gpioWrite(A, 0);
		gpioWrite(B, 0);
		gpioWrite(C, 0);
		gpioWrite(D, 1);
		gpioWrite(E, 1);
		gpioWrite(F, 0);
		gpioWrite(G, 1);
	}else if ('D' == symbol){
		gpioWrite(A, 0);
		gpioWrite(B, 1);
		gpioWrite(C, 1);
		gpioWrite(D, 1);
		gpioWrite(E, 1);
		gpioWrite(F, 0);
		gpioWrite(G, 1);
	}else if ('E' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 0);
		gpioWrite(C, 0);
		gpioWrite(D, 1);
		gpioWrite(E, 1);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else if ('F' == symbol){
		gpioWrite(A, 1);
		gpioWrite(B, 0);
		gpioWrite(C, 0);
		gpioWrite(D, 0);
		gpioWrite(E, 1);
		gpioWrite(F, 1);
		gpioWrite(G, 1);
	}else{
		gpioWrite(A, 0);
		gpioWrite(B, 0);
		gpioWrite(C, 0);
		gpioWrite(D, 0);
		gpioWrite(E, 0);
		gpioWrite(F, 0);
		gpioWrite(G, 0);
	}
}