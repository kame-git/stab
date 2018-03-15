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

void log_write(const char *file, const char *str, int len);
void log_read(const char *file, char *str);

#endif /* _LOG_H_ */

