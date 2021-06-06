#include "ProtocolBuffer.h"
#include "NetStream.h"

ProtocolBuffer::ProtocolBuffer(/* args */)
{
}

ProtocolBuffer::~ProtocolBuffer()
{
}

int ProtocolBuffer::PackStringData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag)
{
  if ((NULL == msg) || (NULL == data))
  {
    return -1;
  }

  if (msg->usMsgLen > 0)
  {
     stm(data, datalen);

    if (!raw_flag)
    {
      stm.WriteWord(msg->ucMsgId);
      stm.WriteByte(msg->usMsgLen);
    }

    stm.WriteNByte(msg->msgData, msg->usMsgLen);

    return stm.GetWriteLen();
  }
  else
  {
    return -1;
  }
}

int ProtocolBuffer::PackByteData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag)
{
  if (msg->usMsgLen == sizeof(ByteInfo_t))
  {
    ByteInfo_t *stuInfo = (ByteInfo_t *)msg->msgData;
    CNetStream stm(data, datalen);

    if (!raw_flag)
    {
      stm.WriteWord(msg->ucMsgId);
      stm.WriteByte(msg->usMsgLen);
    }
    stm.WriteByte(stuInfo->ucUploadInfo);

    return stm.GetWriteLen();
  }
  else
  {
    return -1;
  }
}

int ProtocolBuffer::PackWordData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag)
{
  if (msg->usMsgLen == sizeof(WordInfo_t))
  {
    WordInfo_t *stuInfo = (WordInfo_t *)msg->msgData;
    CNetStream stm(data, datalen);

    if (!raw_flag)
    {
      stm.WriteWord(msg->ucMsgId);
      stm.WriteByte(msg->usMsgLen);
    }
    stm.WriteWord(stuInfo->usUploadInfo);

    return stm.GetWriteLen();
  }
  else
  {
    return -1;
  }
}

int ProtocolBuffer::PackDWordData(MQTTMsg_t *msg, char *data, int datalen, bool raw_flag)
{
  if (msg->usMsgLen == sizeof(DWordInfo_t))
  {
    DWordInfo_t *stuInfo = (DWordInfo_t *)msg->msgData;
    CNetStream stm(data, datalen);

    if (!raw_flag)
    {
      stm.WriteWord(msg->ucMsgId);
      stm.WriteByte(msg->usMsgLen);
    }
    stm.WriteDWord(stuInfo->uiUploadInfo);

    return stm.GetWriteLen();
  }
  else
  {
    return -1;
  }
}

int ProtocolBuffer::Pack(MQTTMsg_t *msg, char *data, int datalen)
{
  if ((NULL == msg) || (NULL == data))
  {
    printf("msg or data is NULL\n");
    return -1;
  }

  printf("-----pack msgid=%d, datalen=%d\n", msg->ucMsgId, msg->usMsgLen);
  int res = -127;

  switch (msg->ucMsgId)
  {
  // DWORD
  case TO_GPS_ALARMFLAG:
  case TO_GPS_LATITUDE:
  case TO_GPS_LONGITUDE:
    res = PackDWordData(msg, data, datalen, 0);
    break;

  // WORD
  case TO_GPS_ALTITUDE:
  case TO_GPS_SPEED:
  case TO_GPS_ORIENTATION:
    res = PackWordData(msg, data, datalen, 0);
    break;

  // BYTE
  case TO_GPS_STATUS:
  case TO_GPS_HAVEALARM:
    res = PackByteData(msg, data, datalen, 0);
    break;

  default:
    break;
  }

  return res;
}
