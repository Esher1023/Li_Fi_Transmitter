/*
 * New_Li_Fi.c
 *
 * Created: 30/10/2019 9:53:43 AM
 * Author : Eshan Wanigasingha
 * AVR code for the ATmega328p
 */ 
#define F_CPU 16000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#define CHAR_LEN 8
#define INIT_LEN 10
#define DELAY 500

void init_protocol ();

int main(void)
{
	DDRB |= 0b00000001;       //PortB, Pin 0 is initialised as the output on the Atmega328p
	unsigned char word[] = "alarm on";    //String to be transmitted through binary.
	int i = 0 ;
	int j = 0;
	
	_delay_us(500);     //Unnecessary delay
	
	while (1)
	{
		init_protocol();    //Sends 10 pulses before the message, inorder communicate the frequency of the data transfer. 

		 i = 0;
		 while ( i < strlen(word) ) { 
			j = 0;
			
			while ( j < CHAR_LEN) {
				if ( ( (1<<(7-j)) & word[i]) != 0) {      //Sends the data with little-endian format  e.g. A = 0b0100 0001
					PORTB = 0b00000001 ;
					_delay_us(DELAY);
					
				} else {
					PORTB = 0b00000000 ;
					_delay_us(DELAY);
					
				}
				
				PORTB = 0b00000000 ;
				_delay_us(DELAY);
				
				
				j ++;
			}
			
			i ++;	
		 }
		 PORTB = 0b00000000 ;
		 _delay_ms(2000);
		 
		
	}

	return 0;
}

void init_protocol() {
	
	int i = 0;
	while ( i < INIT_LEN ) { 
		PORTB = 0b00000001 ;
		_delay_us(DELAY);
		
		PORTB= 0b00000000;
		_delay_us(DELAY);
		
		i ++;
	}
		
}
