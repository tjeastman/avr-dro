#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

int main(void)
{
  DDRB |= _BV(7);

  while (true) {
    PORTB |= _BV(7);
    _delay_ms(1000);
    PORTB &= ~_BV(7);
    _delay_ms(1000);
  }

  return 0;
}
