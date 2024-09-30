#include "operate.h"

typedef int(*pFunc)(String);
typedef struct{
  String cmdName; 
  pFunc cmdFunc;
} stRecvCmd;

// Prototype declaration
int ledLight(String &param); // Test function
int v_move_forward(String &param);
int v_move_backward(String &param);
int v_rot_left(String &param);
int v_rot_right(String &param);
int v_stop(String &param);
int c_move_upper(String &param);
int c_move_lower(String &param);
int c_stop(String &param);
int h_move_hld(String &param);
int h_move_rls(String &param);
int h_stop(String &param);
int heater_onoff(String &param);
int all_stop(String &param);

// Available command list definition
const int RECV_CMD_NUM = 14;
const stRecvCmd recvCmdList[RECV_CMD_NUM]
{
    {"LEDLIGHT", ledLight},
    {"V_MOVE_FORWARD", v_move_forward},
    {"V_MOVE_BACKWARD", v_move_backward},
    {"V_ROT_LEFT", v_rot_left},
    {"V_ROT_RIGHT", v_rot_right},
    {"V_STOP", v_stop},
    {"C_MOVE_UPPER", c_move_upper},
    {"C_MOVE_LOWER", c_move_lower},
    {"C_STOP", c_stop},
    {"H_MOVE_HLD", h_move_hld},
    {"H_MOVE_RLS", h_move_rls},
    {"H_STOP", h_stop},
    {"HEATER_ONOFF", heater_onoff},
    {"ALL_STOP", all_stop}
};

// Each command function definition
int ledLight(String &param)
{
  Serial.println("ledLight() param: " + param);
  return 0;
}

int v_move_backward(String &param)
{
  Serial.println("v_move_backward() param: " + param);
  contrl_catepillar(CTPL_BKWD);
  return 0;
}

int v_move_forward(String &param)
{
  Serial.println("v_move_forward() param: " + param);
  contrl_catepillar(CTPL_FWRD);
  return 0;
}

int v_rot_left(String &param)
{
  Serial.println("v_rot_left() param: " + param);
  contrl_catepillar(CTPL_LTRN);
  return 0;  
}

int v_rot_right(String &param)
{
  Serial.println("v_rot_right() param: " + param);
  contrl_catepillar(CTPL_RTRN);
  return 0;  
}

int v_stop(String &param)
{
  Serial.println("v_stop() param: " + param);
  contrl_catepillar(CTPL_STOP);
  return 0;
}

int c_move_lower(String &param)
{
  Serial.println("c_move_lower() param: " + param);
  contrl_robot_arm(ARM_DOWN);
  return 0;
}

int c_move_upper(String &param)
{
  Serial.println("c_move_upper() param: " + param);
  contrl_robot_arm(ARM_UP);
  return 0;
}

int c_stop(String &param)
{
  Serial.println("c_stop() param: " + param);
  contrl_robot_arm(ARM_STOP);
  return 0;
}

int h_move_hld(String &param)
{
    Serial.println("h_move_hld() param: " + param);
    contrl_robot_hand(HAND_CLOSE);
    return 0;
}

int h_move_rls(String &param)
{
    Serial.println("h_move_rls() param: " + param);
    contrl_robot_hand(HAND_OPEN);
    return 0;
}

int h_stop(String &param)
{
    Serial.println("h_stop() param: " + param);
    contrl_robot_hand(HAND_REST);
    return 0;
}

int heater_onoff(String &param)
{
    Serial.println("v_heater_onoff() param: " + param);
    
    if (param == "ON")
        contrl_heater(true);
    else if (param == "OFF")
        contrl_heater(false);
    else
        Serial.println("Assert: param = " + param);

    return 0;
}

int all_stop(String &param)
{
    Serial.println("emergency_stop started");
    emergency_stop();
    return 0;
}

