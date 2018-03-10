
/* Function for displaying the speed (in rpm, called R)
 * and count (of gear teeth) for sensor 1 and 2
 * Display LCD for gear tooth sensor project (1602a-1)
 * Note here the maximum RPM was estimated to be around 600, and thus only 4 digits max are alloted to RPM
* Created on: 06-Jan-2018
* Author: Andy Luu
*/
#include "display.h"
#include <math.h>

#include <float.h>
#include "msp430g2553.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer

    //Note there is no limit on the count variable yet (count 1 and count2)
    //the plan is to have this number go from 0 to the max number of teeth of the respective gear
    //then reset and count from 0 again.

    FullLCDwriteRPMCount(111,222,333,444);

    while(1){}
}


void FullLCDwriteRPMCount (int rpm1, int count1, int rpm2, int count2) {

    lcd_init(); //initialize display I believe this also clears the display, which could be useful later
    send_string("RPM:"); //line 1 display **note it starts with a space and idk why
    LCDwriteRPMCount(rpm1);
    send_string(" n1:");
    LCDwriteRPMCount(count1);

    send_command(0xC0); //return (go to line 2)

    send_string(" RPM:"); //line 2
    LCDwriteRPMCount(rpm2);
    send_string(" n2:");
    LCDwriteRPMCount(count2);

}


void LCDwriteRPMCount (int a) {

    int i = 0;

    int size = getsize(a); //for 928 size = 3
    int sizecpy = size-1; //max array slots, but this variable will be changed.


    //display can only display 8 numbers max. Allocate 10 space.
    char test1[10];

    //copy the number into an array, digit by digit
    while (i<size){
        //step 1: divide by 10 size-1 times
        test1[i]=div10(a,sizecpy); //for 928, this is 9
        //step 2: take this number, multiply it size-1 times, subtract from original number
        a = a-mult10(test1[i],sizecpy); //this is 928-900 = 28
        //do it again.
        i++;
        sizecpy--;
    }


    test1[i]=0; //need this for null charcter: it ends the string and basically also ends whatever is printed on the screen


    //manually convert all  digits to acII characters to be properly printed
    for (i=0; i<size; i++){
        test1[i] +=48;
    }


    send_string(test1);
    return;
}


/*
 * function multiplies an int, n, by 10
 * does this  x number of times
 */

int mult10(int n, int x) //if x = 2 and n is 9
{
    while (x>0){   //2,1,stop
        n = n*10;  //90,900
        x--;      //1,0
    }

    return n; //900
}

/*
 * function divides an int, n, by 10
 * does this  x number of times
 */
int div10(int n, int x) //if x=2 and n=900
{
    while (x>0){   //2,1,stop
        n = n/10;  //90,9
        x--;      //1,0
    }
    return n;
}

int getsize(int n) //n = 928
{
    int i = 0;

    while (n>0){
        i++; //1,2,3,stops
        n = n/10; //92,2,0
    }

    return i;
}






