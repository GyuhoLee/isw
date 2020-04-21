#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };
int FndState[6] = { 0, 0, 0, 0, 0, 0 };

void Init() {
	int i;
	if (wiringPiSetupGpio() == -1) {
		printf(¡°wiringPiSetupGpio() error\n¡±);
		exit(-1);
	}
	for (i = 0; i < 6; i++) {
		pinMode(FndSelectPin[i], OUTPUT);
		digitalWrite(FndSelectPin[i], HIGH);
	}
	for (i = 0; i < 8; i++) {
		pinMode(FndPin[i], OUTPUT);
		digitalWrite(FndPin[i], LOW);
	}
}

void FndSelect(int position) {
	int i;
	for (i = 0; i < 6; i++) {
		if (i == position) {
			digitalWrite(FndSelectPin[i], LOW);
		}
		else {
			digitalWrite(FndSelectPin[i], HIGH);
		}
	}
}

void FndDisplay(int position, int num) {
	int i, j;
	int flag = 0;
	int shift = 0x01;
	for (i = 0; i < 8; i++) {
		flag = (FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift <<= 1;
	}
	FndSelect(position);
}

void TimePlus(int position)
{
	if (FndState[position] == 9)
	{
		FndState[positon] = 0;
		if (position != 5) TomePlus(position + 1);
	}
	else FndState[position]++;
}

int main() {
	int pos;
	Init();
	while (1) {
		TimePlus(0);
		for (pos = 0; pos < 6; pos++) {
			FndDisplay(pos, FndState[pos]);
			delay(1);
		}
		delay(10);
	}
	return 0;
}