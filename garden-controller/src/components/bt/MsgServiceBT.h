#ifndef __MSGSERVICEBT__
#define __MSGSERVICEBT__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "components/serial/MsgService.h"

class MsgServiceBT {
   public:
    MsgServiceBT(int rxPin, int txPin);
    void init();
    bool isMsgAvailable();
    Msg* receiveMsg();
    void sendMsg(Msg msg);

   private:
    String content;
    Msg* availableMsg;
    SoftwareSerial* channel;
};

#endif
