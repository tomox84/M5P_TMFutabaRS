#include "TMFutabaRS.h"
#include <M5StickCPlus.h>

// Serial2
const int PinRX = 0; // From BTE094 TXD (Blue)
const int PinTX = 26; // From BTE094 RXD (GREEN)

// サーボの定義
TMFutabaRS servo1(1);
TMFutabaRS servo2(2);
TMFutabaRS servo3(3);
TMFutabaRS servo4(4);
TMFutabaRS servo5(5);

void setup() {
  M5.begin();

  // サーボ制御用
  Serial2.begin(115200, SERIAL_8N1, PinRX, PinTX);

  // サーボにサーボ制御用シリアルをセット
  servo1.begin(&Serial2);
  servo2.begin(&Serial2);
  servo3.begin(&Serial2);
  servo4.begin(&Serial2);
  servo5.begin(&Serial2);

  // トップメッセージ
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(GREEN);

  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setCursor(0,3);

  // メモリマップの読み込み
  if (servo1.MemoryMap00to29()) {
    M5.Lcd.println("Ok read 00-29");
    DispSerialMap00to29(&servo1);
  }
  else {
    // 失敗時
    M5.Lcd.println("NG read 00-29");
    Serial.println("NG read 00-29");
  }

  if (servo1.MemoryMap30to59()) {
    M5.Lcd.println("Ok read 40-59");
    DispSerialMap30to59(&servo1);
  }
  else {
    // 失敗時
    M5.Lcd.println("NG read 30-59");
    Serial.println("NG read 30-59");
  }

  if (servo1.MemoryMap42to59()) {
    M5.Lcd.println("Ok read 42-59");
    DispSerialMap42to59(&servo1);
  }
  else {
    // 失敗時
    M5.Lcd.println("NG read 42-59");
    Serial.println("NG read 42-59");
  }

  // 文字のバックの描画
  M5.Lcd.fillRect(0, 135-16, 240, 16, WHITE);
  // 文字の表示
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setCursor(16 + 1, 135-16 + 1);
  M5.Lcd.print("-- Press Buttom --");

  // ボタンの何かを押すまで待機
  while ((M5.BtnA.wasPressed() == false) && (M5.BtnB.wasPressed() == false)) {
    M5.update();
    delay(50);
  }
  M5.update();

  // バックの色
  M5.Lcd.fillScreen(BLUE);
  // 文字の色
  M5.Lcd.setTextColor(WHITE, BLUE);

  // トルクオン
  servo1.TorqueOn();
  servo2.TorqueOn();
  servo3.TorqueOn();
  servo4.TorqueOn();
  servo5.TorqueOn();

  // 0度へ移動
  servo1.Move(0, 10);
  servo2.Move(0, 10);
  servo3.Move(0, 10);
  servo4.Move(0, 10);
  servo5.Move(0, 10);

  // 情報表示のバックの表示
  M5.Lcd.setCursor(6, 20);
  M5.Lcd.print("Srv1");
  M5.Lcd.setCursor(6, 40);
  M5.Lcd.print("Srv2");
  M5.Lcd.setCursor(6, 60);
  M5.Lcd.print("Srv3");
  M5.Lcd.setCursor(6, 80);
  M5.Lcd.print("Srv4");
  M5.Lcd.setCursor(6, 100);
  M5.Lcd.print("Srv5");
}

void loop() {
  // --Servo1 情報表示
  M5.Lcd.setCursor(65, 20);
  if (servo1.MemoryMap42to59()) {
    float pos = (float)(servo1.CurrentPosition) * 0.1;
    int cur = servo1.CurrentCurrent;
    M5.Lcd.printf("%5.1fdeg %3dmA", pos, cur);
  }
  else {
    M5.Lcd.print("N/A           ");
  }

  M5.Lcd.setCursor(65, 40);
  if (servo2.MemoryMap42to59()) {
    float pos = (float)(servo2.CurrentPosition) * 0.1;
    int cur = servo2.CurrentCurrent;
    M5.Lcd.printf("%5.1fdeg %3dmA", pos, cur);
  }
  else {
    M5.Lcd.print("N/A           ");
  }

  M5.Lcd.setCursor(65, 60);
  if (servo3.MemoryMap42to59()) {
    float pos = (float)(servo3.CurrentPosition) * 0.1;
    int cur = servo3.CurrentCurrent;
    M5.Lcd.printf("%5.1fdeg %3dmA", pos, cur);
  }
  else {
    M5.Lcd.print("N/A           ");
  }

  M5.Lcd.setCursor(65, 80);
  if (servo4.MemoryMap42to59()) {
    float pos = (float)(servo4.CurrentPosition) * 0.1;
    int cur = servo4.CurrentCurrent;
    M5.Lcd.printf("%5.1fdeg %3dmA", pos, cur);
  }
  else {
    M5.Lcd.print("N/A           ");
  }

  M5.Lcd.setCursor(65, 100);
  if (servo5.MemoryMap42to59()) {
    float pos = (float)(servo5.CurrentPosition) * 0.1;
    int cur = servo5.CurrentCurrent;
    M5.Lcd.printf("%5.1fdeg %3dmA", pos, cur);
  }
  else {
    M5.Lcd.print("N/A           ");
  }
  
  // ボタン
  if (M5.BtnA.wasPressed()) {
    servo1.Pos(1000);
    servo2.Pos(0);
    servo3.Pos(500);
    servo4.Pos(-400);
    servo5.Pos(800);
  }
  if (M5.BtnB.wasPressed()) {
    servo1.Pos(100);
    servo2.Pos(1000);
    servo3.Pos(-500);
    servo4.Pos(500);
    servo5.Pos(-800);
  }

  M5.update();
  delay(50);

}



