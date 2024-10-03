from pyPS4Controller.controller import Controller

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

class MyController(Controller):
    def __init__(self, com, **kwargs):
        Controller.__init__(self, **kwargs)
#        self.button_status = [False] * 12
        self.button_status = Button()
        # 0:up, 1:down, 2:left, 3:right, 
        # 4:triangle, 5:cross, 6:square, 7:circle, 
        # 8:L1, 9:L2, 10:R1, 11:R2
        self.com = com
        self.com.start()

    def on_up_arrow_press(self):
#        self.button_status[0] = True
        self.button_status.up = True
        self.com.sendcmd('V_MOVE_FORWARD', []) 

    def on_down_arrow_press(self):
#        self.button_status[1] = True
        self.button_status.down = True
        self.com.sendcmd('V_MOVE_BACKWARD', []) 

    def on_up_down_arrow_release(self):
#        self.button_status[0] = False
#        self.button_status[1] = False
        self.button_status.up   = False
        self.button_status.down = False
        self.com.sendcmd('V_STOP', []) 

    def on_left_arrow_press(self):
#        self.button_status[2] = True
        self.button_status.left = True
        self.com.sendcmd('V_ROT_LEFT', []) 

    def on_right_arrow_press(self):
#        self.button_status[3] = True
        self.button_status.right = True
        self.com.sendcmd('V_ROT_RIGHT', []) 

    def on_left_right_arrow_release(self):
#        self.button_status[2] = False
#        self.button_status[3] = False
        self.button_status.left  = False
        self.button_status.right = False
        self.com.sendcmd('V_STOP', [])

    def on_triangle_press(self):
#        self.button_status[4] = True
        self.button_status.triangle = True
#        if self.button_status[8] and self.button_status[10]:
        if self.button_status.L1 and self.button_status.R1:
            self.com.sendcmd('ALL_STOP', [])
        else:
            self.com.sendcmd('LEDLIGHT', ['ON'])

    def on_triangle_release(self):
#        self.button_status[4] = False
        self.button_status.triangle = False
        self.com.sendcmd('LEDLIGHT', ['OFF'])

    def on_x_press(self):
#        self.button_status[5] = True
        self.button_status.cross = True
#        if self.button_status[6]:
        if self.button_status.square:
            self.com.sendcmd('H_STOP', [])
        else:
            self.com.sendcmd('H_MOVE_RLS', []) 

    def on_x_release(self):
#        self.button_status[5] = False
        self.button_status.cross = False
        self.com.sendcmd('H_STOP', [])

    def on_square_press(self):
#        self.button_status[6] = True
        self.button_status.square = True
#        if self.button_status[5]:
        if self.button_status.cross:
            self.com.sendcmd('H_STOP', [])
        else:
            self.com.sendcmd('H_MOVE_HLD', []) 

    def on_square_release(self):
#        self.button_status[6] = False
        self.button_status.square = False
        self.com.sendcmd('H_STOP', [])

    def on_circle_press(self):
#        self.button_status[7] = True
        self.button_status.circle = True
        self.com.sendcmd('HEATER_ONOFF', ['ON']) 

    def on_circle_release(self):
#        self.button_status[7] = False
        self.button_status.circle = False
        self.com.sendcmd('HEATER_ONOFF', ['OFF'])

    def on_L1_press(self):
#        self.button_status[8] = True
        self.button_status.L1 = True
        if self.button_status.R1:
#        if self.button_status[10]:
            self.com.sendcmd('C_STOP', [])
        else:
            self.com.sendcmd('C_MOVE_LOWER', [])

    def on_L1_release(self):
#        self.button_status[8] = False
        self.button_status.L1 = False
        self.com.sendcmd('C_STOP', [])

    def on_L2_press(self, value):
        print("on_L2_press: {}".format(value))
#        self.button_status[9] = True
        self.button_status.L2 = True

    def on_L2_release(self):
        print("on_L2_release")
#        self.button_status[9] = False
        self.button_status.L2 = False

    def on_R1_press(self):
#        self.button_status[10] = True
        self.button_status.R1 = True
#        if self.button_status[8]:
        if self.button_status.L1:
            self.com.sendcmd('C_STOP', [])
        else:
            self.com.sendcmd('C_MOVE_UPPER', [])        

    def on_R1_release(self):
#        self.button_status[10] = False
        self.button_status.R1 = False
        self.com.sendcmd('C_STOP', [])

    def on_R2_press(self, value):
        print("on_R2_press: {}".format(value))
#        self.button_status[11] = True
        self.button_status.R2 = True
        #self.com.sendcmd('C_MOVE_LOWER', [])

    def on_R2_release(self):
        print("on_R2_release")
#        self.button_status[11] = False
        self.button_status.R2 = False
        #self.com.sendcmd('C_STOP', [])

