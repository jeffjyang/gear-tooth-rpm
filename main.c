#include "msp430g2553.h"

#define CHECK_INTERVAL_MS 500;	// TODO verify this number 
#define ACCEPTABLE_RPM_PERCENTAGE_DIFF 0.05;

// TODO verify these numbers
#define WHEEL_GEAR_SIZE 24;
#define ENGINE_GEAR_SIZE 36;

volatile int wheelToothCount = 0;   // TODO volatile needed??
volatile int engineToothCount = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
    //CCR0 =  10000;                     // 12.5 Hz
    CCR0 = 65535;                     // idk how fast this is // maybe every half second? 
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
    	// wait for interrupts for control 
    }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT |= BIT0;

 //   P1OUT |= BIT6;
  //  P1OUT |= BIT6;

	// disable global interrupts while performing check
	// TODO this might not be the right command
	__disable_interrupt();


	// check the speeds of the two gears. 
	// units irrelavent since we only want relative speed 
//	double wheelSpeed = ( wheelToothCount * 1.0 / WHEEL_GEAR_SIZE ) / CHECK_INTERVAL_MS;
//	double engineSpeed = ( (double) engineToothCount / ENGINE_GEAR_SIZE ) / CHECK_INTERVAL_MS;

	// this doesnt work for some reason
	/*
	double wheelSpeed = (wheelToothCount * 1.0) / WHEEL_GEAR_SIZE ;
	wheelSpeed = wheelSpeed / CHECK_INTERVAL_MS;
	double engineSpeed = engineToothCount * 1.0 / ENGINE_GEAR_SIZE;
	engineSpeed = engineSpeed / CHECK_INTERVAL_MS;
*/
/*
	double wheelSpeed = wheelToothCount;
	double engineSpeed = engineToothCount;
*/

	double wheelSpeed = wheelToothCount * 10;
	wheelSpeed = wheelSpeed / WHEEL_GEAR_SIZE;

	double engineSpeed = engineToothCount * 10;
	engineSpeed = engineSpeed / ENGINE_GEAR_SIZE;

	// If engine RPM is within 5% of wheel RPM, set the output pin to HIGH
	double rpmDiff = abs(wheelSpeed - engineSpeed) / ((wheelSpeed + engineSpeed) / 2);

	//rpmDiff < ACCEPTABLE_RPM_PERCENTAGE_DIFF

	double acceptDiff = ACCEPTABLE_RPM_PERCENTAGE_DIFF;

	if (rpmDiff < acceptDiff) {
	// TODO output pins
        P1OUT |= BIT6;
	} else {
        P1OUT &= ~BIT6;
	}
    P1OUT &= ~BIT0;

	wheelToothCount = 0;
	engineToothCount = 0;

	// enable interrups 
	// TODO verify command 
	__enable_interrupt();

//	P1OUT &= ~BIT0;
//    P1OUT &= ~BIT6;

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
