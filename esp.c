/*****************************************************************************
 *   uarttest.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "uart.h"

extern volatile uint32_t UART3Count;
extern volatile uint8_t UART3Buffer[BUFSIZE];
extern volatile uint32_t UART2Count;
extern volatile uint8_t UART2Buffer[BUFSIZE];
extern volatile uint32_t UART1Count;
extern volatile uint8_t UART1Buffer[BUFSIZE];
extern volatile uint32_t UART0Count;
extern volatile uint8_t UART0Buffer[BUFSIZE];
void send_command(unsigned char *data);
void getreply(void);
void delay(int a);
/*****************************************************************************
**   Main Function  main()
This program has been test on Keil LPC1700 board.
*****************************************************************************/
int main (void)
{
  SystemInit();

  UARTInit(0, 9600);
  UARTInit(1, 9600);	/* baud rate setting */
 
  UARTSend( 1, "ATE0\r\n", sizeof("ATE0\r\n"));	
  delay(2000);
  send_command("AT+CWMODE=1\r\n");
  delay(1000);
  while(1){
  	//send_command("AT\r\n");
   	
//	delay(1000);
  	
  	getreply();
  }																  
}

void send_command(unsigned char *data){
	UARTSend( 1, data, sizeof(data) );
	getreply();
	return;	
}

void getreply(){
 while (1) 
  {				/* Loop forever */
	
	
	if ( UART0Count != 0 )
	{
	  LPC_UART1->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( 1, (uint8_t *)UART0Buffer, UART0Count );
	  UART0Count = 0;
	  LPC_UART1->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	  break;
	}

   	else if ( UART1Count != 0 )
	{
	  LPC_UART0->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	  UART1Count = 0;
	  LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	   break;
	}
/*	else{
		UARTSend( 0, "no", 3 );
	}						  */
  }
  return;

}
void delay(int a){
	int i,j;
	for(i=0;i<=a;i++)
	{
		for(j=i;j<=35;j++)
		{
		}
	}
}

/*****************************************************************************
**                            End Of File
*****************************************************************************/
