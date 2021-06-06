#include <string.h>
#include <iostream>
#include "NetStream.h"

using namespace std;

CNetStream::CNetStream(const unsigned char *baseaddr, unsigned int len)
{
  m_baseaddr = (unsigned char *)baseaddr;
  m_curaddr = m_baseaddr;
  m_modefyaddr = m_baseaddr;
  m_netstreamlen = len;
}

CNetStream::CNetStream(const char *baseaddr, unsigned int len)
{
  m_baseaddr = (unsigned char *)baseaddr;
  m_curaddr = m_baseaddr;
  m_modefyaddr = m_baseaddr;
  m_netstreamlen = len;
}

CNetStream::~CNetStream()
{
  m_baseaddr = NULL;
  m_curaddr = NULL;
  m_modefyaddr = NULL;
}

unsigned int CNetStream::GetWriteLen(void)
{
  return m_curaddr - m_baseaddr;
}

unsigned int CNetStream::GetReadLen(void)
{
  return m_curaddr - m_baseaddr;
}

unsigned int CNetStream::GetWriteLeftLen(void)
{
  return m_netstreamlen - (m_curaddr - m_baseaddr);
}

unsigned int CNetStream::GetReadLeftLen(void)
{
  return m_netstreamlen - (m_curaddr - m_baseaddr);
}

unsigned char *CNetStream::GetBaseAddr(void)
{
  return m_baseaddr;
}

void CNetStream::Reset(void)
{
  m_curaddr = m_baseaddr;
  m_modefyaddr = m_baseaddr;
}

unsigned int CNetStream::Seek(unsigned int len)
{
  if (m_baseaddr)
  {
    if (len < m_netstreamlen)
    {
      m_modefyaddr = m_baseaddr + len;
      return len;
    }
    else
    {
      m_modefyaddr = m_baseaddr;
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

bool CNetStream::ModefyNByte(const unsigned char *data, unsigned int datalen)
{
  if (m_baseaddr && data)
  {
    if (m_modefyaddr - m_baseaddr + datalen <= m_netstreamlen)
    {
      memcpy(m_modefyaddr, data, datalen);
      m_modefyaddr += datalen;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ModefyNByte(const char *data, unsigned int datalen)
{
  return ModefyNByte((const unsigned char *)data, datalen);
}

bool CNetStream::ModefyDWord(unsigned int data)
{
  if (m_baseaddr)
  {
    if (m_modefyaddr - m_baseaddr + sizeof(data) <= m_netstreamlen)
    {
      m_modefyaddr[0] = data >> 24;
      m_modefyaddr[1] = data >> 16;
      m_modefyaddr[2] = data >> 8;
      m_modefyaddr[3] = data;
      m_modefyaddr += 4;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ModefyWord(unsigned short data)
{
  if (m_baseaddr)
  {
    if (m_modefyaddr - m_baseaddr + sizeof(data) <= m_netstreamlen)
    {
      m_modefyaddr[0] = data >> 8;
      m_modefyaddr[1] = data;
      m_modefyaddr += 2;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ModefyByte(unsigned char data)
{
  if (m_baseaddr)
  {
    if (m_modefyaddr - m_baseaddr + sizeof(data) <= m_netstreamlen)
    {
      m_modefyaddr[0] = data;
      m_modefyaddr += 1;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::WriteNByte(const unsigned char *data, unsigned int len)
{
  if (m_baseaddr && data)
  {
    if (m_curaddr - m_baseaddr + len <= m_netstreamlen)
    {
      memcpy(m_curaddr, data, len);
      m_curaddr += len;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::WriteNByte(const char *data, unsigned int len)
{
  return WriteNByte((const unsigned char *)data, len);
}

bool CNetStream::WriteDWord(unsigned int data)
{
  if (m_baseaddr)
  {
    if (m_curaddr - m_baseaddr + sizeof(data) <= m_netstreamlen)
    {
      m_curaddr[0] = data >> 24;
      m_curaddr[1] = data >> 16;
      m_curaddr[2] = data >> 8;
      m_curaddr[3] = data;
      m_curaddr += sizeof(data);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::WriteWord(unsigned short data)
{
  if (m_baseaddr)
  {
    if (m_curaddr - m_baseaddr + sizeof(data) <= m_netstreamlen)
    {
      m_curaddr[0] = data >> 8;
      m_curaddr[1] = data;
      m_curaddr += sizeof(data);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::WriteByte(unsigned char data)
{
  if (m_baseaddr)
  {
    if (m_curaddr - m_baseaddr + sizeof(data) <= m_netstreamlen)
    {
      m_curaddr[0] = data;
      m_curaddr += sizeof(data);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ReadNByte(char *data, unsigned int len)
{
  return ReadNByte((unsigned char *)data, len);
}

bool CNetStream::ReadNByte(unsigned char *data, unsigned int len)
{
  if (m_baseaddr)
  {
    if (m_curaddr - m_baseaddr + len <= m_netstreamlen)
    {
      memcpy(data, m_curaddr, len);
      m_curaddr += len;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ReadDWord(unsigned int *data)
{
  if (m_baseaddr)
  {
    if (m_curaddr - m_baseaddr + sizeof(unsigned int) <= m_netstreamlen)
    {
      *data = m_curaddr[0] << 24;
      *data |= m_curaddr[1] << 16;
      *data |= m_curaddr[2] << 8;
      *data |= m_curaddr[3];
      m_curaddr += sizeof(unsigned int);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ReadDWord(int *data)
{
  return ReadDWord((unsigned int *)data);
}

bool CNetStream::ReadWord(unsigned short *data)
{
  if (m_baseaddr)
  {
    if (m_curaddr - m_baseaddr + sizeof(unsigned short) <= m_netstreamlen)
    {
      *data = m_curaddr[0] << 8;
      *data |= m_curaddr[1];
      m_curaddr += sizeof(unsigned short);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ReadWord(short *data)
{
  return ReadWord((unsigned short *)data);
}

bool CNetStream::ReadByte(unsigned char *data)
{
  if (m_baseaddr)
  {
    if (m_curaddr - m_baseaddr + sizeof(unsigned char) <= m_netstreamlen)
    {
      *data = m_curaddr[0];
      m_curaddr += sizeof(unsigned char);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool CNetStream::ReadByte(char *data)
{
  return ReadByte((unsigned char *)data);
}
