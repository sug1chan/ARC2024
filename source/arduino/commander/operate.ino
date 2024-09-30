#include "operate.h"

// parser
typedef struct {
    short ln;
    short lr;
    short rn;
    short rr;
} signal;

void get_cmd(opr op, signal* sig);

void DEBUG_FUNCNAME(char* name);
void DEBUG_FLAG(signal* sig);
void DEBUG_PARAM(int pwm_normal, int pwm_reverse);
void DEBUG_PARAMRIGHT(int pwm_normal, int pwm_reverse);
void DEBUG_PARAMLEFT(int pwm_normal, int pwm_reverse);
void DEBUG_HEATER(bool is_on);

// setup
void init_pinMode(void) {
    // pin mode
    Serial.println("init pinMode: Start");
    pinMode(HEATER,           OUTPUT);
    pinMode(ROBOT_ARM_UP,     OUTPUT);
    pinMode(ROBOT_ARM_DOWN,   OUTPUT);
    pinMode(ROBOT_HAND_OPEN,  OUTPUT);
    pinMode(ROBOT_HAND_CLOSE, OUTPUT);
    pinMode(L_CATEPILLAR,     OUTPUT);
    pinMode(L_CATEPILLAR_REV, OUTPUT);
    pinMode(R_CATEPILLAR,     OUTPUT);
    pinMode(R_CATEPILLAR_REV, OUTPUT);
    Serial.println("init pinMode: Finish");
}

void init_robot_operate(void) {
    contrl_robot_arm(ARM_STOP);
    return;
}

// operate

bool contrl_catepillar(opr op) {
    // control catepillar!
    signal sig;
    int pwm_left_normal, pwm_left_reverse, pwm_right_normal, pwm_right_reverse;

//    Serial.println(CTPL_STOP, BIN);
    if (op == CTPL_STOP) {
        pwm_left_normal     = 255;
        pwm_left_reverse    = 255;
        pwm_right_normal    = 255;
        pwm_right_reverse   = 255;
//        analogWrite(L_CATEPILLAR    , 255);
//        analogWrite(L_CATEPILLAR_REV, 255);
//        analogWrite(R_CATEPILLAR    , 255);
//        analogWrite(R_CATEPILLAR_REV, 255);
    } else {
        get_cmd(op, &sig);

        pwm_left_normal     = PWM_L_CATE_DEFAULT     * sig.ln;
        pwm_left_reverse    = PWM_L_CATE_REV_DEFAULT * sig.lr;
        pwm_right_normal    = PWM_R_CATE_DEFAULT     * sig.rn;
        pwm_right_reverse   = PWM_R_CATE_REV_DEFAULT * sig.rr;
    }

    // logging
    DEBUG_FUNCNAME("contrl_catepillar");
    DEBUG_PARAMLEFT(pwm_left_normal,   pwm_left_reverse);
    DEBUG_PARAMRIGHT(pwm_right_normal, pwm_right_reverse);

//    get_cmd(op, &sig);

    // operate DC Morter
    analogWrite(L_CATEPILLAR    , pwm_left_normal  );
    analogWrite(L_CATEPILLAR_REV, pwm_left_reverse );
    analogWrite(R_CATEPILLAR    , pwm_right_normal );
    analogWrite(R_CATEPILLAR_REV, pwm_right_reverse);

    return true;
}

bool contrl_robot_arm(opr op) {
    // control robot arm!
    signal sig;
    int pwm_normal, pwm_reverse;

    if (op == ARM_STOP) {
        pwm_normal  = 255;
        pwm_reverse = 255;
//        analogWrite(ROBOT_ARM_UP  , 255);
//        analogWrite(ROBOT_ARM_DOWN, 255);
    } else {
        get_cmd(op, &sig);

        pwm_normal  = PWM_ARM_DEFAULT     * sig.rn;
        pwm_reverse = PWM_ARM_REV_DEFAULT * sig.rr;
    }

    // log
    DEBUG_FUNCNAME("contrl_robot_arm");
    DEBUG_PARAMLEFT(pwm_normal,  pwm_reverse);

    //get_cmd(op, &sig);

    // TODO: analogwrite
    analogWrite(ROBOT_ARM_UP  , pwm_normal);
    analogWrite(ROBOT_ARM_DOWN, pwm_reverse);
    return true;
}

