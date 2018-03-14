#ifndef _SIM_DEVICE_H_
#define _SIM_DEVICE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "log.h"

//#define NDEBUG    /* アサーションを無効 */

#define LED_NUM 4
#define SW_NUM 4

typedef enum {
    LED01 = 0x01, LED02 = 0x02, LED03 = 0x04, 
    LED04 = 0x08, LED_ID_NONE = 0x00,
} LED_ID;

typedef enum {
    LED_OFF, LED_ON, LED_STATE_NONE,
} LED_STATE;

typedef enum {
    SWITCH01 = 0x01, SWITCH02 = 0x02, SWITCH03 = 0x04,
    SWITCH04 = 0x08, SWITCH_ID_NONE = 0x00,
} SWITCH_ID;

typedef enum {
    SWITCH_ON, SWITCH_OFF, SWITCH_STATE_NONE,
} SWITCH_STATE;

typedef void (*FUNC)();

void sim_init_hardware();
void sim_set_led(LED_ID led, LED_STATE state);
LED_STATE sim_get_led(LED_ID led);

SWITCH_STATE sim_get_switch(SWITCH_ID sw);
void sim_set_itimer(uint32_t t, FUNC func);
void sim_set_itimer(uint32_t t, FUNC func);
void create_led_string(char *str);

#endif /* _SIM_DEVICE_H_ */

