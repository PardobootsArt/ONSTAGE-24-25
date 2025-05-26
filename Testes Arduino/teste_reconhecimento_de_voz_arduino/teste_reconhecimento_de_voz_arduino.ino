int solLED = 2;  // Porta digital para o LED do sol
int luaLED = 3; // Porta digital para o LED da lua

void setup() {
  Serial.begin(9600); // Taxa de atualização da comunicação com o algoritmo do reconhecimento de imagem
  pinMode(solLED, OUTPUT); // Define a porta digital como saída
  pinMode(luaLED, OUTPUT); // Define a porta digital como saída
}

void loop() {
  if (Serial.available() > 0) { // Garante que a comunicação serial está estabelecida
    int numFingers = Serial.read() - '0';  // Converte o caractere recebido para um número
    if (numFingers == 1) { // Condição caso o contador do reconhecimento de imagem envie "1"
      digitalWrite(luaLED, LOW);  // Apaga o LED da lua
      digitalWrite(solLED, HIGH);  // Acende o LED do sol
      
    }
    else if (numFingers == 2) { // Condição caso o contador do reconhecimento de imagem envie "2"
      digitalWrite(solLED, LOW);  // Apaga o LED do sol
      digitalWrite(luaLED, HIGH);  // Acende o LED da lua

    }
    else if (numFingers == 3){ // Condição caso o contador do reconhecimento de imagem envie algo diferente de "1" ou "2"
      digitalWrite(solLED, LOW);  // Apaga o LED do sol
      digitalWrite(luaLED, LOW);  // Apaga o LED da lua
    }
  }
}
