#ifndef DHT11_H
#define DHT11_H
#include "mbed.h"

#define DHTLIB_OK              0
#define DHTLIB_ERROR_CHECKSUM -1
#define DHTLIB_ERROR_TIMEOUT   -2

class Dht11
{
public:
  /** Construct the sensor object
   *
   *
   * @param pin Pinname for the sensor pin.
   */
   Dht11(PinName const &p);

   /**Update the humidity and temperature from the sensor.
    *
    *
    * @returns
    * 0 on success, otherwise error
    */
    int read();

    /** Get the temp(f) from the saved object.
     *
     * @returns
     * Fahrenheit float
     */
     float getFahrenheit();

    /** Get the temp(c) from the saved object.
     *
     * @returns
     * Celsius int
     */
     int getCelsius();

    /** Get the humidity from the saved object.
     *
     * @returns
     * Humidity percentage int
     */
     int getHumidity();

private:
  ///percentage of humidity
  int _humidity;
  ///Celsius
  int _temperature;
  /// pin to read the sensor info on
  DigitalInOut _pin;
  /// times startup (must settle atleast a second)
  Timer _timer;
};

#endif
