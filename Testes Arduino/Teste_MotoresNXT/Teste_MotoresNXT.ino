#define M1 4
#define M2 5
#define Vel 9
void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(Vel, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  frente_seg(45, 300);
  delay(10000);

}
void frente_seg(int vel, int seg) {
  digitalWrite(M2, LOW);
  digitalWrite(M1, HIGH);
  analogWrite(Vel,vel);
  delay(seg);
  parar();
}
void tras(int vel) {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(Vel,vel);
}
void parar() {
  digitalWrite(M2, LOW);    // Aciona o Motor do Sol (Aparecer)
  digitalWrite(M1, LOW);    // Aciona o Motor do Sol (Aparecer)

}
void travar() {
  digitalWrite(M2, HIGH);    // Aciona o Motor do Sol (Aparecer)
  digitalWrite(M1, HIGH);    // Aciona o Motor do Sol (Aparecer)

}
