// GPIO Access Library 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
// 각 FND와 연결된 라즈베리파이 핀(S0, S1, …, S5)
const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
// FND의 LED와 연결된 라즈베리파이 핀(A, B, …, H)
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
// FND에 출력되는 문자 (0~9) 배열
const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };

void getData(char **data)
{
    char *queryString, *delim;
    int len = 0;
    int i;

    queryString = getenv("QUERY_STRING");
    delim = strchr(queryString, '=');
    for(i = 0; i < sizeof(delim); i++)
    {
        delim[i] = delim[i + 1];
    }
    delim[sizeof(delim)] = '\0';

    if(delim)
    {
        len = strlen(delim);
        *data = malloc(sizeof(char)*len);
        strcpy(*data, delim);
    }
    else
    {
        len = 1;
        *data = malloc(sizeof(char) *len);
        **data = "\0";
    }
}

void Init()
{
    int i;
    if( wiringPiSetupGpio() == -1 )
    {
        printf("wiringPiSetupGpio() error\n");
        exit(-1);
    }
    for( i = 0; i < 6; i++ )
    {
        pinMode( FndSelectPin[ i ], OUTPUT ); // Select 핀을 출력으로 설정
        digitalWrite( FndSelectPin[ i ], HIGH); // Select 핀 OFF  
    }
    for( i = 0; i < 8; i++ )
    {
        pinMode( FndPin[ i ], OUTPUT ); // LED 핀을 출력으로 설정
        digitalWrite( FndPin[ i ], LOW ); // LED 핀을 OFF
    }
}

void FndSelect (int position) {
    int i;
    for( i = 0; i < 6; i++ )
    {
        if( i == position )
        {
            digitalWrite( FndSelectPin[ i ], LOW ); // 선택된 FND의 Select 핀 ON
        }
        else
        {
            digitalWrite( FndSelectPin[ i ], HIGH ); // 선택되지 않은 FND의 Select 핀 OFF
        }
    }
}

void FndDisplay(int position, int num)
{
    int i, j;
    int flag = 0; // FndPin[ ]을 ON/OFF
    int shift = 0x01; // FndFont와 And 연산하여 출력할 LED의 상태 결정
    for( i = 0; i < 8; i++ )
    {
		digitalWrite(FndPin[i], 0); // 우선 지운다.
        flag = ( FndFont[num] & shift ); // i = 0, FndFont[ 0 ] = 0x3F라 하면 (0b00111111 & 0b00000100 = 1) 이다.
        digitalWrite( FndPin[ i ], flag ); // FndPin[ ]을 flag( 0또는 1 )로 ON/OFF
        shift <<= 1; // 왼쪽으로 한 비트 쉬프트한다. I = 0이라 하면, ( shift = 0b00000001 )에서 ( shift = 0b00000010)로 변한다.
    }
    FndSelect( position ) ;
}

void Fnd(char *data)
{
    int i;
	int num = atoi(data);
	int nums[6];


	for (i = 0; i < 6; i++)
	{
		nums[i] = num % 10;
		num /= 10;
	}

	//자릿수에 맞춰서 출력. ex) 세자리수는 왼쪽 3개에 0을 넣는 것이 아니라 쓰지 않는다.
	for (i = 5; i >= 0; i--)
	{
		if (nums[i] == 0) nums[i] = -1;
		else break;
	}

   // while(1)
    //{
        for(i = 0; i < 6; i++)
        {
            if(nums[i] != -1)
            {
                FndDisplay(i, nums[i]);
                delay(1);
            }
        }
    //}

}


int main()
{
    printf("Content-tpye:text/html\n\n");
    printf("<html>\n<head>\n<title>Solution 4</title>\n</head>\n");
    char *data = (char *)0;
    getData(&data);
    Init();
    Fnd(data);
}