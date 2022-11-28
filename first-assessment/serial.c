// include system librarys
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// wiring Pi
#include <wiringPi.h>
#include <wiringSerial.h>

#include <pthread.h>

#define LED_PORT 1
#define SERVO_PORT 0

// Find Serial device on Raspberry with -ls /dev/tty*
// ARDUINO_UNO "/dev/ttyACM0"
// FTDI_PROGRAMMER "/dev/ttyUSB0"
// HARDWARE_UART = "/dev/ttyAMA0"
char device[] = "/dev/ttyACM0";

// file descriptor
int fd;

unsigned long baud = 9600;

int bright = 0;
int angle = 0;
int PWM_FLAG = 0;
int SERVO_FLAG = 0;
int BOTH_FLAG = 0;

// prototypes
int main(void);
void setup(void);
void loop(void);

void mode_1();
void mode_2();
void mode_3();
void mode_4();
void mode_5();
void mode_6();
void mode_7();



void* LED_PWM_THREAD(void* arg){
	
	bright = 0;
	
	while(1){
		for (int i=0; i<=1023; ++i){
			bright++;
			delay(1);
		}
		for (int i=1023; i>=0; --i){
			bright--;
			delay(1);
		}
	}
}

void* SERVO_MOTER_THREAD(void* arg){
	
	angle = 24;
	
	while(1){
		for (int i=0; i<19; ++i){
			angle--;
			delay(50);
		}
		for (int i=0; i<19; ++i){
			angle++;
			delay(50);
		}
	}
}


void setup(){
	
	fflush(stdout);
	
	// get file descriptor
	if ((fd = serialOpen(device, baud)) < 0){
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		exit(1); // error
	}
	
	// setup GPIO in wiringPi mode
	if (wiringPiSetup() == -1){
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		exit(1); // error
	}
	
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, LED_PWM_THREAD, NULL);
	pthread_t thread_servo_id;
	pthread_create(&thread_servo_id, NULL, SERVO_MOTER_THREAD, NULL);
	
	printf("Let's start\n");
}


void loop(){
	
	if (PWM_FLAG == 1){
		pwmWrite(LED_PORT, bright);
	}
	
	if (SERVO_FLAG == 1){
		softPwmWrite(SERVO_PORT, angle);
	}
	
	if (BOTH_FLAG == 1){
		pwmWrite(LED_PORT, bright);
		softPwmWrite(SERVO_PORT, angle);
	}
	
	// read signal
	if (serialDataAvail(fd)){
		char newChar = serialGetchar(fd);
		printf("%c\n", newChar);
		
		switch (newChar) {
			case '1':
				PWM_FLAG = 0;
				SERVO_FLAG = 0;
				mode_1();
				break;
			case '2':
				PWM_FLAG = 0;
				SERVO_FLAG = 0;
				mode_2();
				break;
			case '3':
				SERVO_FLAG = 0;
				mode_3();
				break;
			case '4':
				SERVO_FLAG = 0;
				mode_4();
				break;
			case '5':
				SERVO_FLAG = 0;
				mode_5();
				break;
			case '6':
				SERVO_FLAG = 1;
				mode_6();
				break;
			case '7':
				PWM_FLAG = 1;
				SERVO_FLAG = 1;
				mode_7();
				break;
		}
		
		fflush(stdout);
	}
}

int main(){
	
	setup();
	while(1){
		loop();
	}
	return 0;
	
}


void mode_1(){
	printf("this is one\n");
	printf("LED ON\n");
	pinMode(LED_PORT, OUTPUT);
	digitalWrite(LED_PORT, HIGH);
}

void mode_2(){
	printf("LED OFF\n");
	
	pinMode(LED_PORT, OUTPUT);
	digitalWrite(LED_PORT, LOW);
}

void mode_3(){
	printf("LED PWM\n");
	
	pinMode(LED_PORT, PWM_OUTPUT);
	PWM_FLAG = 1;
	
}

void mode_4(){
	printf("SERVO LEFT\n");
	
	softPwmCreate(SERVO_PORT, 0, 200);
	softPwmWrite(SERVO_PORT, 25);
}

void mode_5(){
	printf("SERVO RIGHT\n");
	
	softPwmCreate(SERVO_PORT, 0, 200);
	softPwmWrite(SERVO_PORT, 5);
}


void mode_6(){
	printf("SERVO WIPER\n");
	
	softPwmCreate(SERVO_PORT, 0, 200);
	SERVO_FLAG = 1;
}

void mode_7(){
	printf("LED AND SERVO\n");
	
	pinMode(LED_PORT, PWM_OUTPUT);
}
