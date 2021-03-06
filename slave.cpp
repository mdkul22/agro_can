/*
Receiver code
CANBus Tutorial based on lots of example code
*/

#include "mbed.h"
#include "dht11.h"
Serial pc(USBTX, USBRX);          // tx, rx for Tera Term output
DigitalOut led2(LED2);            // status LED
CAN can1(p30, p29);               // CAN interface
DHT11 sensor(p9);

int main() {
  CANMessage msg;                 // create empty CAN message
  printf("received a CANbus message...\n"); // Write to serial terminal
  while(1) {
    if(can1.read(msg)) {          // if message is available, read into msg
      if(msg.id == 1300)
      {
      printf("Message received with 1300 AC: %d\n", msg.data[0]);   // display message data
      led2 = !led2;     // toggle receive status LED
      }
      if(msg.id == 1200)
      {
          wait(0.01);
          printf("Received request for sensor!\n");
          sensor.read();
          printf("Humidity: %d", sensor.getHumidity());
          if (can1.write(CANMessage(1200, sensor.getHumidity(), 1))) { // CAN Message to check acivity of Bus
             pc.printf("CAN message sent:");
             wait(0.01);
          }
    }
  }
}
