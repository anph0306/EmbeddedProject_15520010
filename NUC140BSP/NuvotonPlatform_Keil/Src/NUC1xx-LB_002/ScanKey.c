/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright (c) Nuvoton Technology Corp. All rights reserved.                                             */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "Driver\DrvGPIO.h"
#include "NUC1xx-LB_002\ScanKey.h"

uint8_t pin[8] = {0, 1, 2, 3, 13, 14, 15, 11};

void delay(void)
{
	int j;
	for(j = 0; j < 1000; j++);
}

void OpenKeyPad(void)
{
	uint8_t i;
	
	/* Initial key pad */
	for(i = 0; i < 8; i++)
	DrvGPIO_Open(E_GPA, pin[i], E_IO_QUASI);
}

void CloseKeyPad(void)
{
	uint8_t i;

	for(i = 0; i < 8; i++)
	DrvGPIO_Close(E_GPA, pin[i]);
}

//uint8_t Scankey(void)
int8_t Scankey(void)
{
	const uint8_t ROWS = 4;
	const uint8_t COLS = 4;

	uint8_t hexaKeys[ROWS][COLS]= {
																	{'1', '2', '3', 'A'},
																	{'4', '5', '6', 'B'},
																	{'7', '8', '9', 'C'},
																	{'*', '0', '#', 'D'},
																};   
	uint8_t r, c;
	
	delay();
	
	for (r = 0	; r < ROWS; r++)
	{
		DrvGPIO_ClrBit(E_GPA, pin[r]);
		for (c = 0; c < COLS; c++)
		{
			DrvGPIO_SetBit(E_GPA, pin[c + 4]);
			delay();
			
			if(DrvGPIO_GetBit(E_GPA, pin[c + 4]) == 0)
				return hexaKeys[r][c];
		}
	}
	return -1;
}
