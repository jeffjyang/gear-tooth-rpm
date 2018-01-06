#include "msp430g2553.h"


volatile int wheelToothCount = 0;   // TODO volatile n
volatile int engineToothCount = 0;eeded?

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
    //CCR0 =  10000;                     // 12.5 Hz
    CCR0 = 65535;                     // idk how fast this is
    P1OUT &= 0x00;               // Shut down everything
    P1DIR &= 0x00;
    P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input

    P1REN |= BIT3;  //TODO needed?                 // Enable internal pull-up/down resistors
    P1OUT |= BIT3;                   //Select pull-up mode for P1.3
    P1IE |= BIT3;                       // P1.3 interrupt enabled
    P1IES |= BIT3;                     // P1.3 Hi/lo edge
    P1IFG &= ~BIT3;                  // P1.3 IFG cleared

    // pin 2.1
    P2REN |= BIT1;                   // Enable internal pull-up/down resistors
    P2OUT |= BIT1;                   //Select pull-up mode for P
    P2IE |= BIT1;                       // P interrupt enabled
    P2IES |= BIT1;                     // P Hi/lo edge
    P2IFG &= ~BIT1;                  // P IFG cleared

    _BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt
    while(1)                          //Loop forever, we work with interrupts!
    {
        //if (wheelToothCount == engineToothCount) {
        //    P1OUT |= BIT6;
        //} else {
        //    P1OUT &= ~BIT6;
        //}

    }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    //TODO temp code for testing

    if (wheelToothCount == engineToothCount) {
        P1OUT |= BIT6;
    } else {
        P1OUT &= ~BIT6;
    }

}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    wheelToothCount ++;
    P1IFG &= ~BIT3;
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    engineToothCount ++;
    P2IFG &= ~BIT1;

}

// this is a comment 
//comment 2












/*
 * Test code 2
 */
/*
 #include "msp430g2553.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
    CCR0 =  10000;                     // 12.5 Hz
    P1OUT &= 0x00;               // Shut down everything
    P1DIR &= 0x00;
    P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input
    P1REN |= BIT3;                   // Enable internal pull-up/down resistors
    P1OUT |= BIT3;                   //Select pull-up mode for P1.3
    P1IE |= BIT3;                       // P1.3 interrupt enabled
    P1IES |= BIT3;                     // P1.3 Hi/lo edge
    P1IFG &= ~BIT3;                  // P1.3 IFG cleared
    _BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt
    while(1)                          //Loop forever, we work with interrupts!
    {}
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= BIT0;                          // Toggle P1.0
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= BIT6;                      // Toggle P1.6
    P1IFG &= ~BIT3;                     // P1.3 IFG cleared
}


 */



















/*
    while (1) {
        count = 0;
        while (count < 5){
            if ((P1IN & SENSOR1) == 0x00) {
                count ++;
                while((P1IN & SENSOR1) == 0x00);
            }
        }
        P1OUT ^= LED;
       // P1OUT |= LED;
       // delay();
       // P1OUT &= LED;

    }
 */
/*
void delay (void) {
    unsigned int count;
    for (count = 0; count < 60000; count ++);

}
 */


/*
 *
 */

/*
#include <msp430g2553.h>
#include <stdlib.h>


#define LED BIT6
#define SENSOR1 BIT3
#define SENSOR2 BIT4

void delay (void);


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR = LED;
    P1REN = SENSOR1;
    P1OUT = SENSOR1;

    P1REN = SENSOR2;
    P1OUT = SENSOR2;


    int count1 = 0;
    int count2 = 5;

    while (1) {
        if ((P1IN & SENSOR1) == 0x00) {
            count1 ++;
            while((P1IN & SENSOR1) == 0x00);
        }
        if ((P1IN & SENSOR2) == 0x00) {
            count2 ++;
            while((P1IN & SENSOR2) == 0x00);
        }

        if (abs(count1 - count2) < 1) {
            P1OUT |= LED;
        } else {
            P1OUT &= ~LED;
        }
    }
}
 */
