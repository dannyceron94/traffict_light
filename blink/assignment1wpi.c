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
