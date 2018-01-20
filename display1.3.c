
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
    lcd_init(); //initialize display
    char* test1 = "2 ";
    char* test2 = "2 ";
    char* test3 = "2 ";
    char* test4 = "2 ";
    LCDwriteSpeedCount(test1,test2,test3,test4);
    while(1){}
}

void LCDwriteSpeedCount (char* count1, char* count2, char* speed1, char* speed2) {

    char count1p[1];
//    char count2p[0] = {'4'};
    char* count2p = "bob";

    //sprintf(*count2p, "%d", count2);
    char * speed1p;
    char * speed2p;

    //*count1p = count1;
    //count1p[0] = (char)count1;

    //itoa(count2, count2p, 10); //failed
    //sprintf(count2p, "%d", count2);
    //*count2p = count2;


    //*speed1p = speed1;
    //*speed2p = speed2;



    send_string("C1:"); //line 1 display **note it starts with a space and idk why
    send_string(count1);
    send_string("Speed1:");
    send_string(speed1);

    send_command(0xC0); //return (go to line 2)


    send_string(" C2:"); //line 2
    send_string(count2);
    send_string("Speed2:");
    send_string(speed2);

}
