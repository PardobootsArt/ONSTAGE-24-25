int Trig = 11;
int Echo = 13;
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
  // Envia pulso ultrassônico
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  // Calcula a duração do eco
  duracao = pulseIn(Echo, HIGH);
  dist = duracao / 57.2;  // Conversão para cm

  // Mostra no monitor serial
  Serial.print("Distancia: ");
  Serial.println(dist);

  // Controle do LED baseado na distância
  if (dist < 25) {
    while(true){
      for (int i = 0; i <= 255; i++) {
          analogWrite(Led, i);
          delay(10); }
      for (int i = 255; i >= 0; i--) {
          analogWrite(Led, i);
          delay(10); }
      delay(300);
    }
  }
  delay(200); // Pequeno atraso para estabilidade da leitura
}
