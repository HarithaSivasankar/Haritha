/* 
 * File:   Read_Configuration.h
 * Author: ah70192
 *
 * Created on October 18, 2022, 4:16 PM
 */

#ifndef READ_CONFIGURATION_H
#define	READ_CONFIGURATION_H
void Read_Config();
void Read_Config()
{
    PIE3bits.RXB0IE = 1;
    IPR3bits.RXB0IP = 1;
    
    CANCON = 0X0E;
    
    RXF0SIDH = 0X00;
    RXF0SIDL = 0X00;
    RXM0SIDH = 0X00;
    RXM0SIDH = 0X00;
}
#endif	/* READ_CONFIGURATION_H */

