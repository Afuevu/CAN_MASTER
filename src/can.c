#include "can.h"

void CAN1_Init()
{
  RCC->APB2ENR |= 1 << 2;  // enabling GPIOA clock
  RCC->APB1ENR |= 1 << 25; // enabling CAN1 clock
  RCC->APB2ENR |= 1 << 0;  // enabling AFIOEN clock

  GPIOA->CRH &= ~(0x0F << 16); // CAN_TX PA12
  GPIOA->CRH |= (0x0B << 16);  //

  GPIOA->CRH &= ~(0x0F << 12); // CAN_RX PA11
  GPIOA->CRH |= (0x04 << 12);  //

  //  CAN1->MCR &= ~(1 << 0); // Enter initialization mode
  CAN1->MCR |= (1 << 0);
  while ((CAN1->MSR & CAN_MSR_INAK) == 0)
    ;

  CAN1->MCR &= ~(1 << 1); // EXIT FROM SLEEP MODE
  while ((CAN1->MSR & 0X02) != 0U)
    ;

  CAN1->MCR &= ~(1 << 7); // TIME TRIGERRED DISABLE
  CAN1->MCR &= ~(1 << 6); // AUTO BUSS OFF DISABLE

  CAN1->MCR &= ~(1 << 4); // AUTO RETRANSMISSION ENABLED

  CAN1->MCR &= ~(1 << 5); // DISABLE AUTO WAKEUP

  CAN1->MCR &= ~(1 << 3); // RECEIVED FIFO DISABLED

  CAN1->MCR &= ~(1 << 2); // PRIORITY DRIVEN BY IDENTIFIER

   CAN1->BTR &= ~(1 << 30); // normal mode operation
  CAN1->BTR &= ~(1 << 31); // normal mode operation



  CAN1->BTR &= ~(3 << 24); // SETTING SJW TO 1
  CAN1->BTR |= (0 << 24);

  CAN1->BTR &= ~(0x3FF << 0); // PRESCALER IS 9, BUT 8 IS SENT for 250kbs
  CAN1->BTR |= (8 << 0);

  CAN1->BTR &= ~(0x0F << 16);
  CAN1->BTR |= (12 << 16); // TIMER SEGMENT 1 TO BE DECIMAL 13

  CAN1->BTR &= ~(0x07 << 20);
  CAN1->BTR |= (1 << 20); // TIMER SEGMENT 2 TO BE DECIMAL 2

  CAN1->MCR &= ~CAN_MCR_INRQ;

  while ((CAN1->MSR & CAN_MSR_INAK) != 0U)
    ; // Wait for normal mode
}

void CAN1_Tx(void)
{
   uint8_t our_message[8] = {'D', 'E', '_', 'N', 'A', 'D', 'A'};
  if (!(CAN1->TSR & CAN_TSR_TME0))
    return; // Exit if no free mailbox
  CAN1->sTxMailBox[0].TDTR &= ~(0x0F << 0);
  
  
   CAN1->sTxMailBox[0].TIR &= ~(CAN_TI0R_TXRQ); // Ensure TXRQ is cleared

  CAN1->sTxMailBox[0].TIR &= ~(0x7FF << 21);
  CAN1->sTxMailBox[0].TIR |= (0x65D << 21); // SETTING THE STANDARD IDENTIFER TO 0X65D

 

  CAN1->sTxMailBox[0].TIR &= ~(1 << 2); // SETTING THE CAN IDENTIIFER TO BE STANDARD IDENTIFIER IDE BIT

  CAN1->sTxMailBox[0].TIR &= ~(1 << 1); // ENABLE DATA FRAME AND DISABLING REMOTE FRAME RTR BIT

  CAN1->sTxMailBox[0].TDTR = 7; // setting DLC to 7


  // load the message:

 //Load data into TDLR and TDHR (each word = 4 bytes, LSB first)
    CAN1->sTxMailBox[0].TDLR = (our_message[3] << 24) | (our_message[2] << 16) |
                               (our_message[1] << 8) | (our_message[0]);
    CAN1->sTxMailBox[0].TDHR = (our_message[6] << 16) | (our_message[5] << 8) |
                               (our_message[4]);

  CAN1->sTxMailBox[0].TIR |= (1 << 0); // TXRQ = 1 (Request transmission)

 uint32_t timeout = 100000;

    while (!(CAN1->TSR & CAN_TSR_RQCP0) && --timeout);

  CAN1->TSR |= (1 << 0); // CLEAR REQUEST COMPLETE FLAG
}

