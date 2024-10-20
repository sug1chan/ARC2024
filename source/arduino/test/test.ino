#include "commander.h"
#include "operate.h"

#define CMD_RST (0x00)
#define CMD_FWD (0x0A)
#define CMD_BWD (0x05)
#define CMD_RTN (0x09)
#define CMD_LTN (0x06)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  init_pinMode();
}

void loop() {
  // put your main code here, to run repeatedly:
  int optcat[4] = {
    CMD_FWD,
    CMD_BWD,
    CMD_RTN,
    CMD_LTN
  };
  int optarm[4] = {
    ARM_REST,
    ARM_UP,
    ARM_DOWN,
    ARM_STOP
  };

//デバッグしたい箇所のコメントアウトを外してデバッグを実行する
  for(int i = 0; i < 4; i++){
    //cmd_move_catepillar(optcat[i]);
    //delay(1000);
    //cmd_move_catepillar(CMD_RST);
    //delay(1000);
    //cmd_change_slowmode(CAT_MODE_SLOW);
    //delay(1000);
    //cmd_change_slowmode(CAT_MODE_NORMAL);
    //delay(1000);
    //cmd_turn_onoff_heater(HEATER_ON);
    //delay(1000);
    //cmd_turn_onoff_heater(HEATER_OFF);
    //delay(1000);
    //cmd_move_arm(optarm[i]);
    //delay(1000);
    cmd_emergency_stop(i);
    delay(1000);
  }
}
