import array, socket, struct

class Cmd_No:
    CAT_MOVE       = 1
    CAT_SLOW_MODE  = 2
    HEATER_MODE    = 3
    ARM_MODE       = 4
    EMERGENCY_STOP = 5

# option
class CAT_MOVE_OPT():
    l_up   = 0x08
    l_down = 0x04
    l_rest = 0x00
    l_stop = 0x0C
    r_up   = 0x02
    r_down = 0x01
    r_rest = 0x00
    r_stop = 0x03

    @classmethod
    def get_opt(cls, state):
        opt = 0
        return opt

class CAT_SLOW_OPT():
    on  = 0x01
    off = 0x00

class HTR_MODE_OPT():
    on  = 0x01
    off = 0x00

class ARM_OPT():
    rest  = 0x00
    lower = 0x01
    upper = 0x02
    stop  = 0x03

class E_STOP_OPT():
    do = 0


class Cmd_Class():
    def __init__(self, name, opt):
        self.name   = name
        self.cmd_no = Cmd_No.__dict__[self.name]
#        self.opt    = opt
        self.struct = struct.Struct(">ii")

    def send_cmd(self, opt_arg):
        return self.struct.pack(self.cmd_no, opt_arg)

# Command
CAT_MOVE       = Cmd_Class("CAT_MOVE",       cat_move_opt)
CAT_SLOW_MODE  = Cmd_Class("CAT_SLOW_MODE",  cat_slow_mode_opt)
HEATER_MODE    = Cmd_Class("HEATER_MODE",    heater_mode_opt)
ARM_MODE       = Cmd_Class("ARM_MODE",       arm_mode_opt)
EMERGENCY_STOP = Cmd_Class("EMERGENCY_STOP", emergency_stop_opt)


# ------- debug function ------------------------

def debug():
    debug_list = [CAT_MOVE,
                  CAT_SLOW_MODE,
                  HEATER_MODE,
                  ARM_MODE,
                  EMERGENCY_STOP,]

    for cmd in debug_list:
        opt = cmd.opt

        print("Name:", cmd.name)
        print("No  :", cmd.cmd_no)
        print("Cmd :")

        for key in opt:
            print(f"  {key} = {cmd.opt[key]}")

if __name__ == "__main__":
    debug()

