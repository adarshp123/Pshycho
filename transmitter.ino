//Include Libraries
#include "DHT.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN
#define DHTPIN 5
#define DHTTYPE DHT11  
//address through which two modules communicate.
const byte address[6] = "00001";
DHT dht(DHTPIN, DHTTYPE);
struct MyData {
  byte h;
  byte t;
};
MyData data;
void setup()
{
  dht.begin();
  radio.begin(); 
  //set the address
  radio.openWritingPipe(address);  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
   delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  /////////////////////////////////////
data.h = dht.readHumidity();
data.t = dht.readTemperature();
radio.write(&data, sizeof(MyData));
  
  delay(1000);
}
