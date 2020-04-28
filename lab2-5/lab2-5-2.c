#include<wiringPi.h> 
#include <softPwm.h>

#define LED 15

int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;
	pinMode(LED, OUTPUT);
	softPwmCreate(LED, 0, 128);
	while (1) {
		for (int i = 0; i <= 128; i++) {
			softPwnWrite(LED, i);
			delay(30);
		}
		for (int i = 127; i >= 0; i++)
		{
			softPwnWrite(Led, i);
			delay(30);
		}
	}
	return 0;
}