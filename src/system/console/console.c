#include "platform.h"

#include "console.h"
#include "usart.h"

#define WELCOME_MESSAGE     "Hello World!\r\n" \
                            "STM32F767ZI 216MHz\r\n"

static void console_putWelcomeMessage(void);

void console_init(void)
{
    usart_init();
    
    console_putWelcomeMessage();
}

static void console_putWelcomeMessage(void)
{
    usart_puts(WELCOME_MESSAGE);
}
