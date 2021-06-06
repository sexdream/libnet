#include "stdio.h"
#include "NetStream.h"
#include "stdint.h"
#include "TOProtocolDefines.h"

#ifndef __PROTOCOLBUFFER_H__
#define __PROTOCOLBUFFER_H__

#define MSG_MAX_LEN (1024)

/* MQTT message*/
typedef struct tag_MQTTMsg
{
  uint8_t ucMsgId;   /* message ID*/
  uint16_t usMsgLen; /* message length*/
  uint8_t ucSource;  /* message source,reserve */
  uint32_t uiTaskId; /* task ID sign this task,reserve */
  char msgData[MSG_MAX_LEN]; /* message data */
} MQTTMsg_t;

class ProtocolBuffer
{
public:
  ProtocolBuffer(/* args */);
  virtual ~ProtocolBuffer();

public:
  int PackStringData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag);
  int PackByteData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag);
  int PackWordData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag);
  int PackDWordData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag);

   int Pack(MQTTMsg_t *msg, char *data, int datalen);
};

#endif