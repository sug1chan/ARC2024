#include <stdbool.h>

// define pin

#define HEATER            5   // degial pin 05
#define ROBOT_ARM_UP      2   // degial pin 10
#define ROBOT_ARM_DOWN    3   // degial pin 11
#define ROBOT_HAND_OPEN  25   // degial pin 12
#define ROBOT_HAND_CLOSE 26   // degial pin 13
#define L_CATEPILLAR     15   // degial pin 08
#define L_CATEPILLAR_REV 16   // degial pin 09
#define R_CATEPILLAR     17   // degial pin 06
#define R_CATEPILLAR_REV 18   // degial pin 07

//define output catapiller
#define	RIGHT_NORMAL	(1U)			/*	右車輪前進				*/
#define	RIGHT_REVERSE	(2U)			/*	右車輪後進				*/
#define	LEFT_NORMAL		(4U)			/*	左車輪前進				*/
#define	LEFT_REVERSE	(8U)			/*	左車輪後進				*/
#define	LR_NUM			(4U)			/*	テーブルの最大値		*/

//define output catapiller speed
#define	CAT_NORMAL		(255U)			/*	キャタピラの速度_通常	*/
#define	CAT_SLOW		(100U)			/*	キャタピラの速度_スロー	*/
#define	CAT_NONE		(0U)			/*	キャタピラの速度_スロー	*/

//define output catapiller mode
#define CAT_MODE_NORMAL	(0U)			/*	キャタピラモード_スロー	*/
#define CAT_MODE_SLOW	(1U)			/*	キャタピラモード_スロー	*/

//define output heater onoff
#define	HEATER_OFF		(0U)			/*	ヒーターOFF				*/
#define	HEATER_ON		(1U)			/*	ヒーターON				*/


// define PWM

// default
#define PWM_DEFAULT 255

#define PWM_ARM_DEFAULT        126
#define PWM_ARM_REV_DEFAULT    63
#define PWM_HAND_DEFAULT       PWM_DEFAULT
#define PWM_HAND_REV_DEFAULT   PWM_DEFAULT
#define PWM_L_CATE_DEFAULT     PWM_DEFAULT
#define PWM_L_CATE_REV_DEFAULT PWM_DEFAULT
#define PWM_R_CATE_DEFAULT     PWM_DEFAULT
#define PWM_R_CATE_REV_DEFAULT PWM_DEFAULT

// define type

typedef char opr;

// COMMAND

// for CATEPILLAR

#define OPR_LR_REST   0
#define OPR_L_NORMAL  (1 << 3)
#define OPR_L_REVERSE (1 << 2)
#define OPR_R_NORMAL  (1 << 1)
#define OPR_R_REVERSE (1 << 0)

#define OPR_L_STOP    (OPR_L_NORMAL | OPR_L_REVERSE)
#define OPR_R_STOP    (OPR_R_NORMAL | OPR_R_REVERSE)

// OTHER (ROBOT ARM, ROBOT HAND)

#define OPR_REST      0
#define OPR_NORMAL    OPR_R_NORMAL
#define OPR_REVERSE   OPR_R_REVERSE
#define OPR_STOP      OPR_R_STOP

// for ROBOT HAND

#define HAND_REST     OPR_REST
#define HAND_OPEN     OPR_NORMAL
#define HAND_CLOSE    OPR_REVERSE
#define HAND_STOP     OPR_STOP

// operate ARM

#define ARM_REST      OPR_REST
#define ARM_UP        OPR_NORMAL
#define ARM_DOWN      OPR_REVERSE
#define ARM_STOP      OPR_STOP

// operate CATEPILLAR

#define CTPL_REST     OPR_LR_REST                       // Rest
#define CTPL_STOP     (OPR_L_STOP    | OPR_R_STOP)      // Stop
#define CTPL_FWRD     (OPR_L_NORMAL  | OPR_R_NORMAL)    // Forward
#define CTPL_BKWD     (OPR_L_REVERSE | OPR_R_REVERSE)   // Backward
#define CTPL_LFWD                      OPR_R_NORMAL      // Left Forward
#define CTPL_RFWD     OPR_L_NORMAL                      // Right Forward
#define CTPL_LBWD                      OPR_R_REVERSE     // Left  Backward
#define CTPL_RBWD     OPR_L_REVERSE                     // Right Backward
#define CTPL_LTRN     (OPR_L_REVERSE | OPR_R_NORMAL)    // Left  Turn
#define CTPL_RTRN     (OPR_L_NORMAL  | OPR_R_REVERSE)   // Right Turn

// setup Pin mode
void init_pinMode(void);
void pwm_normal(void);

// operate arduino
bool contrl_catepillar(opr);
bool contrl_robot_arm(opr);
bool contrl_robot_hand(opr);
bool contrl_heater(bool);

// emergency stop
void emergency_stop(void);

