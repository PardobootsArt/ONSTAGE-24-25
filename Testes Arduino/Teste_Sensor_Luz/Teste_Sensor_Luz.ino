#define sensorluz A0
int valorsensor;
void setup() {
pinMode(sensorluz, INPUT);
Serial.begin(9600);
}

void loop() {
valorsensor = analogRead(sensorluz);
Serial.println(valorsensor);
delay(500);
}
