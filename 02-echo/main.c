#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>


#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

uint32_t global_variable = 0;
const uint32_t constant_variable = 42;

int main()
{
	stdio_init_all();
	printf("Hello World!\n");
	while(1)
	{
		char symbol = getchar();
		printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);
	}
}
