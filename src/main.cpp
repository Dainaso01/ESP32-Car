#include <Arduino.h>
#include <ESP32Servo.h>
#include <PS4Controller.h>

Servo servo1;
Servo servo2;

void setup() {
    Serial.begin(115200);
    
    // サーボモーターのピンを設定
    servo1.attach(18);  // 今回はGPIO 18
    servo2.attach(19);  // 今回はGPIO 19
    
    // PS4コントローラーの接続
    PS4.begin("78:21:84:c4:5c:ba");  // ここに使う予定のPS4コントローラーのMACアドレスを入力
    
    Serial.println("Ready to connect to PS4 Controller...");
}

void loop() {
    if (PS4.isConnected()) {
        // デッドゾーンの設定
        int deadzone = 40; // ドリフトを除去するためのデッドゾーンの範囲
        
        // 例として左スティックと右スティックのY軸でサーボを制御
        int lStickY = PS4.RStickY();
        int rStickY = PS4.LStickY();
        
        // スティックの値をサーボモーターのポジションにマッピング
        int servo1Position = map(lStickY, -128, 127, 180, 0);
        int servo2Position = map(rStickY, -128, 127, 0, 180);
        
        // デッドゾーン処理
        if (abs(servo1Position - 90) < deadzone) {
            servo1Position = 90;  // 中央位置に設定
        }

        if (abs(servo2Position - 90) < deadzone) {
            servo2Position = 90;  // 中央位置に設定
        }
      
        servo1.write(servo1Position);
        servo2.write(servo2Position);
        
        Serial.print("Servo 1 Position: ");
        Serial.print(servo1Position);
        Serial.print(" | Servo 2 Position: ");
        Serial.println(servo2Position);
        
        delay(20);  // スムーズな動作のために少し遅延を入れる
    }
}
