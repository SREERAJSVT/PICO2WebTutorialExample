#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LED_PIN PICO_DEFAULT_LED_PIN
#define LED_DELAY_MS 500
#define TEMP_SENSOR_CHANNEL 4  // ADC channel for internal temperature sensor



int main()
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    adc_init();
    adc_select_input(TEMP_SENSOR_CHANNEL);
    
    while (true) {
        printf("Hello, From Pico 2 RP !\n");
        sleep_ms(1000);
         // Blink LED
        gpio_put(LED_PIN, 1);
        sleep_ms(LED_DELAY_MS);
        gpio_put(LED_PIN, 0);
        sleep_ms(LED_DELAY_MS);

        // Read internal temperature and convert to Celsius
        uint16_t raw = adc_read();
        float voltage = raw * 3.3f / (1 << 12);
        float temperature = 27.0f - (voltage - 0.706) / 0.001721;

        // Output temperature via USB serial
        printf("Internal Temperature: %.2f C\n", temperature);
        sleep_ms(1000);  // Delay for temperature reading
    }
}
