/* protocol.h
 *
 * A cross-platofrm AVR and x86 serial communication library.
 *
 * Author: Austin Hendrix
 */

#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#ifdef ARDUINO
#include <Arduino.h>
#include <Stream.h>
#endif

class Packet {
   private:
      //const static uint8_t PACKET_SZ = N;

      char * const buffer;
      const uint8_t buf_sz;
      uint8_t sz;
      uint8_t idx;

      const static char esc = 0x1B;

   public:
      // construct a packet, set first byte to type
      Packet(char packet_type, unsigned char s, char * b) : 
         buffer(b), buf_sz(s), sz(1), idx(1), type(0)
      { buffer[0] = packet_type; }

      // construct a packet from a buffer
      Packet(char * in, unsigned char in_sz);

#ifdef ARDUINO
      // construct a packet with a particular size
      Packet(char packet_type, unsigned char size);
#endif

      // directly append a character, so we can use packets as a buffer
      void input(char c);

      // append various data types to a packet
      void append(uint8_t  c);
      void append(int8_t   c);
      void append(uint16_t s);
      void append(int16_t  s);
      void append(uint32_t i);
      void append(int32_t  i);
      void append(uint64_t i);
      void append(int64_t  i);
      void append(float    f);
      void append(double   d);

      //void append(volatile uint16_t & s);
      //void append(volatile int16_t  & s);

      // read various types from a packet
      unsigned char  readu8();
      signed char    reads8();
      unsigned short readu16();
      signed short   reads16();
      uint32_t       readu32();
      int32_t        reads32();
      float          readfloat();

      // get data for sending packet
      const char * outbuf() { return buffer; }
      unsigned char outsz() { return sz; }

      // utility methods
      void finish();
      void reset() { sz = 1; idx = 1; }

      char type;
};

#ifdef ARDUINO
class Protocol {
  public:
    Protocol(Stream & serial) : ser(serial), input(0, buf_sz, buffer)  {};
    void poll();
    void setCallback(void (*callback)(Packet&)) { this->callback = callback; }
    void send(Packet &packet);

  private:
    Stream &ser;
    void (*callback)(Packet&);
    // TODO: buffer size
    static const uint8_t buf_sz = 255;
    char buffer[buf_sz];
    Packet input;
};
#endif // ARDUINO

#endif
