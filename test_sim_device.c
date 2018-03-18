#include "sim_device.h"

void test_scene1();
void test_scene2();
void test_scene3();
void test_scene4();
void test_scene_timer01();   /* タイマテスト */
void test_integrate01();    /* 統合テスト */
void test_integrate02();

int main()
{
    sim_init_hardware();

    //test_scene1();
    //test_scene2();
    //test_scene3();
    //test_scene4();
    //test_scene_timer01();
    //test_integrate01();    /* 統合テスト */
    test_integrate02();

    return 0;
}
 

/**
 * test_integrate02で使用するコールバック関数
 * @warning リエントラントな関数しか安全でない
 */
void callback02(void)
{
    /* 安全ではない */
/*    printf("activate callback function.\n"); */
    
    /* 安全 */
    /*
    ssize_t n;
    char *buf = "activate callback function.\n";
    if ((n = write(0, buf, strlen(buf))) < 0) {
        perror("write");
        exit(1);
    }
    */
    if (sim_get_led(LED01) == LED_ON) {
        sim_set_led(LED01, LED_OFF);
    } else {
        sim_set_led(LED01, LED_ON);
    }
}

/**
 * 統合テスト　その2
 * スイッチでタイマの制御
 * スイッチ1を押すとタイマ開始、スイッチ2を押すとタイマ停止
 * 端末を3つ開く必要がある。
 * $ ./test_sim_device
 * $ tail -f led_log
 * $ echo "0001" > sw_log
 * @pre sim_init_hardwareを呼び出していること
 */
void test_integrate02() 
{
    SWITCH_STATE sw1_now, sw1_old;
    SWITCH_STATE sw2_now, sw2_old;

    sw1_old = SWITCH_OFF;
    sw2_old = SWITCH_OFF;

    sim_set_itimer(1000, callback02);

    while (1) {
        sw1_now = sim_get_switch(SWITCH01);
        if (sw1_now != sw1_old) {
            if (sw1_now == SWITCH_ON) {
                printf("SW1 is ON.\n");
                printf("timer start\n");
                sim_start_itimer();
            }
            sw1_old = sw1_now;
        } 

        sw2_now = sim_get_switch(SWITCH02);
        if (sw2_now != sw2_old) {
            if (sw2_now == SWITCH_ON) {
                printf("SW2 is ON.\n");
                printf("timer stop\n");
                sim_stop_itimer();
            }
            sw2_old = sw2_now;
        } 
        usleep(500*1000);   /* CPU負荷を低減 */
    }
}

/**
 * 統合テスト　その1
 * スイッチの状態を読出しLEDに反映
 * 端末を3つ開く必要がある。
 * $ ./test_sim_device
 * $ tail -f led_log
 * $ echo "0001" > sw_log
 * @pre sim_init_hardwareを呼び出している
 */
void test_integrate01() 
{
 
    while (1) {
        if (sim_get_switch(SWITCH01) == SWITCH_ON) {
            printf("SW1 is ON.\n");
            sim_set_led(LED01, LED_ON);

            usleep(500*1000);   
        } else {
            printf("SW1 is OFF.\n");
            sim_set_led(LED01, LED_OFF);

            usleep(500*1000);
        }
        if (sim_get_switch(SWITCH02) == SWITCH_ON) {
            printf("SW2 is ON.\n");
            sim_set_led(LED02, LED_ON);

            usleep(500*1000);   
        } else {
            printf("SW2 is OFF.\n");
            sim_set_led(LED02, LED_OFF);

            usleep(500*1000);
        }
    }
}

/**
 * sim_set_led関数のテスト
 */
void test_scene1()
{
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
}

/**
 * log_check_bit関数のテスト
 * 内部でlog_read関数を呼び出しログファイルからデータを取得
 * @warning テスト終了後はlog_check_bit関数をstaticに変更
 */
void test_scene2()
{
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
}

/**
 * sim_get_switch関数のテスト
 */
void test_scene3()
{
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
}

/**
 * create_led_string関数とlog_write関数のテスト
 */
void test_scene4()
{
    char str[LED_NUM];
    led_state[0] = 1;
    create_led_string(str);
    log_write(LOG_LED_FILE, str, LED_NUM);
    
    led_state[2] = 1;
    create_led_string(str);
    log_write(LOG_LED_FILE, str, LED_NUM);
}
/**
 * タイマーのテスト　その1
 * タイマーにコールバック関数をセットして、呼び出される
 * ことを確認
 * @warning リエントラントな関数しか安全でない
 */
void callback(void)
{
    /* 安全ではない */
/*    printf("activate callback function.\n"); */
    
    /* 安全 */
    ssize_t n;
    char *buf = "activate callback function.\n";
    if ((n = write(0, buf, strlen(buf))) < 0) {
        perror("write");
        exit(1);
    }
}

void test_scene_timer01()
{
    sim_set_itimer(1000, callback);
    sim_start_itimer();

    sigset_t set;
    sigemptyset(&set);
    int count = 0;
    while (count++ < 10) {
        sigsuspend(&set);
    }
    sim_stop_itimer();
    sleep(5);
    printf("timer test no.01 finished.\n");
}

