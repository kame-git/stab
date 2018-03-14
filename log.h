#ifndef _LOG_H_
#define _LOG_H_

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

#include "sim_device.h"

#define LOG_SW_FILE "sw_log"
#define LOG_LED_FILE "led_log"

void log_write(const char *file, const char *str, int len);
void log_read(const char *file, char *str);
bool log_check_bit(int sw);

#endif /* _LOG_H_ */

