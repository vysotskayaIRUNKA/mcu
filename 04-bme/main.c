#include "stdio-task/stdio-task.h"
#include "stdio.h"
#include "stdlib.h"
#include "pico/stdlib.h"
#include "protocol-task.h"
#include "led-task/led-task.h"
#include "hardware/i2c.h"
#include "bme280-driver.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

void rp2040_i2c_read(uint8_t* buffer, uint16_t length)
{
	i2c_read_timeout_us(i2c1, 0x76, buffer, length, false, 100000);
}

void rp2040_i2c_write(uint8_t* data, uint16_t size)
{
	i2c_write_timeout_us(i2c1, 0x76, data, size, false, 100000);
}

void version_callback(const char* args)
{
	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void led_on_callback(const char* args)
{
	printf("led turned on\n");
	led_task_state_set(LED_STATE_ON);
}

void led_off_callback(const char* args)
{
	printf("led turned off\n");
	led_task_state_set(LED_STATE_OFF);

}

void led_blink_callback(const char* args)
{
	printf("led started blinking\n");
	led_task_state_set(LED_STATE_BLINK);
}

void read_regs_callback(const char* args)
{
	uint8_t addr = args[0];
	uint8_t N = args[2];
	uint8_t buffer[256] = {0};
	if (addr<=0xFF && N<=0xFF && (addr+N)<=0x100)
	{
		bme280_read_regs(addr, buffer, N);
		for (int i = 0; i < N; i++)
		{
			printf("bme280 register [0x%X] = 0x%X\n", addr + i, buffer[i]);
		}
	}
}

api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
	{"on", led_on_callback, "make led to turn on"},
	{"off", led_off_callback, "make led to turn off"},
	{"blink", led_blink_callback, "make led blink"},
	{"read_reg", read_regs_callback, "reading device's reg"},
	{NULL, NULL, NULL},
};

int main()
{
	stdio_task_init();
	stdio_init_all();
	protocol_task_init(device_api);
	led_task_init(i2c_read, i2c_write);
	i2c_init(i2c1, 100000);
	gpio_set_function(14, GPIO_FUNC_I2C);
	gpio_set_function(15, GPIO_FUNC_I2C);
	bme280_init();

	while(1)
	{
		char* command = stdio_task_handle();
		led_task_handle();
		protocol_task_handle(command);
	}
}
