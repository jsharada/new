/*
 */

//start single conversion
#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint16_t overflow=0;

int main(void)
{

    // Insert code
    TCCR1B |= (1<<CS12); //clk/256 prescaler

    //TCCR1A |= (1<<CS10);
    TCCR1A |= (1<<WGM10);
    TCCR1B |= (1<<WGM12);
    TCNT1 =0x00;        // reg used for counting
    TIMSK1 |=(1<<TOIE1);//interrupt mask reg & TOIE0 enable overflow
    sei();
    DDRC |= (1<<PC0);


    while(1)
    {
        if(overflow>=12)//overflow counting
        {
        if(TCNT1>=64)//ticks counting reg
        {
            PORTC ^= (1<<0);
            TCNT1=0;
            overflow=0;
        }
     }
    }


    return 0;
}
ISR(TIMER1_OVF_vect)
  {
      overflow++;
  }

