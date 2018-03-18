# デバイスシミュレーション用
LED、スイッチとタイマをシミュレーションする。LEDはファイル(led_log)に出力する。スイッチはファイル(sw_log)から読み取る。

## 使い方
``` $ ./test_sim_device ```  
``` $ tail -f led_log ```  
スイッチ1をオンにする例  
``` $ echo "0001" > sw_log ```

## シミュレーション用関数一覧
* シミュレーション環境初期化関数
> void sim_init_hardware();
* LEDの点滅制御
> void sim_set_led(LED_ID led, LED_STATE state);
* LEDの状態取得
> LED_STATE sim_get_led(LED_ID led);
* スイッチの状態取得
> SWITCH_STATE sim_get_switch(SWITCH_ID sw);
* タイマの周期とコールバック関数の設定
> void sim_set_itimer(uint32_t t, FUNC func);
* タイマ開始
> void sim_start_itimer();
* タイマ停止
> void sim_stop_itimer();
* LEDログファイルに書込むデータ(*:点灯、-:消灯)を生成
> void create_led_string(char *str);
* スイッチ用ログファイルから取得したデータからオン・オフを判断
> bool log_check_bit(int sw);

## TODO
* タイマ関数の引数エラーチェックを行うこと
* 複数のタイマを設定できるように修正すること
* LEDの状態確認用のプログラムを(tail -fではなく)別途作成すること
* スイッチの状態変化のプログラムを(echoではなく)別途作成すること
* 周辺機器の制御をGUIで行えるように、GUIのアプリケーションを作成すること
    * GUIアプリとはソケットなどの通信を利用すること

