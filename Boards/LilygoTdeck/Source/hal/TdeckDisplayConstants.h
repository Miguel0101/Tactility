#pragma once

#define TDECK_LCD_SPI_HOST SPI2_HOST
#define TDECK_LCD_PIN_CS GPIO_NUM_12
#define TDECK_LCD_PIN_DC GPIO_NUM_11 // RS
#define TDECK_LCD_PIN_BACKLIGHT GPIO_NUM_42
#define TDECK_LCD_SPI_FREQUENCY 40000000
#define TDECK_LCD_HORIZONTAL_RESOLUTION 320
#define TDECK_LCD_VERTICAL_RESOLUTION 240
#define TDECK_LCD_BITS_PER_PIXEL 16
#define TDECK_LCD_DRAW_BUFFER_HEIGHT (TDECK_LCD_VERTICAL_RESOLUTION / 10)
#define TDECK_LCD_SPI_TRANSFER_HEIGHT (TDECK_LCD_VERTICAL_RESOLUTION / 10)

// Backlight (PWM)
#define TDECK_LCD_BACKLIGHT_LEDC_TIMER LEDC_TIMER_0
#define TDECK_LCD_BACKLIGHT_LEDC_MODE LEDC_LOW_SPEED_MODE
#define TDECK_LCD_BACKLIGHT_LEDC_CHANNEL LEDC_CHANNEL_0
#define TDECK_LCD_BACKLIGHT_LEDC_DUTY_RES LEDC_TIMER_8_BIT
#define TDECK_LCD_BACKLIGHT_LEDC_FREQUENCY (4000)
