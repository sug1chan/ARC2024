import time
from ps4ControllerBridge import MyController
from socket_com import ClientSocketCom

SERVER_IP_ADDR = '192.168.5.10'
SERVER_PORT_NUM = 55555

def main():
    com = ClientSocketCom(SERVER_IP_ADDR, SERVER_PORT_NUM)
    controller = MyController(com, interface="/dev/input/js0", connecting_using_ds4drv=False)
    try:
        count = 0
        while count < 2:
            try:
                controller.listen()
            except Exception as e:
                print(str(e))
                print('Retry to execute listen().')
                count += 1
                time.sleep(1)
                continue
    finally:
        com.stop()
        print('Program was terminated.')

if __name__ == '__main__':
    main()