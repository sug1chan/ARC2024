import array, socket, struct

class Cmd_No:
    CAT_MOVE       = 1
    CAT_SLOW_MODE  = 2
    HEATER_MODE    = 3
    ARM_MODE       = 4
    EMERGENCY_STOP = 5

# option
cat_move_opt       = {"left_up"   : 0,
                      "left_down" : 1,
                      "left_stop" : 1,
                      "right_up"  : 2,
                      "right_down": 3,
                      "right_stop": 3,}
cat_slow_mode_opt  = {"on" : 0x01,
                      "off": 0x00,}
heater_mode_opt    = {"on" : 0x01,
                      "off": 0x00,}
arm_mode_opt       = {"upper": 0x01,
                      "lower": 0x02,
                      "stop" : 0x00,}
emergency_stop_opt = {"do": 0x00,}

class Packet():
    def __init__(self, cmd_name, cmd_no, opt):
        self.cmd_name = cmd_name
        self.cmd_no   = cmd_no
        self.opt      = opt

    def get_data(self):
        return array.array('B', [])

class Cmd_Class():
    def __init__(self, name, opt):
        self.name   = name
        self.cmd_no = Cmd_No.__dict__[self.name]
        self.opt    = opt
        self.struct = struct.Struct(">ii")

    def send_cmd(self, opt_arg):
        return self.struct.pack(self.cmd_no, opt_arg)

    def __getattr__(self, opt_arg):
        if opt_arg not in self.opt:
            raise Exception("Invalid Option: {}".format(opt_arg))

        self.send_cmd(self.opt[opt_arg])

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

