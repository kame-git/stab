#include "log.h"

/** ログ 
 */
void log_write(const char *file, const char *str, int len)
{
    int fd;
    char buf[256];

    if ((fd = open(file, O_WRONLY | O_APPEND)) < 0) {
        sprintf(buf, "can not open %s.", file);
        perror(buf);
        exit(1);
    }

    ssize_t n;
    if ((n = write(fd, str, len)) < 0) {
        sprintf(buf, "can not write %s.", file);
        perror(buf);
        exit(1);
    }

    if ((n = write(fd, "\n", 1)) < 0) {
        sprintf(buf, "can not write %s.", file);
        perror(buf);
        exit(1);
    }

    close(fd);


}

void log_read(const char *file, char *str)
{
    int fd;
    char buf[256];

    if ((fd = open(file, O_RDONLY)) < 0) {
        sprintf(buf, "can not open %s.", file);
        perror(buf);
        exit(1);
    }

    ssize_t n;
    if ((n = read(fd, buf, sizeof(buf))) < 0) {
        sprintf(buf, "can not read %s.", file);
        perror(buf);
        exit(1);
    }

    close(fd);

    strcpy(str, buf);
}

