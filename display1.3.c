
/* Function for displaying the speed
 * and count (of gear teeth) for sensor 1 and 2
 * Display LCD for gear tooth sensor project
* Created on: 06-Jan-2018
* Author: Andy Luu
*/
#include "display.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer
    LCDwriteSpeedCount(1,2,3,4);
    while(1){}
}

void LCDwriteSpeedCount (int count1, int count2, int speed1, int speed2) {

    char count1p[1];
    char * count2p;
    char * speed1p;
    char * speed2p;

    //*count1p = count1;
    count1p[0] = (char)count1;
    *count2p = count2;
    *speed1p = speed1;
    *speed2p = speed2;


    lcd_init(); //initialize display
    send_string("C1:"); //line 1 display **note it starts with a space and idk why
    send_string(count1p);
    send_string("Speed1:");
    send_string(speed1p);

    send_command(0xC0); //return (go to line 2)


    send_string(" C2:"); //line 2
    send_string(count2p);
    send_string("Speed2:");
    send_string(speed2p);

}
