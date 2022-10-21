/* 
 * File:   CAN_Init.h
 * Author: ah70192
 *
 * Created on October 15, 2022, 5:24 PM
 */

#ifndef CAN_INIT_H
#define	CAN_INIT_H

void can_init(){
    
    TRISBbits.RB2 = 0; //Tx Pin Direction definition
    TRISBbits.RB3 = 1; //Rx Pin Direction definition    
}
#endif	/* CAN_INIT_H */

