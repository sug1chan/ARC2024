typedef int(*cmd_func)(int);
struct cmd_list {
    String cmd_name;
    cmd_func cmd_func;
}

enum Command {
    CMD_NONE = 0,
    CAT_MOVE,
    CAT_SLOW_MODE,
    HEATER_MODE,
    ARM_MOVE,
    EMERGENCY_STOP,
    CMD_MAX
}


// Command Function

int cmd_move_catepillar(int);
int cmd_change_slowmode(int);
int cmd_turn_onoff_heater(int);
int cmd_move_arm(int);
int cmd_emergency_stop(int);


// Command Function List

const struct cmd_list recv_cmd_list[CMD_MAX] = {
    [CAT_MOVE]       = {"CAT_MOVE",       cmd_move_catepillar},
    [CAT_SLOW_MODE]  = {"CAT_SLOW_MODE",  cmd_changeslow_mode},
    [HEATER_MODE]    = {"HEATER_MODE",    cmd_turn_onoff_heater},
    [ARM_MOVE]       = {"ARM_MOVE",       cmd_move_arm},
    [EMERGENCY_STOP] = {"EMERGENCY_STOP", cmd_emergency_mode},
}

