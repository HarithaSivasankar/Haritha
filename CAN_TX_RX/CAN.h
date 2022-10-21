/* 
 * File:   CAN.h
 * Author: ah70192
 *
 * Created on October 11, 2022, 4:37 PM
 */

#ifndef CAN_H
#define	CAN_H

void CAN_Configurator()
{
    CANCON = 0X80;  //Enable Configuration mode
    
    while((CANSTAT)!= 0x80); //Checking Configuration status set or not
    
    /* set Baud rate*/
    BRGCON1 = 0xC1;   //Baud rate 250 Kbps
    
    BRGCON2 = 0xAE;   //
    
    BRGCON3 = 0xA5;
    
    CIOCON = 0x20;   //CAN I/O Control Register
    
    CANCON = 0x08;   //Normal Mode
   
}
#endif

