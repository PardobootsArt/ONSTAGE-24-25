int Trig = 11;
int Echo = 13;
long duracao;
long dist;
#define MPoco_1 4
#define MPoco_2 5
#define PinVel_Poco 9
void setup() {
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(MPoco_1, OUTPUT);
  pinMode(MPoco_2, OUTPUT);
  pinMode(PinVel_Poco, OUTPUT);
  Serial.begin(9600);
}

void loop() {
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
  if (dist < 10) {
    AcionarPoco('D', 70, 2000);
  } else {
    PararMotores();
  }

  delay(200);
}

void AcionarPoco(char dir, int vel, int seg){
  if (dir == 'E'){
    digitalWrite(MPoco_1, HIGH);
    digitalWrite(MPoco_2, LOW);
    analogWrite(PinVel_Poco, vel);
    delay(seg);
    digitalWrite(MPoco_1, LOW);
    digitalWrite(MPoco_2, LOW);
  }
  else if (dir == 'D'){
    digitalWrite(MPoco_1, LOW);
    digitalWrite(MPoco_2, HIGH);
    analogWrite(PinVel_Poco, vel);
    delay(seg);
    digitalWrite(MPoco_1, LOW);
    digitalWrite(MPoco_2, LOW);
  }
}

void PararMotores(){
  digitalWrite(MPoco_1, LOW);
  digitalWrite(MPoco_2, LOW);
}
