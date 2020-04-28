#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
const int FndFont[6] = { 0x76, 0x79, 0x38, 0x38, 0x3F, 0x00 };
int FndState[6] = { 5, 5, 5, 5, 5, 5 };

void Init() {
	int i;
	if (wiringPiSetupGpio() == -1) {
		//printf(¡°wiringPiSetupGpio() error\n¡±);
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
int main() {
	int pos;
	int first = 0;
	Init();
	while (1) {
		for (pos = 6; pos > 0; pos--) {
			FndState[pos] = FndState[pos - 1];
			FndDisplay(pos, FndState[pos]);
			delay(1);
		}
		FndState[0] = (FndState[0] + 1) % 6;
		FndDisplay(pos, FndState[0]);
		delay(500);
	}
	return 0;
}