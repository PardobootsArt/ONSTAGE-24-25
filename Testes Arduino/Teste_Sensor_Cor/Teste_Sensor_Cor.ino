const int 1s0 = 8;
const int 1s1 = 9;
const int 1s2 = 12;
const int 1s3 = 11;
const int 1out = 10;

const int 2s0 = 0;
const int 2s1 = 1;
const int 2s2 = 4;
const int 2s3 = 2;
const int 2out = 3;
 
//==========================================================================
//=================> Pinos do led RGB
//=================

int pinoledverm = 7;
int pinoledverd = 6;
int pinoledazul = 5;
  
//==========================================================================
//=================> Variaveis cores
//=================

int red1 = 0;
int green1 = 0;
int blue1 = 0;

int red2 = 0;
int green2 = 0;
int blue2 = 0;
  
//==========================================================================
//=================> Início do setup
//================= ctrl + u = verifica o código

void setup()
{
  pinMode(1s0, OUTPUT);
  pinMode(1s1, OUTPUT);
  pinMode(1s2, OUTPUT);
  pinMode(1s3, OUTPUT);
  pinMode(1out, INPUT);

  pinMode(2s0, OUTPUT);
  pinMode(2s1, OUTPUT);
  pinMode(2s2, OUTPUT);
  pinMode(2s3, OUTPUT);
  pinMode(2out, INPUT);
  
  pinMode(pinoledverm, OUTPUT);
  pinMode(pinoledverd, OUTPUT);
  pinMode(pinoledazul, OUTPUT);
  Serial.begin(9600);
  
  digitalWrite(1s0, HIGH);
  digitalWrite(1s1, HIGH);
  digitalWrite(2s0, HIGH);
  digitalWrite(2s1, HIGH);
}
 

//==========================================================================
//=================> Início do loop
//================= ctrl + u = verifica o código

void loop()
{
  color();//Detecta a cor

  //Mostra valores no serial monitor
  Serial.print("Vermelho :");
  Serial.print(red1, DEC);
  Serial.print(" Verde : ");
  Serial.print(green1, DEC);
  Serial.print(" Azul : ");
  Serial.print(blue1, DEC);
  Serial.println();
 
  //Verifica se a cor vermelha foi detectada
  if (red1 < blue1 && red1 < green1 && red1 < 500)
  {
    Serial.println("Vermelho");
    digitalWrite(pinoledverm, LOW); //Acende o led vermelho
    digitalWrite(pinoledverd, HIGH);
    digitalWrite(pinoledazul, HIGH);
  }
 
  //Verifica se a cor azul foi detectada
  else if (blue1 < red1 && blue1 < green1 && blue1 < 1000)
  {
    Serial.println("Azul");
    digitalWrite(pinoledverm, HIGH);
    digitalWrite(pinoledverd, HIGH);
    digitalWrite(pinoledazul, LOW); //Acende o led azul
  }
 
  //Verifica se a cor verde foi detectada
  else if (green1 < red1 && green1 < blue1)
  {
    Serial.println("Verde");
    digitalWrite(pinoledverm, HIGH);
    digitalWrite(pinoledverd, LOW); //Acende o led verde
    digitalWrite(pinoledazul, HIGH);
  }
  Serial.println();
 delay(500);
  //Delay para apagar os leds e reiniciar o process
}
 
void color()
{
  //Rotina que le o valor das cores
  digitalWrite(1s2, LOW);
  digitalWrite(1s3, LOW);
  digitalWrite(2s2, LOW);
  digitalWrite(2s3, LOW);
  //count OUT, pRed, RED
  red1 = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(1s3, HIGH);
  red2 = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(2s3, HIGH);
  
  //count OUT, pBLUE, BLUE
  blue1 = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(1s2, HIGH);
  blue2 = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(2s2, HIGH);
  //count OUT, pGreen, GREEN
  green1 = pulseIn(out1, digitalRead(out1) == HIGH ? LOW : HIGH);
  green2 = pulseIn(out2, digitalRead(out2) == HIGH ? LOW : HIGH);
}
