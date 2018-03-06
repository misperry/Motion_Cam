/*
 *  File Name: Motion_Cam.c
 *
 *  Application: Raspberry Pi Zero
 *
 *  Description:  This sofware will control a servo motor
 *  via GPIO_PIN 18 to move a USB camera in 3 different
 *  direcitons 0, 90, and 180 degrees.  This will be
 *  triggered based on motino sensors placed at the 
 *  angles described above.  They will be connected to
 *  GPIO_PIN 14, 15, and 23.  The ystem will trigger motion
 *  and face the camera towards the sensor that picked up
 *  the motion
 *
 *  Author:  M. Sperry - http://www.youtube.com/misperry
 *  Date:  03/05/2018
 *  Revision: 1.0
 *
 * 
 */
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>

int counter = 0;

void Take_Picture(void)
{
	char command[500];
	int status;
        
	counter++;
	sprintf(command,"fswebcam -i 0 -r 1280x720 --no-banner pic%d.jpg",counter);
	system(command); 
}

int main()
{

	wiringPiSetupGpio();
	pinMode(18, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);

	pwmSetClock(192);
	pwmSetRange(2000);

	delay(10);
        
	//Center the servo
	pwmWrite(18,155);
	delay(200);

	for (;;)
	{
		if (digitalRead(14))
		{
			printf("Left Sensor Read\n");
			pwmWrite(18,234);
			delay(10);
			Take_Picture();
			while (digitalRead(14));
		}
		else if (digitalRead(15))
		{
			printf("Center Sensor Read\n");
			pwmWrite(18,155);
			delay(10);
			Take_Picture();
			while (digitalRead(15));
		}
		else if (digitalRead(23))
		{
			printf("Right Sensor Read\n");
			pwmWrite(18,70);
			delay(10);
			Take_Picture();
			while (digitalRead(23));
		}
		delay(500);
	}

	return 0;
}
