#include <Ethernet2.h>

const int RECV_CMD_FIELD_NUM_MAX = 10;
String recvCmdFieldList[RECV_CMD_FIELD_NUM_MAX];

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0xE8, 0x7F
};
IPAddress ip(192, 168, 5, 10);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 5, 10);
EthernetServer socketServer(55555);
String recvMsg = "";

void setup()
{
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);
  // start listening for clients
  socketServer.begin();
  // Open serial communications for debug
  Serial.begin(9600);
}

void loop()
{
  // Return of EthernetClient.available(): 
  // Client object. If the client has no readable data,
  // this object evaluates to false in the if statement.
  EthernetClient client = socketServer.available();

  if (client)
  {
    // Receive message
    char recvByte = client.read();
    if ((int)recvByte > 0)
    {
      recvMsg = recvMsg + String(recvByte);
      if (recvByte == '\r')
      {
        Serial.println("Received message: " + recvMsg);

        // Parse message
        recvMsg.trim();
        int fieldNum = split(recvMsg, ' ', recvCmdFieldList, RECV_CMD_FIELD_NUM_MAX);
        recvMsg = "";
        if (fieldNum < 2) return;
        for(int i = 0; i < RECV_CMD_FIELD_NUM_MAX; i++)
        {
          if (recvCmdFieldList[i] != "") Serial.println("Recv: " + recvCmdFieldList[i]);
        }

        // Execute command
        for (int i = 0; i < RECV_CMD_NUM; i++)
        {
          if (recvCmdList[i].cmdName == recvCmdFieldList[1])
            int res = (int)(recvCmdList[i].cmdFunc)(recvCmdFieldList[2]);
        }
      }
    }
    else
    {
      Serial.println("No message");
      recvMsg = "";
    }
  }
}