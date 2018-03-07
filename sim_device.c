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
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

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
    SWITCH01 = 0x01, SWITHC02 = 0x02, SWITCH03 = 0x04,
    SWITCH04 = 0x08, SWITCH_ID_NONE = 0x00,
} SWITCH_ID;

typedef enum {
    SWITCH_ON, SWITCH_OFF, SWITCH_STATE_NONE,
} SWITCH_STATE;

LED_STATE led_state[LED_NUM];   /**< LEDの状態 */
SWITCH_STATE sw_state[SW_NUM];     /**< SWの状態 */
void (*func)();         /**< タイマー用コールバック関数 */

/** 初期化関数 */
void sim_init_hardware()
{
    int i;

    for (i = 0; i < LED_NUM; i++)
        led_state[i] = LED_OFF;

    for (i = 0; i < SW_NUM; i++)
        sw_state[i] = SWITCH_OFF;

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
static char *create_led_string(LED_ID led, LED_STATE state,
        const char* str)
{

    return NULL;
}


/** スイッチ制御 */
SWITCH_STATE sim_get_switch(SWITCH_ID sw)
{

    return SWITCH_STATE_NONE;
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
static void log_write(FILE *fp, const char *str)
{

}

static void log_read(FILE *fp, char *str)
{

}

int main()
{

    sim_init_hardware();

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

    return 0;
}