bool contrl_robot_hand(opr op) {
    // control robot hand
    signal sig;
    int pwm_normal, pwm_reverse;

    if (op == HAND_STOP) {
        pwm_normal  = 255;
        pwm_reverse = 255;
        //analogWrite(ROBOT_HAND_OPEN,  255);
        //analogWrite(ROBOT_HAND_CLOSE, 255);
        //return true;
    } else {
        get_cmd(op, &sig);

        pwm_normal  = PWM_HAND_DEFAULT     * sig.rn;
        pwm_reverse = PWM_HAND_REV_DEFAULT * sig.rr;
    }

    // log
    DEBUG_FUNCNAME("contrl_robot_hand");
    DEBUG_PARAM(pwm_normal,  pwm_reverse);

//    get_cmd(op, &sig);

    analogWrite(ROBOT_HAND_OPEN,  pwm_normal);
    analogWrite(ROBOT_HAND_CLOSE, pwm_reverse);
    return true;
}

bool contrl_heater(bool is_on) {
    // control heater
    DEBUG_FUNCNAME("contrl_heater");

    if (is_on) {
        Serial.println("    HEATER          : ON");
        digitalWrite(HEATER, HIGH);
//        digitalWrite(HEATER1, HIGH);
//        digitalWrite(HEATER2, HIGH);
    } else {
        Serial.println("    HEATER          : OFF");
        digitalWrite(HEATER, LOW);
//        digitalWrite(HEATER1, LOW);
//        digitalWrite(HEATER2, LOW);
    }

    return true;
}

// emergency stop
void emergency_stop() {
    contrl_heater(false);
    contrl_robot_hand(HAND_REST);
    contrl_robot_arm(ARM_REST);
    contrl_catepillar(CTPL_REST);
    return true;
}

// function

void get_cmd(opr op, signal* sig) {
    char ln, lr, rn, rr;

    ln = (op & OPR_L_NORMAL)  == OPR_L_NORMAL;
    lr = (op & OPR_L_REVERSE) == OPR_L_REVERSE;
    rn = (op & OPR_R_NORMAL)  == OPR_R_NORMAL;
    rr = (op & OPR_R_REVERSE) == OPR_R_REVERSE;

    sig->ln = (int)ln;
    sig->lr = (int)lr;
    sig->rn = (int)rn;
    sig->rr = (int)rr;

//    DEBUG_FLAG(sig);
    return;
}

// logging
void DEBUG_FUNCNAME(char* name) {
    Serial.println(name);
    return;
}

void DEBUG_FLAG(signal* sig) {
    Serial.println("---- FLAG ------------");
    Serial.print("left normal   : ");
    Serial.println(sig->ln);
    Serial.print("left reverse  : ");
    Serial.println(sig->lr);
    Serial.print("right normal  : ");
    Serial.println(sig->rn);
    Serial.print("right reverse : ");
    Serial.println(sig->rr);
    return;
}

void DEBUG_PARAM(int pwm_normal, int pwm_reverse) {
    Serial.print("    NORMAL        : ");
    Serial.println(pwm_normal);
    Serial.print("    REVERSE       : ");
    Serial.println(pwm_reverse);
    return;
}

void DEBUG_PARAMLEFT(int pwm_normal, int pwm_reverse) {
    Serial.print("    LEFT  NORMAL  : ");
    Serial.println(pwm_normal);
    Serial.print("    LEFT  REVERSE : ");
    Serial.println(pwm_reverse);
    return;
}

void DEBUG_PARAMRIGHT(int pwm_normal, int pwm_reverse) {
    Serial.print("    RIGHT NORMAL  : ");
    Serial.println(pwm_normal);
    Serial.print("    RIGHT REVERSE : ");
    Serial.println(pwm_reverse);
    return;
}

