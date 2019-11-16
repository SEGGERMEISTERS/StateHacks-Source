#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

const signed int VoltageInput = A0;
float vOut = NULL;
float vIn = NULL;
float R1 = 30000;
float R2 = 7500;
signed int value = NULL;

///////////////////////////////

const signed int Gas = A1;
float gasValue = NULL;

//////////////////////////

#define DHTPIN 11
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

/////////////////////////////////////

const signed int VibPin = 9;

////////////////////////////

const signed int WaterPin = A2;
signed int WaterValue = NULL;

////////////////////////
void setup() {
  pinMode(VoltageInput, INPUT);
  pinMode(Gas,INPUT);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  pinMode(VibPin, INPUT);
  pinMode(WaterPin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  value = analogRead(VoltageInput);
   vOut = (value * 5.0) / 1024.0; 
   vIn = vOut / (R2/(R1+R2)); 
//Serial.print("INPUT V= ");
//Serial.println(vIn);

////////////////////////////
gasValue = analogRead(Gas);
//Serial.print("gas value = ");
//Serial.println(gasValue);

//////////////////////////
sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    //Serial.print(F("Temperature: "));
    //Serial.print(event.temperature);
    //Serial.println(F("°C"));
  }
  
  ///////////////////////////////

  signed int vibMeasure = TP_init();
  //Serial.print("Viberation = ");
  //Serial.println(vibMeasure);
  
  /////////////////////////////////
  
  WaterValue = analogRead(WaterPin);
  //Serial.print("Water = ");
  //Serial.println(WaterValue);
  Serial.print(WaterValue);
  Serial.print(",");
  Serial.print(vibMeasure);
  Serial.print(",");
  Serial.print(event.temperature);
  Serial.print(",");
  Serial.print(gasValue);
  Serial.print(",");
  Serial.print(vIn);
  Serial.print("\n");
    delay(1000);

}

long TP_init(){
  delay(10);
  long measurement=pulseIn (VibPin, HIGH);  
  return measurement;
}
