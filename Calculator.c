/*
 * Calculator.c
 *
 *  Created on: Dec 30, 2025
 *      Author: praba
 */
#include <Calculator.h>
#include <stdio.h>
uint16_t lcd_pins[8] =
{
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9
};
char keymap[4][6] =
{
    /* A */ {'C','7','8','9','*','/'},
    /* B */ {'S','4','5','6','-','R'},
    /* C */ {'%','1','2','3',' ','m'},
    /* D */ {'Q','0','.','=','+','p'}
};


void lcdenable(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}
void lcdcommand(uint8_t command)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	lcdWrite(command);
}
void lcdWrite(uint8_t data)
{
    for(int i = 0; i < 8; i++)
    {
        if(data & (1 << i))
            HAL_GPIO_WritePin(GPIOB, lcd_pins[i], GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(GPIOB, lcd_pins[i], GPIO_PIN_RESET);
    }
    lcdenable();
}
void lcdinit(void)
{
	lcdcommand(0x30);
	HAL_Delay(10);
	lcdcommand(0x30);
	HAL_Delay(10);
	lcdcommand(0x30);
	HAL_Delay(10);
	lcdcommand(0x38);
	HAL_Delay(10);
	lcdcommand(0x0E);
	HAL_Delay(10);
}
void lcdchar(uint8_t ch)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	lcdWrite(ch);
}
void lcdstring(char *string)
{
	while(*string)
	lcdchar(*string++);
}
void Keypad_SetRow(uint8_t row)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA,(GPIO_PIN_0 << row),GPIO_PIN_RESET);
}
int Keypad_ReadColumn(void)
{
    uint16_t colPins[6] = {
        GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6,
        GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9
    };

    for(int col = 0; col < 6; col++)
    {
        if(HAL_GPIO_ReadPin(GPIOA, colPins[col]) == GPIO_PIN_RESET)
            return col;
    }
    return -1;
}

char Keypad_GetKey(void)
{
    for(uint8_t row = 0; row < 4; row++)
    {
        Keypad_SetRow(row);
        HAL_Delay(2);
        int col = Keypad_ReadColumn();
        if(col != -1)
        {
            while(Keypad_ReadColumn() != -1);
            return keymap[row][col];
        }
    }
    return 0;
}
void lcdPrintInt(int num)
{
    char buf[16];
    sprintf(buf, "%d", num);
    lcdstring(buf);
}
void lcdPrintfloat (float num)
{
	char buf[20];
	sprintf(buf, "%.2f", num);
	lcdstring(buf);
}
float calculate(float a, float b, char oper)
{
    if(oper == '+') return a + b;
    if(oper == '-') return a - b;
    if(oper == '*') return a * b;
    if(oper == '/') return (b != 0) ? (a / b) : 0;
    return a;
}



