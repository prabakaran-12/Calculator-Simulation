/*
 * Calculator.h
 *
 *  Created on: Dec 30, 2025
 *      Author: praba
 */
#include "main.h"

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

void lcdenable(void);
void lcdWrite(uint8_t data);
void lcdcommand(uint8_t command);
void lcdinit(void);
void lcdchar(uint8_t ch);
void lcdstring(char *string);
void Keypad_SetRow(uint8_t row);
int Keypad_ReadColumn(void);
char Keypad_GetKey(void);
void lcdPrintInt(int num);
void lcdPrintfloat (float num);
float calculate(float a, float b, char oper);


#endif /* CALCULATOR_H_ */
