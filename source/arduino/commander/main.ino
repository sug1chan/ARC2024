#include <Ethernet2.h>
#include "commander.h"
#include "parse.h"

#define MAX_BUF_LEN 8
#define SEPARATE "----------------------------------------"

const int32_t debug = 1;

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0xE8, 0x7F
};
IPAddress ip(192, 168, 5, 10);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 5, 10);
EthernetServer socketServer(55555);

uint8_t buf[MAX_BUF_LEN];
int32_t ibuf = 0;

void buf_init();
void show_data(String, int32_t, int32_t);

void setup() {
  Ethernet.begin(mac, ip, gateway, subnet);
  socketServer.begin();
  Serial.begin(9600);
  Serial.println(SEPARATE);
  Serial.println("init ARC2024!");
  Serial.println(SEPARATE);
}

void loop() {
  struct cmd_packet res;
  EthernetClient client = socketServer.available();

  if (client) {
    Serial.println(SEPARATE);
    Serial.println("connected.");
    Serial.println(SEPARATE);
    buf_init();

    while (client.connected()) {
      if(client.available()) {
        buf[ibuf++] = client.read();

        if (ibuf < 8)
          continue;

        parse(buf, ibuf, &res);
        ibuf = 0;

        if (!(0 <= res.cmd && res.cmd < CMD_MAX)) {
          Serial.print("Error: Invalid Cmd No.: ");
          Serial.print(res.cmd);
          Serial.println(" !");
        } else {
          struct cmd_func_list cmd = recv_cmd_list[res.cmd];
          cmd.cmd_func(res.opt);
          show_data(cmd.cmd_name, res.cmd, res.opt);
        }
      }
    }

    client.stop();
    Serial.println(SEPARATE);
    Serial.println("Disconnected.");
    Serial.println(SEPARATE);
  }
}

void buf_init() {
  memset(buf, 0, sizeof buf);
  ibuf = 0;
}

void to_bin(int32_t num) {
  int32_t max_bin = 4;
  for (int32_t i = max_bin - 1; i >= 0; i --) {
    Serial.print((num >> i) & 1);
  }
}

void show_data(String name, int32_t no, int32_t opt) {
    Serial.print("Recv Command: ");
    Serial.print(name);
    Serial.print(" (No. = ");
    Serial.print(no);
    Serial.println(")");
    Serial.print("opt = ");
    to_bin(opt);
    Serial.println("");
}