/*-------------------------------------------------
  名前: メモリマップの表示
  機能: DispSerialMap00to29
  引数
    srv: 表示するサーボ
  戻値: なし
  -------------------------------------------------*/
void DispSerialMap00to29(TMFutabaRS *srv) {
  Serial.println("-- Memory map 00-29 ---------------");
  Serial.printf(" Model                  : %s\n", srv->ModelString());
  Serial.printf(" Firmware Version       : %02X\n", srv->FirmwareVersion);
  Serial.printf(" ID                     : %02X\n", srv->ID);
  Serial.printf(" Reverse                : %s\n", srv->isReverse ? "false" : "true");
  Serial.printf(" Baud Rate              : %d bps\n", srv->BaudRate());
  Serial.printf(" Return Delay           : %d usec\n", srv->ReturnDelayMicroSec);
  Serial.printf(" Right Limit Angle      : %-+3.1f deg\n", (float)(srv->LimitAngleR) * 0.1);
  Serial.printf(" Left  Limit Angle      : %-+3.1f deg\n", (float)(srv->LimitAngleL) * 0.1);
  Serial.printf(" Temperature Limit      : %d deg\n", srv->LimitTemp);
  Serial.printf(" Torque In Silence      : %s\n", srv->TorqueInSilenceString());
  Serial.printf(" Warm-up Time           : %1.2f sec\n", (float)(srv->WarmUpTime) * 0.01);
  Serial.printf(" Right Compliance Margin: %2.1f deg\n", (float)(srv->ComplianceMarginR) * 0.1);
  Serial.printf(" Left  Compliance Margin: %2.1f deg\n", (float)(srv->ComplianceMarginL) * 0.1);
  Serial.printf(" Right Compliance Slope : %d deg\n", srv->ComplianceSlopeR);
  Serial.printf(" Left  Compliance Slope : %d deg\n", srv->ComplianceSlopeL);
  Serial.printf(" Punch                  : %3.2f %%\n", (float)(srv->Punch) * 0.01);
  Serial.println("-----------------------------------");
}

/*-------------------------------------------------
  名前: メモリマップの表示
  機能: DispSerialMap30to59
  引数
    srv: 表示するサーボ
  戻値: なし
  -------------------------------------------------*/
void DispSerialMap30to59(TMFutabaRS *srv) {
  Serial.println("-- Memory map 30-59 ---------------");
  Serial.printf(" Goal Position          : %3.1f deg\n", (float)(srv->GoalPosition) * 0.1);
  Serial.printf(" Goal Time              : %d msec\n", srv->GoalTime);
  Serial.printf(" Max Torque             : %d %%\n", srv->MaxTorque);
  Serial.printf(" Torque Mode            : %s\n", srv->TorqueModeString());
  Serial.printf(" Current Position       : %3.1f deg\n", (float)(srv->CurrentPosition) * 0.1);
  Serial.printf(" Current Time           : %d msec\n", srv->CurrentTime * 10);
  Serial.printf(" Current Speed          : %d deg/sec\n", srv->CurrentSpeed);
  Serial.printf(" Current Current        : %d mA\n", srv->CurrentCurrent);
  Serial.printf(" Current Temperature    : %d deg\n", srv->CurrentTemperature);
  Serial.printf(" Current Volts          : %1.2f V\n", srv->CurrentVolts * 0.01);
  Serial.println("-----------------------------------");
}

/*-------------------------------------------------
  名前: メモリマップの表示
  機能: DispSerialMap42to59
  引数
  srv: 表示するサーボ
  戻値: なし
  -------------------------------------------------*/
void DispSerialMap42to59(TMFutabaRS *srv) {
  Serial.println("-- Memory map 42-59 ---------------");
  Serial.printf(" Current Position       : %3.1f deg\n", (float)(srv->CurrentPosition) * 0.1);
  Serial.printf(" Current Time           : %d msec\n", srv->CurrentTime);
  Serial.printf(" Current Speed          : %d deg/sec\n", srv->CurrentSpeed);
  Serial.printf(" Current Current        : %d mA\n", srv->CurrentCurrent);
  Serial.printf(" Current Temperature    : %d deg\n", srv->CurrentTemperature);
  Serial.printf(" Current Volts          : %1.2f V\n", srv->CurrentVolts * 0.01);
  Serial.println("-----------------------------------");
}
