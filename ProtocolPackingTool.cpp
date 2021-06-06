#include "ProtocolPackingTool.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "NetStream.h"

#define FRAMESLICE (2) //attr slice flag offset

CProtocolPackingTool::CProtocolPackingTool()
{
}

CProtocolPackingTool::CProtocolPackingTool(char *phoneBCD)
{
}

CProtocolPackingTool::~CProtocolPackingTool()
{
}

void CProtocolPackingTool::StrToBCD(const char *str, char *bcd, unsigned int bcdlen)
{
  int i;
  int len = strlen(str);
  char tmp = 0;
  for (i = bcdlen - 1; i >= 0; i--)
  {
    if (len > 0)
    {
      if (len / 2 > 0)
      {
        tmp = (str[len - 2] - 0x30) << 4 | (str[len - 1] - 0x30);
        len -= 2;
        bcd[i] = tmp;
      }
      else
      {
        tmp = (str[len - 1] - 0x30);
        bcd[i] = tmp;
        break;
      }
    }
    else
    {
      break;
    }
  }
}

int32_t CProtocolPackingTool::StringNumberToBCD(const char *pszString, int32_t len, char *pszBCD)
{
  if (!pszString || !pszBCD)
  {
    printf("param error while covert string to bcd\n");
    return -1;
  }

  int reallen = strlen(pszString);
  if (reallen > len)
  {
    reallen = len;
  }
  memset(pszBCD, 0, (reallen + 1) / 2);
  for (int i = 0; i < reallen; i++)
  {
    if (pszString[i] < '0' && pszString[i] > '9')
    {
      printf("Bad string code str=%s\n", pszString);
      return -1;
    }
    pszBCD[i / 2] |= ((pszString[i] - 0x30) << ((i % 2) * 4));
  }

  return 0;
}
// serach header in tcp stream
int CProtocolPackingTool::FindOnePack(const char *data, int len, const char **packstartaddr)
{
  //TODO assume header is at the front
  *packstartaddr = data;

  return 0;
}

int32_t CProtocolPackingTool::ParseMsgHead(const char *data, RecvMsg_S *recvmsg)
{
  CNetStream stm(data, sizeof(RecvMsg_S));

  //msgid
  stm.ReadWord(&recvmsg->msgid);
  // msgattri
  stm.ReadWord(&recvmsg->msgattri);
  // sequenceno
  stm.ReadWord(&recvmsg->sequenceno);

  if (recvmsg->msgattri & (1 << FRAMESLICE))
  {
    stm.ReadWord(&recvmsg->packagecnt);
    stm.ReadWord(&recvmsg->packageno);
  }
  // message length
  stm.ReadWord(&recvmsg->length);

  return stm.GetWriteLen();
}

int32_t CProtocolPackingTool::ParseReceiveData(const char *data, int datalen, RecvMsg_S **msg)
{
  const char *packstart = NULL;
  int ret = 0;

  if (datalen < (int)sizeof(RecvMsg_S))
  {
    printf("pack data length err!\n");
    return -1;
  }

  ret = FindOnePack(data, datalen, &packstart);
  if (ret < 0)
  {
    printf("there is no package!\n");
    return -1;
  }

  RecvMsg_S header;

  int headlen = ParseMsgHead(packstart, &header);

  *msg = (RecvMsg_S *)malloc(sizeof(RecvMsg_S) + header.length * sizeof(uint8_t));
  if (*msg == NULL)
  {
    printf("malloc failed\n");
    return -1;
  }

  memcpy((*msg), &header, sizeof(RecvMsg_S));
  memcpy((char *)(*msg)->data, data + headlen, (*msg)->length);

  return headlen + (*msg)->length;
}

int32_t CProtocolPackingTool::PackSendData(SendMsg_S *sender, uint32_t out_buflen, char *outdata)
{
  CNetStream stm(outdata, out_buflen);

  //message ID WORD
  stm.WriteWord(sender->msgid);

  //message sequenceno DWORD
  stm.WriteDWord(sender->sequenceno);

  //message packagecnt DWORD
  stm.WriteDWord(sender->packagecnt);

  //message packageno DWORD
  stm.WriteDWord(sender->packageno);

  //message time DWORD
  stm.WriteDWord(sender->time);

  //message data flag BYTE
  stm.WriteByte(sender->flag);

  // message length WORD
  stm.WriteWord(sender->length);

  //message body
  if (sender->length > 0)
  {
    stm.WriteNByte(sender->data, sender->length);
  }
  //CRC BYTE
  stm.WriteByte(this->CheckData(outdata, stm.GetWriteLen()));

  return stm.GetWriteLen();
}

char CProtocolPackingTool::CheckData(const char *data, int len)
{
  char value = data[0];
  for (int i = 1; i < len; i++)
  {
    value ^= data[i];
  }
  return value;
}