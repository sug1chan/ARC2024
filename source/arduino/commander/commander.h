typedef int32_t(*cmd_func)(int32_t);
struct cmd_func_list {
    String cmd_name;
    cmd_func cmd_func;
};


#define CMD_NONE        0
#define CAT_MOVE        1
#define CAT_SLOW_MODE   2
#define HEATER_MODE     3
#define ARM_MOVE        4
#define EMERGENCY_STOP  5
#define CMD_MAX         6


// Command Function

int cmd_move_catepillar(int);
int cmd_change_slowmode(int);
int cmd_turn_onoff_heater(int);
int cmd_move_arm(int);
int cmd_emergency_stop(int);


// Command Function List

const struct cmd_func_list recv_cmd_list[CMD_MAX] = {
    {"CAT_MOVE",       cmd_move_catepillar},
    {"CAT_SLOW_MODE",  cmd_change_slowmode},
    {"HEATER_MODE",    cmd_turn_onoff_heater},
    {"ARM_MOVE",       cmd_move_arm},
    {"EMERGENCY_STOP", cmd_emergency_stop}
};

