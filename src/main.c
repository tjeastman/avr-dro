#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

int main(void)
{
  DDRB = 0xff;

  while (true) {
    PORTB = 0xff;
    _delay_ms(1000);
    PORTB = 0x00;
    _delay_ms(1000);
  }

  return 0;
}
