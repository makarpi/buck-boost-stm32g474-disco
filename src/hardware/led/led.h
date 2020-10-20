/*
 * file:	led.h
 * author:	makarpi
 * brief:	LED controller
 */

#ifndef _LED_H_
#define _LED_H_

enum {LEDS_STATE_OFF = 0, LEDS_STATE_ON, LEDS_STATE_TOGGLE};

void leds_init(void);
void leds_blueLedSetState(uint8_t state);
void leds_redLedSetState(uint8_t state);

#endif /* _LED_H_ */