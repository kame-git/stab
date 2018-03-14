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
#include "log.h"

/* グローバル変数 */
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
    log_write(LOG_LED_FILE, led_str, LED_NUM);
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

/**
 * LEDの状態を文字列に変換
 * グローバル変数led_stateを確認して文字列(点灯:*、消灯:-)を生成する。
 * @param[inout] str 生成した文字列を格納
 */
void create_led_string(char *str)
{
    int i;

    for (i = 0; i < LED_NUM; i++) {
        if (led_state[SW_NUM-i-1] == LED_ON)
            *(str+i) = '*';
        else
            *(str+i) = '-';
    }
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


/** タイマ制御 
 * 指定された時間でコールバック関数を実行する。
 * @param[in] t 時間[m秒]
 * @param[in] func 関数ポインタ
 */
void sim_set_itimer(uint32_t t, FUNC func)
{

}

