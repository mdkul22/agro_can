#include "dht11.h"

Dht11::Dht11(PinName const &p) : _pin(p)
{
  // set creation time so we can make
  // sure we pause at least 1 second for
  // startup
  _timer.start();
  _temperature = 0;
  _humidity = 0;
}

int Dht::read()
{
  // BUFFER TO RECEIVE
  uint8_t bits[5]; // bitstream sent by DHT11 is 40 bits
  uint8_t cnt = 7;
  uint8_t idx = 0;

  //EMPTY BUFFER
  for(int i=0;i<5;i++) bits[i]=0;

  // Verify sensor is settled after boot
  while(_timer.read_ms() < 1500) {}
  _timer.stop();
  // Notify read to read by sending a low signal to DHT11
  _pin.output();
  _pin = 0;
  wait_ms(18);
  _pin = 1;
  wait_us(40);
  _pin.input();
  // ACKNOWLEDGE OR TIMEOUT
  unsigned int loopCnt = 10000;
  while(_pin == 0)
      if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
  loopCnt = 10000;
  while(_pin == 1)
      if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
  // READ OUTPUT - 40 Bits => 5 BYTES or TIMEOUT
  for (int i =0;i<40;i++)
  {
    loopCnt = 10000;
    while(_pin == 0)
        if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

    // unsigned long t = micros();
    Timer t;
    t.start();
    loopCnt = 10000;
    while(_pin == 1)
      if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

    if(t.read_us() > 40) bits[idx] |= (1 << cnt);
    if(cnt==0) // next byte?
    {
      cnt = 7;
      idx++;
    }
    else cnt--;
  }
_humidity = bits[0];
_temperature = bits[2];

uin8_t sum = bits[0] + bits[2];

if(bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;
return DHTLIB_OK;
}

float Dht11:getFahrenheit()
{
  return ((_temperature * 1.8) + 32);
}

int Dht11::getCelsius() {
  return(_temperature);
}

int Dht11::getHumidity() {
  return(_humidity);
}
