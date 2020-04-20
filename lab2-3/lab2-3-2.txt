#include <wiringPi.h>
const int LedRed[8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
const int Keypad[3] = { 16, 13, 12 };

int KeypadRead()
{
	int i, keypadnum=-1;
	for(i=0; i<2; i++) {
		if(digitalRead(Keypad[i])) {
			keypadnum = i; break;
		}
	}
	return keypadnum;
}

void LedControl(int num)
{
	int i;
	for(i=0; i<8; i++) {
		if(i==num)
			digitalWrite(LedRed[i], HIGH);
		else
			digitalWrite(LedRed[i], LOW);
	}
	if(!digitalRead(Keypad[2])
		return 0;
	return 1;
}

int main(void)
{
	int i, keypadnum=-1;
	if(wiringPiSetupGpio() == -1)
		return 1;
	for(i=0; i<8; i++) {
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}
	for(i=0; i<3; i++)
		pinMode(Keypad[i], INPUT);
	while(1) {
		keypadnum = KeypadRead();
		if(keypadnum== 0) {
			int escape = 1;
			while(escape)
			{
				for(i=0; i<8; i++) {
					escape = LedControl(i);
					if(!escape) break;
					for(i = 0; i < 50000000; i++){
						escape = digitalRead(Keypad[2]
						if(!escape) break;
					}
					if(!escape) break;
				}
				for(i=0; i<8; i++)
					digitalWrite(LedRed[i], LOW);
			}
		} else if(keypadnum== 1) {
			int escape = 1;
			while(escape)
			{
				for(i=7; i>=0; i--) {
					escape = LedControl(i);
					if(!escape) break;
					for(i = 0; i < 50000000; i++){
						escape = digitalRead(Keypad[2]
						if(!escape) break;
					}
					if(!escape) break;
				}
			}
			for(i=0; i<8; i++)
				digitalWrite(LedRed[i], LOW);
		}
	}
	return 0;
}