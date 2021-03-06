
/* Function for displaying the speed
 * and count (of gear teeth) for sensor 1 and 2
 * Display LCD for gear tooth sensor project (1602a-1)
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
    lcd_init(); //initialize display

    int num1 = 1;
    char num2 = (char)num1;
    int num3 = 3;
    int num4 = 4;


    char* test1 = "225";
    char* test2 = &num2;
    char* test3 = "77";
    char* test4 = "11";


    itoa(num1, test1, 10);
    itoa(num2, test2, 10);
    itoa(num3, test3, 10);
    itoa(num4, test4, 10);




    LCDwriteSpeedCount(test1,test2,test3,test4);
    while(1){}
}

/*
 * function takes strings and writes them to the screen
 */
void LCDwriteSpeedCount (char* count1, char* count2, char* speed1, char* speed2) {

    int a = 2;
    int b = 2;

    send_string("S1:"); //line 1 display **note it starts with a space and idk why
    if (a*b) {
    send_string(count1);
    }
    send_string(" RPM1:");
    send_string(speed1);

    send_command(0xC0); //return (go to line 2)


    send_string(" S2:"); //line 2
    send_string(count2);
    send_string(" RPM2:");
    send_string(speed2);


    //this is in lcd_init and it doesn't work:
    //send_command(0x0E); // clear the screen
    //you need to clear all the bits after what's written, or make sure whatever is written takes up the exact number of spaces on the lcd
    //aka if there are 16 spots and u fill 12, you need to clear the remaining 4
    //or else whatever was there before (in the 4 spots) will remain.

}

/*
 * itoa is a common C function that CCS does not have: it turns ints into strings.
 * it also didn't work since it requires multiplication... try a diff function
 */



void itoa(long unsigned int value, char* result, int base)
    {
      // check that the base if valid
      if (base < 2 || base > 36) { *result = '\0';}

      char* ptr = result, *ptr1 = result, tmp_char;
      int tmp_value;

      do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - (value*base))];
      } while ( value );

      // Apply negative sign
      if (tmp_value < 0) *ptr++ = '-';
      *ptr-- = '\0';
      while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
      }

    }










/*
 * try a different function
 *WOW COME ON THIS HAS MULTIPLICATION TOO
 */

//why static void?

/*
static void SendValue (float data)
{

    static int pint;
    static int pfract;
    static char string[7];
    int len,i,sign;

    sign=(int)data;
    pint =(int)data;
    pfract= (int)((data - pint)*1000);
    pint = abs(pint);
    pfract = abs(pfract);

    sprintf(string,"%03d.%03d",pint,pfract);

    len=strlen(string);
    if (sign < 0)
    {
      TXBUF0= 45; //"-"
        while (!(IFG1 & UTXIFG0));
    }
    for(i=0 ; i<len ; i++)
    {
        TXBUF0= string[i];
        while (!(IFG1 & UTXIFG0));
    }
    _NOP();
}
*/



