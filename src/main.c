
/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#include "platform.h"
#include "system_stm32g4xx.h"

#include "hrtim.h"


/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
int i = 0;
float dutyCycle = 0.0f;

int main(void)
{
  SystemInit();
  SystemClock_Config();

  LL_GPIO_InitTypeDef LED_GPIO_User = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

  LED_GPIO_User.Pin = LL_GPIO_PIN_15;
  LED_GPIO_User.Mode = LL_GPIO_MODE_OUTPUT;
  LED_GPIO_User.Pull = LL_GPIO_PULL_NO;

  LL_GPIO_Init(GPIOA, &LED_GPIO_User);

  LED_GPIO_User.Pin = LL_GPIO_PIN_1;

  LL_GPIO_Init(GPIOB, &LED_GPIO_User);

  LED_GPIO_User.Pin = LL_GPIO_PIN_5;

  LL_GPIO_Init(GPIOB, &LED_GPIO_User);

  LED_GPIO_User.Pin = LL_GPIO_PIN_7;

  LL_GPIO_Init(GPIOB, &LED_GPIO_User);

  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
  // LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
  // LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_15);

  hrtim_init();

  while (1)
  {
    LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_1);
    LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_5);
    LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_7);
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_15);
    
    LL_HRTIM_TIM_SetCompare1(HRTIM1, LL_HRTIM_TIMER_D, 54400U * dutyCycle);

    dutyCycle += 0.01f;
    if(dutyCycle > 1.0f)
    {
      dutyCycle = 0.0f;
    }

    for(i = 0; i < 1000000; i++)
    {

    }
  }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4)
  {
  }
  LL_PWR_EnableRange1BoostMode();
  LL_RCC_HSI_Enable();
   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  LL_RCC_HSI_SetCalibTrimming(64);
  LL_RCC_HSI48_Enable();
   /* Wait till HSI48 is ready */
  while(LL_RCC_HSI48_IsReady() != 1)
  {
  }

  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_EnableDomain_SYS();
  LL_RCC_PLL_Enable();
   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Insure 1�s transition state at intermediate medium speed clock based on DWT */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
  while(DWT->CYCCNT < 100);
  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_SetSystemCoreClock(170000000);

   /* Update the time base */
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_HSI48);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);
  LL_RCC_SetADCClockSource(LL_RCC_ADC12_CLKSOURCE_SYSCLK);
}