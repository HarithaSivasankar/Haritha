/* 
 * File:   Pin_Initialization.h
 * Author: ah70192
 *
 * Created on October 15, 2022, 5:18 PM
 */

#ifndef PIN_INITIALIZATION_H
#define	PIN_INITIALIZATION_H

void Pin_Configuration()
{
    TRISA = 0XFF;
    TRISB = 0X7F;
    TRISC = 0XFF;
    TRISD = 0X3F;
}

#endif	/* PIN_INITIALIZATION_H */

