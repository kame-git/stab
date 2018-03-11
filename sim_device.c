/**
 * @brief シミュレーション用デバイスドライバ
 * @detail NEP資料「構造化分析演習」で使用する。LEDと
 * スイッチとタイマをシミュレーションする。
 * - LEDの点灯状況はログファイルに書き込むため、別の
 *   ターミナルから「tail -f」で書き込み状況の確認が
 *   可能。ただし、tail -fは1秒間隔程度で内容を確認
 *   しているため、ログへの書き込み速度が速いとうまく
 *   表示されない。
 * - ログに書き込まれたスイッチの状態を読み出す。ログ
 *   には「echo "～" > ファイル名」で書込む。
 * - タイマはLinuxのSIGALMを使用する。
 */
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

//#define NDEBUG    /* アサーションを無効 */

#define LED_NUM 4
#define SW_NUM 4

#define LOG_SW_FILE "sw_log"
#define LOG_LED_FILE "led_log"

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

/* グローバル変数 */
LED_STATE led_state[LED_NUM];   /**< LEDの状態 */
SWITCH_STATE sw_state[SW_NUM];     /**< SWの状態 */
void (*func)();         /**< タイマー用コールバック関数 */

/* プロトタイプ宣言 */
static bool log_check_bit(int sw);
static void create_led_string(char *str);
static void log_write(const char *file, const char *str);

/** 初期化関数 */
void sim_init_hardware()
{
    int i;

    for (i = 0; i < LED_NUM; i++)
        led_state[i] = LED_OFF;

    for (i = 0; i < SW_NUM; i++)
        sw_state[i] = SWITCH_OFF;

    /** ログで使用するファイルの作成 */
    char buf[256];
    int fd;
    if ((fd = open(LOG_SW_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
        sprintf(buf, "can not open %s.", LOG_SW_FILE);
        perror(buf);
        exit(1);
    }
    
    /** 初期値の書込み */
    strcpy(buf, "0000");
    int n;
    if ((n = write(fd, buf, strlen(buf))) < 0) {
        sprintf(buf, "can not open %s.", LOG_SW_FILE);
        perror(buf);
        exit(1);
    }

    close(fd);

    if ((fd = open(LOG_LED_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
        sprintf(buf, "can not open %s.", LOG_LED_FILE);
        perror(buf);
        exit(1);
    }

    close(fd);

    func = NULL;
}

/** LED制御 */
void sim_set_led(LED_ID led, LED_STATE state)
{
    int i;

    assert(led == LED01 || led == LED02 || led == LED03 || led == LED04);
    assert(state == LED_ON || state == LED_OFF);

    for (i = 0; i < LED_NUM; i++) {
        if ((led >> i) & 0x01)
            led_state[i] = state;
    }

	char led_str[LED_NUM] = {'-'};
	/* グローバル変数led_state配列からログ出力用の文字列を生成 */
	create_led_string(led_str);	
	log_write(LOG_SW_FILE, led_str);
}

LED_STATE sim_get_led(LED_ID led)
{
    int i;

    assert(led == LED01 || led == LED02 || led == LED03 || led == LED04);

    for (i = 0; i < LED_NUM; i++) {
        if ((led >> i) & 0x01)
            return led_state[i];
    }

    assert(false);  /* 未到達のはず */

    return LED_STATE_NONE;
}

/** LEDの状態をログに書き込むための文字列生成 */
//static char *create_led_string(LED_ID led, LED_STATE state, char* str)
static void create_led_string(char *str)
{

	/*
	int i;

	for (i = 0; i < SW_NUM; i++) {
		if (led  >> (SW_NUM-i-1)) {
			if (state == LED_ON) {
				*(str+i) = '*';
			} else {
				*(str+i)= '-';
			}
			break;
		} else {
			if (led_state[i] == LED_ON)
				*(str+i) = '*';
			else 
				*(str+i) = '-';
		}
	} 

    return str;
	*/
}


/** スイッチ制御 */
SWITCH_STATE sim_get_switch(SWITCH_ID sw)
{
	bool ret =log_check_bit(sw);
	
	if (ret)
		return SWITCH_OFF;
	else
		return SWITCH_ON;
}

typedef void (*FUNC)();

/** タイマ制御 
 * 指定された時間でコールバック関数を実行する。
 * @param[in] t 時間[m秒]
 * @param[in] func 関数ポインタ
 */
void sim_set_itimer(uint32_t t, FUNC func)
{

}

/** ログ 
 * @TODO 標準ライブラリ関数は使用できない。
 */
static void log_write(const char *file, const char *str)
{

}

static void log_read(const char *file, char *str)
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
    printf("log read : %s\n", str);
}

/** ログから取得したデータのビットオンオフの確認 */
static bool log_check_bit(int sw)
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

int main()
{

    sim_init_hardware();

    /*
    LED_STATE ls = sim_get_led(LED01);
    printf("LED01=%d\n", ls);
    sim_set_led(LED01, LED_ON);
    ls = sim_get_led(LED01);
    printf("LED01=%d\n", ls);
    sim_set_led(LED02, LED_ON);
    sim_set_led(LED03, LED_ON);
    sim_set_led(LED04, LED_ON);
    sim_set_led(LED01, LED_OFF);
    sim_set_led(LED02, LED_OFF);
    sim_set_led(LED03, LED_OFF);
    sim_set_led(LED04, LED_OFF);
    */

    /*
    char str[256];
    log_read(LOG_SW_FILE, str);
    */

	/*
    if (log_check_bit(SWITCH03)) {
        printf("sw3 is pressed.\n");
    } else {
        printf("sw3 is no pressed.\n");
    }

    if (log_check_bit(SWITCH03)) {
        printf("sw3 is pressed.\n");
    } else {
        printf("sw3 is no pressed.\n");
    }
	*/

	/*
	if(sim_get_switch(SWITCH01)) {
		printf("SW1 is ON.\n");
	} else {
		printf("SW1 is OFF.\n");
	}

	if(sim_get_switch(SWITCH01)) {
		printf("SW1 is ON.\n");
	} else {
		printf("SW1 is OFF.\n");
	}
	*/

	/* 間違い！ */
	/*
	char led_str[LED_NUM];
	char *str = create_led_string(LED01, LED_ON, led_str);
	int i;
	for (i = 0; i < LED_NUM; i++)
		putchar(led_str[i]);
	putchar('\n');

	str = create_led_string(LED01, LED_OFF, led_str);
	for (i = 0; i < LED_NUM; i++)
		putchar(led_str[i]);
	putchar('\n');

	str = create_led_string(LED02, LED_ON, led_str);
	for (i = 0; i < LED_NUM; i++)
		putchar(led_str[i]);
	putchar('\n');

	str = create_led_string(LED02, LED_OFF, led_str);
	for (i = 0; i < LED_NUM; i++)
		putchar(led_str[i]);
	putchar('\n');
	*/

    return 0;
}

