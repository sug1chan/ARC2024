//#include "commander.h"
#include "operate.h"
/********************************************/
/*		DEFINE_ARRAY&STRUCT_START			        */
/********************************************/
static int32_t pwm_right_normal, pwm_right_reverse, pwm_left_normal, pwm_left_reverse;
static int32_t is_slow_mode = 0;
static int32_t old_opt = 0;

typedef struct
{
	int32_t lrMove;													/*	キャタピラのパワー(固定値)	*/
	int32_t pwmCatMove;												/*	キャタピラのパワー(変数)	*/
}lrcat;


static lrcat lrnorev[LR_NUM]=									/*	ビット位置の配列			*/
{
	{RIGHT_NORMAL	,	pwm_right_normal	},
	{RIGHT_REVERSE,	pwm_right_reverse	},
	{LEFT_NORMAL	,	pwm_left_normal		},
	{LEFT_REVERSE	,	pwm_left_reverse	}
};

/********************************************/
/*		DEFINE_ARRAY&STRUCT_END				        */
/********************************************/


/********************************************/
/*		DEFINE_FUNCTION_PROTOTYPE_START		    */
/********************************************/
void get_cmd(opr op, signal* sig);

void DEBUG_FUNCNAME(char* name);
void DEBUG_FLAG(signal* sig);
void DEBUG_PARAM(int32_t pwm_normal, int32_t pwm_reverse);
void DEBUG_PARAMRIGHT(int32_t pwm_normal, int32_t pwm_reverse);
void DEBUG_PARAMLEFT(int32_t pwm_normal, int32_t pwm_reverse);
void DEBUG_HEATER(bool is_on);
/********************************************/
/*		DEFINE_FUNCTION_PROTOTYPE_END		      */
/********************************************/


/********************************************/
/*		DEFINE_FUNCTION_START				          */
/********************************************/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		各ピン初期化処理用関数				         _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
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
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		キャタピラ動作用関数				           _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
int32_t cmd_move_catepillar(int32_t opt) {
	for(int32_t i = 0;i < LR_NUM;i++){
		if((opt & lrnorev[i].lrMove) == lrnorev[i].lrMove){			/*ビットが立っている場合				*/
			if(is_slow_mode == CAT_MODE_SLOW){
				lrnorev[i].pwmCatMove = CAT_SLOW;					/*スロー出力を入れる					*/
			}else{
				lrnorev[i].pwmCatMove = CAT_NORMAL;					/*ノーマル出力を入れる					*/
			}
		}else{
			lrnorev[i].pwmCatMove = CAT_NONE;						/*出力なしを入れる						*/
		}
	}
	// logging
	DEBUG_FUNCNAME("contrl_catepillar");
	DEBUG_PARAMLEFT(lrnorev[2].pwmCatMove,   lrnorev[3].pwmCatMove);
	DEBUG_PARAMRIGHT(lrnorev[0].pwmCatMove, lrnorev[1].pwmCatMove);
	
	// operate DC Morter
	analogWrite(L_CATEPILLAR	, lrnorev[2].pwmCatMove);
	analogWrite(L_CATEPILLAR_REV, lrnorev[3].pwmCatMove);
	analogWrite(R_CATEPILLAR	, lrnorev[1].pwmCatMove);
	analogWrite(R_CATEPILLAR_REV, lrnorev[0].pwmCatMove);
	
  old_opt = opt;
	return 0;
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		キャタピラスローモード動作用関数	      _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
int32_t cmd_change_slowmode(int32_t opt) {
	// slow mode
	DEBUG_FUNCNAME("slow_mode");

	if(opt == CAT_MODE_SLOW){
		is_slow_mode = 1;
	}else{
		is_slow_mode = 0;
	}
	cmd_move_catepillar(old_opt);
	return 0;
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		ヒーターONOFF用関数					           _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
int32_t cmd_turn_onoff_heater(int32_t opt){
	// control heater
	DEBUG_FUNCNAME("contrl_heater");

	if (opt == HEATER_ON) {
		Serial.println("    HEATER          : ON");
		digitalWrite(HEATER, HIGH);
	} else {
		Serial.println("    HEATER          : OFF");
		digitalWrite(HEATER, LOW);
	}
	return 0;
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		アーム動作用関数					             _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
int32_t cmd_move_arm(int32_t opt) {
	// control robot arm!
	signal sig;
	int32_t pwm_normal, pwm_reverse;

	if (opt == ARM_STOP) {
		pwm_normal  = 255;
		pwm_reverse = 255;
	} else {
		get_cmd(opt, &sig);
	
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
	return 0;
}


/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		緊急停止用関数						             _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
int32_t cmd_emergency_stop(int32_t opt) {
	cmd_move_catepillar(CAT_NONE);
	cmd_change_slowmode(CAT_MODE_NORMAL);
	cmd_turn_onoff_heater(HEATER_OFF);
	cmd_move_arm(ARM_STOP);
	return 0;
}


/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		コマンド計算用関数                 	   _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
void get_cmd(int32_t op, signal* sig) {
    char ln, lr, rn, rr;

    ln = (op & OPR_L_NORMAL)  == OPR_L_NORMAL;
    lr = (op & OPR_L_REVERSE) == OPR_L_REVERSE;
    rn = (op & OPR_R_NORMAL)  == OPR_R_NORMAL;
    rr = (op & OPR_R_REVERSE) == OPR_R_REVERSE;

    sig->ln = (int32_t)ln;
    sig->lr = (int32_t)lr;
    sig->rn = (int32_t)rn;
    sig->rr = (int32_t)rr;

//    DEBUG_FLAG(sig);
    return;
}

/********************************************/
/*			DEFINE_FUNCTION_END		          		*/
/********************************************/



/********************************************/
/*		DEFINE_LOGGING_FUNCTION_START	       	*/
/********************************************/

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		機能名確認用関数					             _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
void DEBUG_FUNCNAME(char* name) {
	Serial.println(name);
	return;
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		機能名確認用関数					             _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
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

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_   前進・後進動作確認用関数                _*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
void DEBUG_PARAM(int32_t pwm_normal, int32_t pwm_reverse) {
	Serial.print("    NORMAL        : ");
	Serial.println(pwm_normal);
	Serial.print("    REVERSE       : ");
	Serial.println(pwm_reverse);
	return;
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		左車輪前進・後進動作確認用関数	      	_*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
void DEBUG_PARAMLEFT(int32_t pwm_normal, int32_t pwm_reverse) {
	Serial.print("    LEFT  NORMAL  : ");
	Serial.println(pwm_normal);
	Serial.print("    LEFT  REVERSE : ");
	Serial.println(pwm_reverse);
	return;
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
/*_		右車輪前進・後進動作確認用関数	      	_*/
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
void DEBUG_PARAMRIGHT(int32_t pwm_normal, int32_t pwm_reverse) {
	Serial.print("    RIGHT NORMAL  : ");
	Serial.println(pwm_normal);
	Serial.print("    RIGHT REVERSE : ");
	Serial.println(pwm_reverse);
	return;
}
/********************************************/
/*		DEFINE_LOGGING_FUNCTION_END			      */
/********************************************/
