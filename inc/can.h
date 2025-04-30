#ifndef __CAN_H
#define __CAN_H
#include <stdint.h>
#include "stm32f1xx.h"

typedef struct{
uint32_t id;
uint8_t data[7];
uint8_t dlc;
}CAN_Message;

void CAN1_Init(void);
void CAN1_Tx(CAN_Message *msg);
#endif /* INC_ADC_H_ */



  