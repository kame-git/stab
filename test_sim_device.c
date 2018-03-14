#include "sim_device.h"

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

    /*
    char str[LED_NUM];
    led_state[0] = 1;
    create_led_string(str);
    log_write(LOG_LED_FILE, str, LED_NUM);
    
    led_state[2] = 1;
    create_led_string(str);
    log_write(LOG_LED_FILE, str, LED_NUM);
    */ 
    return 0;
}
