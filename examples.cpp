#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <softPwm.h>

int main (void)
{
  wiringPiSetup () ;

  // UART Send ------------------
  int fd ;

  if ((fd = serialOpen ("/dev/ttyS0", 9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  
  fprintf (stdout, "Puttinh A \n");
  serialPutchar (fd, 'a') ;
  printf ("A put\n") ;
  
  // Blink LEDs ------------------
  /**pinMode (0, OUTPUT) ;
  for (;;)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    digitalWrite (0,  LOW) ; delay (500) ;
  }**/
  
  // PWM out
  softPwmCreate(1, 0, 100) ;
  softPwmWrite (1, 50) ;
  while(1);
  
  return 0 ;
}
