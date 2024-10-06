from pyPS4Controller.controller import Controller
from command import *

class Button:
    up       = False
    down     = False
    left     = False
    right    = False
    triangle = False
    cross    = False
    square   = False
    circle   = False
    L1       = False
    L2       = False
    R1       = False
    R2       = False
    play     = False

class MyController(Controller):
    def __init__(self, com, **kwargs):
        Controller.__init__(self, **kwargs)
        self.button_status = Button()
        self.legacy_mode = 0
        # 0:up, 1:down, 2:left, 3:right, 
        # 4:triangle, 5:cross, 6:square, 7:circle, 
        # 8:L1, 9:L2, 10:R1, 11:R2
        self.com = com
        self.com.start()

# ----------------------------------------------------------

    def cat_cmd(self):
        arg  = (self.button_status.up       * CAT_MOVE_OPT.l_up)
        arg |= (self.button_status.down     * CAT_MOVE_OPT.l_down)
        arg |= (self.button_status.triangle * CAT_MOVE_OPT.r_up)
        arg |= (self.button_status.cross    * CAT_MOVE_OPT.r_down)

        msg = CAT_MOVE.pack(arg)
        self.com.sendMsg(msg)

    def heater_cmd(self):
        if self.button_status.circle:
            msg = HEATER_MODE.pack(HTR_MODE_OPT.on)
        else:
            msg = HEATER_MODE.pack(HTR_MODE_OPT.off)

        self.com.sendMsg(msg)

    def arm_cmd(self):
        arg  = (self.button_status.L1 * ARM_OPT.upper)
        arg |= (self.button_status.L2 * ARM_OPT.lower)

        msg = ARM_MODE.pack(arg)
        self.com.sendMsg(msg)

    def slow_cmd(self):
        if self.button_status.R1:
            msg = CAT_SLOW_MODE.pack(CAT_SLOW_OPT.on)
        else:
            msg = CAT_SLOW_MODE.pack(CAT_SLOW_OPT.off)

        self.com.sendMsg(msg)

    def emer_cmd(self):
        msg = EMERFENCY_STOP.pack(E_STOP_OPT.do)
        self.com.sendMsg(msg)

# ----------------------------------------------------------
# legacy mode

    def legacy_cat_cmd(self, arg):
        msg = CAT_MOVE.pack(arg)
        self.com.sendMsg(msg)

    def legacy_heater_mode(self, arg):
        msg = HEATER_MODE.pack(arg)
        self.com.sendMsg(msg)

    def legacy_arm_cmd(self, arg):
        msg = ARM_MODE.pack(arg)
        self.com.sendMsg(msg)

    def legacy_slow_mode(self, arg):
        msg = CAT_SLOW_MODE.pack(arg)
        self.com.sendMsg(msg)

# ----------------------------------------------------------

    def on_up_arrow_press(self):
        self.button_status.up = True

        if self.legacy_mode:
            self.legacy_cat_cmd(CAT_MOVE_OPT.fwd)
        else:
            self.cat_cmd()

    def on_down_arrow_press(self):
        self.button_status.down = True

        if self.legacy_mode:
            self.legacy_cat_cmd(CAT_MOVE_OPT.bwd)
        else:
            self.cat_cmd()

    def on_up_down_arrow_release(self):
        self.button_status.up   = False
        self.button_status.down = False

        if self.legacy_mode:
            self.legacy_cat_cmd(CAT_MOVE_OPT.rest)
        else:
            self.cat_cmd()

    def on_left_arrow_press(self):
        self.button_status.left = True

        if self.legacy_mode:
            self.legacy_cat_cmd(CAT_MOVE_OPT.ltrn)

    def on_right_arrow_press(self):
        self.button_status.right = True

        if self.legacy_mode:
            self.legacy_cat_cmd(CAT_MOVE_OPT.rtrn)

    def on_left_right_arrow_release(self):
        self.button_status.left  = False
        self.button_status.right = False

        if self.legacy_mode:
            self.legacy_cat_cmd(CAT_MOVE_OPT.rest)

    def on_triangle_press(self):
        self.button_status.triangle = True
        self.cat_cmd()

    def on_triangle_release(self):
        self.button_status.triangle = False
        self.cat_cmd()

    def on_x_press(self):
        self.button_status.cross = True
        self.cat_cmd()

    def on_x_release(self):
        self.button_status.cross = False
        self.cat_cmd()

    def on_square_press(self):
        self.button_status.square = True
        self.heater_cmd()

    def on_square_release(self):
        self.button_status.square = False

    def on_circle_press(self):
        self.button_status.circle = True
        self.heater_cmd()

    def on_circle_release(self):
        self.button_status.circle = False
        self.heater_cmd()

    def on_L1_press(self):
        self.button_status.L1 = True
        self.arm_cmd()

    def on_L1_release(self):
        self.button_status.L1 = False
        self.arm_cmd()

    def on_L2_press(self, value):
        if self.button_status.L2 is False:
            self.button_status.L2 = True
            self.arm_cmd()

    def on_L2_release(self):
        self.button_status.L2 = False
        self.arm_cmd()

    def on_R1_press(self):
        self.button_status.R1 = True
        self.slow_cmd()

    def on_R1_release(self):
        self.button_status.R1 = False
        self.slow_cmd()

    def on_R2_press(self, value):
        if self.button_status.R2 is False:
            self.button_status.R2 = True

    def on_R2_release(self):
        self.button_status.R2 = False

    def on_playstation_button_press(self):
        self.button_status.play = True
        self.legacy_mode ^= 1

    def on_playstation_button_release(self):
        self.button_status.play = False

# ----------------------------------------------------------

    def on_L3_up(self, value):
        pass

    def on_L3_down(self, value):
        pass

    def on_L3_left(self, value):
        pass

    def on_L3_right(self, value):
        pass

    def on_L3_y_at_rest(self):
        pass

    def on_L3_x_at_rest(self):
        pass

    def on_L3_press(self):
        pass

    def on_L3_release(self):
        pass

    def on_R3_up(self, value):
        pass

    def on_R3_down(self, value):
        pass

    def on_R3_left(self, value):
        pass

    def on_R3_right(self, value):
        pass

    def on_R3_y_at_rest(self):
        pass

    def on_R3_x_at_rest(self):
        pass

    def on_R3_press(self):
        pass

    def on_R3_release(self):
        pass

