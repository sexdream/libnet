#ifndef __PROTOCALPACKINGTOOL_H__
#define __PROTOCALPACKINGTOOL_H__
#include "ProtocolPackingTool.h"
#include <stdint.h>

typedef struct _RecvMsg_S
{
  uint16_t msgid;      /* message ID */
  uint16_t msgattri;   /* message attr */
  uint16_t sequenceno; /* sequence NO. */
  uint16_t packagecnt; /* package cnt */
  uint16_t packageno;  /* package NO. */
  uint16_t length;    /* data length */
  uint8_t data[0];     /* payload */
} RecvMsg_S;

typedef struct _SendMsg_S
{
  uint16_t msgid;        /* message ID */
  uint16_t sequenceno;   /* sequence NO. */
  uint16_t packagecnt;   /* package cnt */
  uint16_t packageno;    /* package NO. */
  uint32_t time;         /* realtime */
  uint8_t flag;          /* data flag */
  uint16_t length;       /* data length */
  const uint8_t data[0]; /* payload */
} SendMsg_S;

class CProtocolPackingTool
{
public:
  CProtocolPackingTool();
  CProtocolPackingTool(char *phoneBCD);
  ~CProtocolPackingTool();

public:
  int32_t PackSendData(SendMsg_S *header, uint32_t out_buflen, char *outdata);
  int32_t ParseReceiveData(const char *data, int datalen, RecvMsg_S **msg);

private:
  char CheckData(const char *data, int len);

  int32_t StringNumberToBCD(const char *pszString, int32_t len, char *pszBCD);
  void StrToBCD(const char *str, char *bcd, unsigned int bcdlen);

  int32_t ParseMsgHead(const char *data, RecvMsg_S *recvmsg);
  int FindOnePack(const char *data, int len, const char **packstartaddr);
};

#endif
