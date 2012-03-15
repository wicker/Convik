/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#include "config.h"
#include "core/pwm.h"
#include "core/usart.h"
#include "utils/char_fifo.h"

#include <avr/io.h>
#include <util/delay.h>

void delayms(uint16_t millis) {
	while ( millis ) {
		_delay_ms(1);
		millis--;
	}
}

int main(void) {
	DDRB |= 1<<PB0; // data direction register, PB0 pin, <avr/io.h>
	usart_init(); // <core/usart.h>
	pwm_init(); // <core/pwm.h>
	pwm_set(0); // <core/pwm.h>
	char ch; // because we send chars

	while(1) {
		// usart_recv_fifo() <core/usart.h>
		// char_fifo_is_empty() <utils/char_fifo.h>
		if(char_fifo_is_empty(usart_recv_fifo()))
			// char_fifo_pop() <core/usart.h>
			char_fifo_pop(usart_recv_fifo(), &ch);
			// usart_send_char(); <core/usart.h>
			usart_send_char(ch);
	}
	return 0;
}

