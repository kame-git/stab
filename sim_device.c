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

#include <stdlib.h>
#include <stdint.h>

/** 初期化関数 */
void sim_init_hardware()
{

}

typedef enum {
    LED01, LED02, LED03, LED04, LED_ID_NONE,
} LED_ID;

typedef enum {
    LED_ON, LED_OFF, LED_STATE_NONE,
} LED_STATE;

/** LED制御 */
void sim_set_led(LED_ID led, LED_STATE state)
{

}

LED_STATE sim_get_led(LED_ID led)
{

    return LED_STATE_NONE;
}

/** LEDの状態をログに書き込むための文字列生成 */
static char *create_led_string(LED_ID led, LED_STATE state,
        const char* str)
{

    return NULL;
}

typedef enum {
    SWITCH01, SWITHC02, SWITCH03, SWITCH04, SWITCH_ID_NONE,
} SWITCH_ID;

typedef enum {
    SWITCH_ON, SWITCH_OFF, SWITCH_STATE_NONE,
} SWITCH_STATE;

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

int main()
{

    return 0;
}

