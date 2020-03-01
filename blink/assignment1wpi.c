/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Danny Daneth Ceron Garcia
* Student ID: 918581149
* Project: <project name, like Assignment 1 - Traffic Light
*
* File: <assignment1wpi.c>
*
* Description: this program uses wiring Pi library to send electrical pulses
*              to specific pins on the raspbery Pi. there are 3 LED's connect to the raspberry Pi
*              each LED is connected in series and dues to kirchhoff's law the entire system will have the same current 
*              regardless of the order in which you connect the LED and the resistor.
*               
*              the library access the pi's pin registers and sets
*              them as output, then set the pin to 1 to send make the LED blink by using GPIO_SET.
*              then uses GPIO_CLR we reset the pin.
*
*              each light has a delay time to give the effect of a traffic light
* Sources: http://wiringpi.com/examples/blink/
**************************************************************/
#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  pinMode (2,OUTPUT); 
  pinMode (3,OUTPUT);

  for (int x=0;x<=2;x=x+1)
  {
    digitalWrite (0, HIGH) ; delay (500*6) ;
    digitalWrite (0, LOW) ; 
    digitalWrite (2, HIGH) ; delay (500*1.5) ;
    digitalWrite (2, LOW) ;
    digitalWrite (3, HIGH) ; delay (500*5) ;
    digitalWrite (3, LOW) ;
  }
  return 0 ;
}
