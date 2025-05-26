int Trig = 13;
int Echo = 11;
int Led = 3;
long duracao;
long dist;

void setup() 
{
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Led, OUTPUT);
  Serial.begin(9600);
}
void loop() 
{  
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  duracao = pulseIn(Echo, HIGH);
  
  dist = duracao / 57.2;
  
  Serial.print("Distancia:");
  Serial.println(dist);
  
  if(dist > 15)digitalWrite(Led, LOW);
  
  if(dist < 15)digitalWrite(Led, HIGH);   
}
  
