# Dagny Protocol Library

A serial protocol for sending different types of packets over a serial link.

## Installation

Check out the github project into your library directory:

    cd Arduino/libraries
    git clone https://github.com/trainman419/dagny_protocol.git

## Usage

Setting up the `Protocol` object. The protocol object needs a serial port (Serial object) to use for transmitting and receiving data.

    Protocol link(Serial); // create a protocol object called 'link'

The `Protocol` object also needs a function to call whenever it receives a new packet:

    void linkCallback(Packet &p) {
      switch(p.type) {
        case 'A':
          // process packet type A
          p.readu8(); // read an unsigned 8-bit value
          p.reads32(); // read a signed 32-bit value
          p.readfloat(); // read a float
          break;
        case 'B':
          // process packet type B
          break;
        // etc
      }
    }

    void setup() {
      link.setCallback(linkCallback);
    }

In the main loop, the `Protocol` object handles reading from the `Serial` port and calls the callback whenever it reads a complete packet.

    void loop() {
      link.poll();
    }

The `Protocol` object is also used for sending `Packet`s:

    Packet data('D'); // create a packet with type D

    void loop() {
      uint8_t foo = 42;
      data.add(foo); // adds foo to our packet
      link.send(data); // sends 'data'
    }
