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
    /*
    printf("log read : %s\n", str);
    */
}

/** ログから取得したデータのビットオンオフの確認 */
bool log_check_bit(int sw)
{
    char str[256];

    log_read(LOG_SW_FILE, str);

    int i;
    char ch;
    for (i = 0; i < SW_NUM; i++) {
        if ((sw >> i) & 0x01) {
            ch = str[SW_NUM-i-1];
            if (ch == '1') {
                return true;
            } else {
                return false;
            }
        }
    }

    return false;
}

