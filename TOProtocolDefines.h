#ifndef __TOP_DEFINES_H__
#define __TOP_DEFINES_H__

// Header
#define TO_HEADER_MESSAGE_ID (0x0001)

//Messag
#define TO_GPS_ALARMFLAG (0x0001)
#define TO_GPS_STATUS (0x0002)
#define TO_GPS_LATITUDE (0x0003)
#define TO_GPS_LONGITUDE (0x0004)
#define TO_GPS_ALTITUDE (0x0005)
#define TO_GPS_SPEED (0x0006)
#define TO_GPS_ORIENTATION (0x0007)
#define TO_GPS_HAVEALARM (0x0008)

#define MAX_SEND_PAYLOAD (900)



typedef struct tag_ByteInfo
{
  uint8_t ucUploadInfo;
} __attribute__((__packed__)) ByteInfo_t;

typedef struct tag_WordInfo
{
  uint16_t usUploadInfo;
} __attribute__((__packed__)) WordInfo_t;

typedef struct tag_DWordInfo
{
  uint32_t uiUploadInfo;
} __attribute__((__packed__)) DWordInfo_t;

#endif
