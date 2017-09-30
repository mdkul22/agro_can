/*
Transmitter code
CANBus Tutorial based on lots of example code
*/

#include "mbed.h"
Serial pc(USBTX, USBRX);          // tx, rx for Tera Term output

DigitalOut led1(LED1);            // LED1 displays messsage sent Status
CAN can1(p9, p10);                // CAN interface
char counter = 0;                 // Counter Variable to store number of sent messages
InterruptIn button(p5)

void ask_val()
{
  CANMessage msg;
    if (can1.write(CANMessage(1200, 1, 1))) {
       pc.printf("Ask Sensor node \n");       // display message
       if(can1.read(msg))
       {
         if(msg.id==1200)
         {
           LCD.printf(msg.data);
         }
       }
       }
    else{
      can1.reset();                           // Reset CANbus if there is a problem
    }

}

int main() {
  button.rise(&ask_val);
  printf("sending a message via CANbus... ");
  while (1) {
    // send value to CAN bus and monitor return value to check if CAN
    // message was sent successfully. If so display, increment and toggle
    if (can1.write(CANMessage(1300, &counter, 1))) { // CAN Message to check acivity of Bus
       pc.printf("CAN Network Active: %d\n", counter);
       counter++;
       led1 = !led1;
    }
    else{
      can1.reset();                                           // Reset CANbus if there is a problem
    }
    wait(2);                                                  // wait a second
  }
}
