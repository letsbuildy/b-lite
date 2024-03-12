const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */

void setup() {
  Serial.begin(115200); /* Define baud rate for serial communication */
}

void loop() {
  int sensor_reading =  analogRead(sensor_pin);
  float moisture_percentage = map(sensor_reading,425,150,0,100); 
  Serial.print("Raw reading = ");
  Serial.println(sensor_reading);
  Serial.print("moisture level = ");
  Serial.print(moisture_percentage);
  Serial.println("%");

  delay(1000);
}