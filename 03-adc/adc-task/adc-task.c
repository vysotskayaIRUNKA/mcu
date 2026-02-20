#include "hardware/adc.h"
#include "stdio.h"
#include "pico/stdlib.h"

const uint LEG_ADC = 26;
const uint ADC_CHANNEL = 0;
const uint ADC_CHANNEL_TEMP = 4;

void adc_task_init()
{
    adc_init();
    adc_gpio_init(LEG_ADC);
    adc_set_temp_sensor_enabled(true);
}

float voltage_measure()
{
    adc_select_input(ADC_CHANNEL);
    uint16_t voltage_count = adc_read();
    return voltage_count/4095.0 * 3.3;
}

float temp_measure()
{
    adc_select_input(ADC_CHANNEL_TEMP);
    uint16_t temp_counts = adc_read();
    float temp_V = temp_counts/4095.0 * 3.3;
    return 27.0f - (temp_V - 0.706f) / 0.001721f;
}
