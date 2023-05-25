#include <atmel_start.h>
#include <usart_basic_example.h>
#include <atomic.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	ENABLE_INTERRUPTS();
	/* Replace with your application code */
	while (1) {
		//USART_0_test_usart_basic();
		char c = USART_0_read();
		USART_0_write(c);
	}
}
