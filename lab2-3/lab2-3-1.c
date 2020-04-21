#include <wiringPi.h>
const int LedRed[8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
const int Keypad[8] = { 16, 13, 12, 6, 21, 26, 20, 19 };
int LedState[8] = {0,0,0,0,0,0,0,0};
int beforeState[8] = {0,0,0,0,0,0,0,0};

void KeypadRead()
{
	int i, keypadnum=-1;
	for(i=0; i<8; i++) {
		if(!digitalRead(Keypad[i])) {
			beforeState[i] = 1;
		}
		else{
			if(beforeState[i] == 1){
				LedState[i] = (LedState[i] + 1) % 2;
				digitalWrite(LedRed[i], LedState[i]);
				beforeState[i] = 0;
			}
		}
	}
}

void LedControl(int keypadnum)
{
	int i;
	for(i=0; i<8; i++) {
		if(i==keypadnum)
			digitalWrite(LedRed[i], HIGH);
		else
			digitalWrite(LedRed[i], LOW);
	}
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
	for(i=0; i<8; i++)
		pinMode(Keypad[i], INPUT);
	while(1)
	{
		KeypadRead();
	}
	return 0;
}