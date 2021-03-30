#include <PacketSerial.h>
#include "util/delay.h"

#include <SoftwareSerial.h> // only for debug

SLIPPacketSerial myPacketSerial;
SoftwareSerial mySerial(10, 11); // only for debug // RX, TX

struct data_t{
  int dane_int_1;
  int dane_int_2;
  float dane_float_1;
  float dane_float_2;
  uint8_t dane_byte_1;
  uint8_t dane_byte_2;
} data_to_send, data_incomming;


void set_random_values(void){
  // set some values
  data_to_send.dane_int_1 = random(-10000,10000);
  data_to_send.dane_int_2 = random(-10000,10000);
  data_to_send.dane_float_1 = random(0,200)*21.37;
  data_to_send.dane_float_2 = random(0,200)*21.37;
  data_to_send.dane_byte_1 = random(0,255);
  data_to_send.dane_byte_2 = random(0,255);
}

void setup() {
  myPacketSerial.begin(115200);
  // only for debug
  mySerial.begin(4800);
  mySerial.println("Starting!");
  myPacketSerial.setPacketHandler(&onPacketReceived);
}



void loop() {
  // put your main code here, to run repeatedly:
  set_random_values();
  myPacketSerial.send((uint8_t*)&data_to_send, sizeof(data_to_send));
  myPacketSerial.update();
  _delay_ms(1000);
}


void onPacketReceived(const uint8_t* buffer, size_t size){
  memcpy((void*)&data_incomming, buffer, size);
  mySerial.println("Received sliped packet!");
  mySerial.print("int1 = ");
  mySerial.println(data_incomming.dane_int_1);
  mySerial.print("int2 = ");
  mySerial.println(data_incomming.dane_int_2);
  mySerial.print("float1 = ");
  mySerial.println(data_incomming.dane_float_1);
  mySerial.print("float2 = ");
  mySerial.println(data_incomming.dane_float_2);
  mySerial.print("byte1 = ");
  mySerial.println(data_incomming.dane_byte_1);
  mySerial.print("byte2 = ");
  mySerial.println(data_incomming.dane_byte_2);
  
}




