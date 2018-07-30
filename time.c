

#include <mega32.h>
#include <delay.h>
flash char display[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90} ;
int sec=0;
int p1,p2=0;
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
TCNT0=0xB2;
sec+=10;
if(sec==1000)
{
 sec=0;
 p1++;
}

if(p1==10)
{
p2++;
p1=0;
if(p2==10){p2=0;}
}


}

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{


}

void main(void)
{
DDRB=0x08;
PORTB=0x00;

DDRC=0xff;
PORTC=0x00;

DDRD=0x03;
PORTD=0x03;

TCCR0=(0<<WGM00) | (1<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0xB2;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<OCIE0) | (1<<TOIE0);

// Global enable interrupts
#asm("sei")

while (1)
      {
       PORTD=0x02;
       PORTC=display[p1];
       delay_ms(10);
       PORTD=0x01;
       PORTC=display[p2];
       delay_ms(10);



      }
}
