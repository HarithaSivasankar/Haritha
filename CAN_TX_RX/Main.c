/*
 * File:   Main.c
 * Author: ah70192
 *
 * Created on October 11, 2022, 11:33 AM
 */

// PIC18F458 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF         // Brown-out Reset Enable bit (Brown-out Reset enabled)
#pragma config BORV = 25        // Brown-out Reset Voltage bits (VBOR set to 2.5V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG4L
#pragma config STVR = OFF       // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will not cause Reset)
#pragma config LVP = OFF        // Low-Voltage ICSP Enable bit (Low-Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OF
#include <xc.h>
#define _XTAL_FREQ 20000000
#define SW PORTBbits.RB1

void can_write(unsigned int ID, unsigned char data[], unsigned char DLC);


#include "Pin_Initialization.h"
#include "CAN.h"
#include "CAN_Init.h"
#include "Read_Configuration.h"

unsigned char CAN_Receive_Dta[8],CAN_Datalength = 0,Flag = 0;
unsigned int CAN_Acceptance_Filter_Data = 0;

void Read_Data();

void main(void) {
    
    unsigned int ID = 0xF2;  //Message Identifier
    
    unsigned char data[8] = {78,15,2,3,4,5,6,7};
    
    unsigned char DLC = 0x08;
    
    
    INTCONbits.GIE = 1;  //Enable Global Interrupt
    INTCONbits.PEIE = 1; //Enable Peripheral Interrupt
    
    Pin_Configuration();
    
    INTCON2bits.RBPU = 0;
     
     can_init();

     CAN_Configurator(); //Function call 
     
     Read_Config();
     
     can_write(ID, data, DLC);
     
     char i=0;
     for(i=0;i<8;i++)
     {
         CAN_Receive_Dta[i] = 0x60 + i;
     }
    
    
    while(1)
    {
        PORTBbits.RB7 =~ PORTBbits.RB7;
        if(Flag)
        {
            Read_Data();
            can_write(0X70,CAN_Receive_Dta,0x08);
            Flag = 0;
        }
    }
    return;
}

/*Transmitting data*/

void can_write(unsigned int ID, unsigned char* data, unsigned char DLC){   //DLC - Data length Code
    
    
    CANCON = 0x08;  //Setting Configuration mode and Buffer Register
    
 //   while((CANSTAT)!= 0x88);
    
    TXB0SIDH = (ID>>3) & (0xFF);   //Transmit buffer 
    
    TXB0SIDL = (ID<<5) & (0xFF);
    
    TXB0DLC = DLC;
    
    TXB0D0 = data[0];
    TXB0D1 = data[1];
    TXB0D2 = data[2];
    TXB0D3 = data[3];
    TXB0D4 = data[4];
    TXB0D5 = data[5];
    TXB0D6 = data[6];
    TXB0D7 = data[7];
    TXB0CON=0X08;
    CANCON = 0X08; 
    
}
void Read_Data()
{   
    CANCON = 0x0E;   //Normal Mode
    CAN_Datalength = RXB0DLC; //0-3 bits

    
    CAN_Receive_Dta[0] = RXB0D0;
    CAN_Receive_Dta[1] = RXB0D1;
    CAN_Receive_Dta[2] = RXB0D2;
    CAN_Receive_Dta[3] = RXB0D3;
    CAN_Receive_Dta[4] = RXB0D4;
    CAN_Receive_Dta[5] = RXB0D5;
    CAN_Receive_Dta[6] = RXB0D6;
    CAN_Receive_Dta[7] = RXB0D7;
    
    RXB0CONbits.RXFUL = 0;

//    CAN_Acceptance_Filter_Data = RXB0SIDH;  
//    CAN_Acceptance_Filter_Data = (CAN_Acceptance_Filter_Data << 3) | (RXB0SIDL >> 5); 


    LATDbits.LATD6 =~ PORTDbits.RD6;        
//    INTCONbits.GIE = 1;
}

void __interrupt() ISR()
{
    if(PIR3bits.RXB0IF == 1)  //if Peripheral Interrupt 3 set 
    {
        PIR3bits.RXB0IF = 0;
        Flag = 1;
    }
}