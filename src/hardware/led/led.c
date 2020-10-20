#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx.h"
#include "stm32f7xx_ll_bus.h"

#include "led.h"

typedef struct{
    GPIO_TypeDef* gpioPort;
    uint32_t    gpioPin;
    uint32_t    gpioClock;
}leds_t;

leds_t ledRed = {
    .gpioPort = GPIOB,
    .gpioPin = LL_GPIO_PIN_14,
    .gpioClock = LL_AHB1_GRP1_PERIPH_GPIOB
};

leds_t ledBlue = {
    .gpioPort = GPIOB,
    .gpioPin = LL_GPIO_PIN_7,
    .gpioClock = LL_AHB1_GRP1_PERIPH_GPIOB
};

static void led_init(leds_t *pLed);
static void led_on(leds_t *pLed);
static void led_off(leds_t *pLed);
static void led_toggle(leds_t *pLed);

void leds_init(void)
{
    led_init(&ledRed);
    led_init(&ledBlue);
}

void leds_blueLedSetState(uint8_t state)
{
    if(LEDS_STATE_ON == state)
    {
        led_on(&ledBlue);
    }
    else if(LEDS_STATE_TOGGLE == state)
    {
        led_toggle(&ledBlue);
    }
    else if(LEDS_STATE_OFF == state)
    {
        led_off(&ledBlue);
    }
}

void leds_redLedSetState(uint8_t state)
{
    if(LEDS_STATE_ON == state)
    {
        led_on(&ledRed);
    }
    else if(LEDS_STATE_TOGGLE == state)
    {
        led_toggle(&ledRed);
    }
    else if(LEDS_STATE_OFF == state)
    {
        led_off(&ledRed);
    }
}

static void led_init(leds_t *pLed)
{
    LL_GPIO_InitTypeDef LED_GPIO_User = {0};

    LL_AHB1_GRP1_EnableClock(pLed->gpioClock);

    LED_GPIO_User.Pin = pLed->gpioPin;
    LED_GPIO_User.Mode = LL_GPIO_MODE_OUTPUT;
    LED_GPIO_User.Pull = LL_GPIO_PULL_NO;

    LL_GPIO_Init(pLed->gpioPort, &LED_GPIO_User);
}

static void led_on(leds_t *pLed)
{
    LL_GPIO_SetOutputPin(pLed->gpioPort, pLed->gpioPin);
}

static void led_off(leds_t *pLed)
{
    LL_GPIO_ResetOutputPin(pLed->gpioPort, pLed->gpioPin);
}

static void led_toggle(leds_t *pLed)
{
    LL_GPIO_TogglePin(pLed->gpioPort, pLed->gpioPin);
}
