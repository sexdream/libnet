#ifndef __NET_STREAM_H__
#define __NET_STREAM_H__

class CNetStream
{
public:
  CNetStream(const unsigned char *baseaddr, unsigned int len);
  CNetStream(const char *baseaddr, unsigned int len);
  ~CNetStream();
  unsigned int GetWriteLen(void);
  unsigned int GetReadLen(void);
  unsigned int GetWriteLeftLen(void);
  unsigned int GetReadLeftLen(void);
  unsigned char *GetBaseAddr(void);
  void Reset(void);
  unsigned int Seek(unsigned int len);
  bool ModefyNByte(const unsigned char *data, unsigned int datalen);
  bool ModefyNByte(const char *data, unsigned int datalen);
  bool ModefyDWord(unsigned int data);
  bool ModefyWord(unsigned short data);
  bool ModefyByte(unsigned char data);
  bool WriteNByte(const unsigned char *data, unsigned int len);
  bool WriteNByte(const char *data, unsigned int len);
  bool WriteDWord(unsigned int data);
  bool WriteWord(unsigned short data);
  bool WriteByte(unsigned char data);
  bool ReadNByte(unsigned char *data, unsigned int len);
  bool ReadNByte(char *data, unsigned int len);
  bool ReadDWord(unsigned int *data);
  bool ReadDWord(int *data);
  bool ReadWord(unsigned short *data);
  bool ReadWord(short *data);
  bool ReadByte(unsigned char *data);
  bool ReadByte(char *data);

private:
  unsigned char *m_baseaddr;
  unsigned char *m_curaddr;
  unsigned char *m_modefyaddr;
  unsigned int m_netstreamlen;
};

#endif
