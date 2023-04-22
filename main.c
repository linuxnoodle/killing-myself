#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/adc.h"

// BEGIN LED
#define RED 4
#define GREEN 5
#define BLUE 6
// END LED

// BEGIN ADC
#define ADC_PIN 26
#define ADC_VREF 3.3
#define ADC_CONV ADC_VREF / (1 << 12)
// END ADC

// range from 30g to 1000g
// BEGIN THRESHOLD
#define RED_THRES_MIN 30
#define RED_THRES_MAX 300

#define GREEN_THRES_MIN 301
#define GREEN_THRES_MAX 600

#define BLUE_THRES_MIN 601
#define BLUE_THRES_MAX 1000
// END THRESHOLD

double grams = 0; 

void loop(){
    if (grams >= RED_THRES_MIN && grams <= RED_THRES_MAX){
        gpio_put(RED, 1);
        printf("RED LED ON\n");
    } else {
        gpio_put(RED, 0);
    }

    if (grams >= GREEN_THRES_MIN && grams <= GREEN_THRES_MAX){
        gpio_put(GREEN, 1);
        printf("GREEN LED ON\n");
    } else {
        gpio_put(GREEN, 0);
    }

    if (grams >= BLUE_THRES_MIN && grams <= BLUE_THRES_MAX){
        gpio_put(BLUE, 1);
        printf("BLUE LED ON\n");
    } else {
        gpio_put(BLUE, 0);
    }
    
    uint16_t adcRaw = adc_read();
    double voltage = adcRaw * ADC_CONV;
    printf("ADC %d, %fV\n", adcRaw, voltage);

    grams = 172014.0 * voltage - 288505.0;

    if (grams < 30){
        grams = 30;
    } else if (grams > 1000){
        grams = 1000;
    }

    // print to first decimal place
    printf("Grams: %d\n\n", (int)grams);
}

int main(){
    // initialization
    stdio_init_all();
    
    gpio_init(RED);
    gpio_init(BLUE);
    gpio_init(GREEN);
    gpio_init(23);
    
    gpio_set_dir(RED, GPIO_OUT);
    gpio_set_dir(BLUE, GPIO_OUT);
    gpio_set_dir(GREEN, GPIO_OUT);

    // decrease switching noise
    gpio_set_dir(23, GPIO_OUT);
    gpio_put(23, 1);

    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(0);
    
    while (1){
        loop();
        sleep_ms(10000);
    }
    return 0;
}
