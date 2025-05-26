#define MSol_1 6
#define MSol_2 7
#define MLua_1 4
#define MLua_2 5
#define Vel_Sol 10
#define Vel_Lua 9
int Trig = 13;
int Echo = 11;
long dist;
long duracao;

void setup() {
  pinMode(MSol_1, OUTPUT);
  pinMode(MSol_2, OUTPUT);
  pinMode(MLua_1, OUTPUT);
  pinMode(MLua_2, OUTPUT);
  pinMode(Vel_Sol, OUTPUT);
  pinMode(Vel_Lua, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
  
  
  ultrassonico();
  while(dist > 30) {
    ultrassonico();
    frente(50);
  }
    parar();
}

void loop() {

}
void frente(int vel) {
  digitalWrite(MSol_2, HIGH);    // Aciona o Motor do Sol (Aparecer)
  analogWrite(Vel_Sol,vel);
  digitalWrite(MLua_2, HIGH);    // Aciona o Motor do Sol (Aparecer)
  analogWrite(Vel_Lua,vel);
}
void parar() {
    digitalWrite(MSol_2, LOW);    // Aciona o Motor do Sol (Aparecer)
    digitalWrite(MLua_2, LOW);    // Aciona o Motor do Sol (Aparecer)

}
void ultrassonico() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  duracao = pulseIn(Echo, HIGH);
  
  dist = duracao / 57.2;
  
  Serial.print("Distancia:");
  Serial.println(dist);
}
