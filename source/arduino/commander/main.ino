#include <Ethernet2.h>
#include "main.h"
#include "commander.h"

#define MAX_BUF_LEN 8

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0xE8, 0x7F
};
IPAddress ip(192, 168, 5, 10);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 5, 10);
EthernetServer socketServer(55555);

uint8_t buf[MAX_BUF_LEN];
int32_t ibuf;

void setup() {
  memset(buf, 0, sizeof buf);
  ibuf = 0;

  Ethernet.begin(mac, ip, gateway, subnet);
  socketServer.begin();
  Serial.begin(9600);
}

void loop() {
  struct command_packet res;
  EthernetClient client = socketServer.available();

  if (client) {
    buf[ibuf++] = client.read();

    if (ibuf >= 8) {
      // parse buf;
      parse(buf, ibuf, &res);
      ibuf = 0;

      if (!(0 <= res.cmd && res.cmd < CMD_MAX)) {
        Serial.println("Error: Invalid Cmd No.: %d !\n", res.cmd);
        return;
      }
      struct cmd_list cmd = recv_cmd_list[res.cmd];
      Serial.println("Recv Command: %s, opt = %x\n", cmd.cmd_name, res.opt);
      cmd.cmd_func(res.opt);
    }
  }
}
