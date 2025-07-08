int solLED = 2;  // Porta digital para o LED do sol
int luaLED = 3; // Porta digital para o LED da lua
#define MSol_1 4
#define MSol_2 5
#define MLua_1 6
#define MLua_2 7
#define PinVel_Sol 9
#define PinVel_Lua 10

void setup() {
  Serial.begin(9600); // Taxa de atualização da comunicação com o algoritmo do reconhecimento de imagem
  pinMode(solLED, OUTPUT); // Define a porta digital como saída
  pinMode(luaLED, OUTPUT); // Define a porta digital como saída
  pinMode(MSol_1, OUTPUT);
  pinMode(MSol_2, OUTPUT);
  pinMode(MLua_1, OUTPUT);
  pinMode(PinVel_Sol, OUTPUT);
  pinMode(PinVel_Lua, OUTPUT);
  digitalWrite(solLED, LOW);
  digitalWrite(luaLED, LOW);
}

void loop() {
  if (Serial.available() > 0) { // Garante que a comunicação serial está estabelecida
    int reconhecimento = Serial.read() - '0';  // Converte o caractere recebido para um número
    if (reconhecimento == 1) {
      digitalWrite(solLED, HIGH);
      digitalWrite(luaLED, LOW);
      AcionarSol('D', 80, 1550);
    }
    else if (reconhecimento == 2) {
      digitalWrite(solLED, LOW);
      digitalWrite(luaLED, HIGH);
      AcionarSol('E', 50, 700);
      delay(1000);
      AcionarLua('E', 80, 1600);
    }
    else if (reconhecimento == 3) { // Condição caso o contador do reconhecimento de imagem envie "4"
      digitalWrite(solLED, LOW);
      digitalWrite(luaLED, LOW);
      AcionarLua('D', 50, 1000);
    }
    else if (reconhecimento == 0) { // Condição caso o contador do reconhecimento de imagem envie "4"
      PararMotores();
      digitalWrite(luaLED, LOW);    // Garante a Lua apagada 
      digitalWrite(solLED, LOW);   // Garante o Sol apagado
    }
    
  }
}
void AcionarSol(char dir, int vel, int seg){
  if (dir == 'E'){
    digitalWrite(MSol_1, HIGH);
    digitalWrite(MSol_2, LOW);
    analogWrite(PinVel_Sol, vel);
    delay(seg);
    digitalWrite(MSol_1, LOW);
    digitalWrite(MSol_2, LOW);
  }
  else if (dir == 'D'){
    digitalWrite(MSol_1, LOW);
    digitalWrite(MSol_2, HIGH);
    analogWrite(PinVel_Sol, vel);
    delay(seg);
    digitalWrite(MSol_1, LOW);
    digitalWrite(MSol_2, LOW);
  }
}
void AcionarLua(char dir, int vel, int seg){
  if (dir == 'D'){
    digitalWrite(MLua_1, HIGH);
    digitalWrite(MLua_2, LOW);
    analogWrite(PinVel_Lua, vel);
    delay(seg);
    digitalWrite(MLua_1, LOW);
    digitalWrite(MLua_2, LOW);
  }
  else if (dir == 'E'){
    digitalWrite(MLua_1, LOW);
    digitalWrite(MLua_2, HIGH);
    analogWrite(PinVel_Lua, vel);
    delay(seg);
    digitalWrite(MLua_1, LOW);
    digitalWrite(MLua_2, LOW);
  }
}
void PararMotores(){
  digitalWrite(MLua_1, LOW);
  digitalWrite(MLua_2, LOW);
  digitalWrite(MSol_1, LOW);
  digitalWrite(MSol_2, LOW);
}
