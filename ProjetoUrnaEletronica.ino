//Autor:João Francisco Leão Magi

//Inclusão das bibliotecas
#include <SPI.h>
#include <SD.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

// Configuração para o teclado
const byte ROWS = 4; // Número de linhas do teclado
const byte COLS = 3; // Número de colunas do teclado
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {31, 33, 35,37}; // Pinos das linhas do teclado
byte colPins[COLS] = {39,41,43}; // Pinos das colunas do teclado
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Configuração para o display LCD
LiquidCrystal lcd(12,11 , 5, 4, 3, 2); // Pinos RS, E, D4, D5, D6, D7 do LCD

// Declaração das variáveis 
const int confirmButtonPin = 15; // Definindo o pino para o botão de confirmar
const int nullButtonPin = 17; // Definindo o pino para o botão de votar em branco
const int cancelButtonPin = 16; // Definindo o pino para o botão de cancelar
File myFile; //Variável necessária para a utilização do micro sd
int time1 = 150; // Variável para definir o tempo do buzzer que emite o som de confirmação
int time2 =200; // Variável definir o tempo do buzzer que emite o som de cancelar
int sequence; // Variável que recebe a sequencia de números digitados pelo usuário
int pinoSS = 53; //Variável necessária para a utilização do micro sd

//Função para a Tela Inicial, consiste em um conjunto de códigos referente a tela de inicio da urna eletrônica
void TelaIni(){
  lcd.clear();
  lcd.print("Urna Eletronica");
  lcd.setCursor(0, 1);
  lcd.print("Digite 3 numeros");
  }

//Função para escrever na tela qualquer mensagem que o usuario desejar
void Mensagem (String msg){
  lcd.clear();
  lcd.print("Urna Eletronica");
  lcd.setCursor(0, 1);
  lcd.print(msg);
  delay(1000);
 }
//Função para a música de confirmação
void Musica(){
  delay(500);
  tone(10,528,time1);
  delay(time1);
  tone(10,349,time1);
  delay(time1);
  tone(10,349,time1);
  delay(time1);
  }
//Função para a música de cancelar
  void Musica2(){
  delay(500);
  tone(10,294,time2);
  delay(time2);
  tone(10,440,time2);
  delay(time2);
  tone(10,440,time2);
  delay(time2);
  }


void setup() {

  lcd.begin(16, 2); //Definindo o tamanho do display LCD
  Serial.begin(9600); // Define BaundRate
  //Chamando a função da tela inicial
  TelaIni();

  //Declaração da entrada ou saída dos pinos
  pinMode(10,OUTPUT);
  pinMode(confirmButtonPin, INPUT_PULLUP);
  pinMode(nullButtonPin, INPUT_PULLUP);
  pinMode(cancelButtonPin, INPUT_PULLUP);
  pinMode(pinoSS, OUTPUT);

  Serial.begin(9600);
    Serial.println("Arduino e Cia - Teste de Modulo cartao micro SD");
    Serial.println("Inicializando cartao SD...");
  
  if (SD.begin()) { // Inicializa o SD Card
  Serial.println("SD Card pronto para uso."); // Imprime na tela
  }
   
  else {
  Serial.println("Falha na inicialização do SD Card.");
  return;
  }
   
  myFile = SD.open("votacaoteste", FILE_WRITE); // Cria / Abre arquivo .txt
  
  }
void loop() {
  
  static String sequence = "";
  static bool confirmed = false;

  char key = keypad.getKey();
  if (key) {
    if (sequence.length()<3){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Urna Eletronica");
      lcd.setCursor(0, 1);
      sequence += key; //Atribui o número digitado a variável sequence
      lcd.print(sequence);
    }
  }

  if (digitalRead(confirmButtonPin) == LOW) { //Se o botão Confirmar for pressionado ir para o proximo passo
    if (sequence.length() > 0){ //Se a sequencia é maior que 0 ir para o proximo passo
      if (sequence.length()==3){ // Se a sequencia é for = a 3 ir para o proximo passo
        if(sequence == "333"||sequence == "111"||sequence == "222" ||sequence == "666" ){ //Se o número digitado pelo usuario for igual a algum número dessa lista seguir para o proximo passo 
          confirmed = true; 
          Musica(); 
          myFile = SD.open("votacaoteste.txt", FILE_WRITE); // Cria / Abre arquivo .txt
          if (myFile) { // Se o Arquivo abrir imprime:
            Serial.println(sequence); 
            myFile.println(sequence); // Escreve no Arquivo
            myFile.close(); 
            Serial.println("Terminado."); 
            Serial.println(" ");
            }
          delay(1000); 
          Mensagem("Aguardando"); 
          Mensagem("VotacaoEncerrada");
          sequence = ""; 
          TelaIni(); 
          myFile = SD.open("votacaoteste.txt"); 
          if (myFile) {
            Serial.println("Conteúdo do Arquivo:"); 
              while (myFile.available()) { 
              Serial.write(myFile.read());
              }
            myFile.close(); 
            } 
            else {
              Serial.println("Erro ao Abrir Arquivo .txt"); 
              }
         }
          else{ // Se o número não for nenhum dos citados a cima
            Mensagem("Invalido"); 
            TelaIni(); 
            Mensagem("Digite um numero"); 
            Mensagem("valido"); o
            TelaIni(); 
            Mensagem(sequence); 
            lcd.setCursor(0, 1); 
            lcd.print(sequence); 
          }
       }
        else{ //Se o número não for = a 3
          Mensagem("Incompleto"); 
          TelaIni(); 
          Mensagem(sequence); 
          lcd.setCursor(0, 1);  
          lcd.print(sequence); 
       }
     }   
  }
  if (digitalRead(nullButtonPin) == LOW) { //Se o botão nulo for pressionado ir para o proximo passo
    confirmed = true; 
    Musica(); 
    sequence = "NULO"; 
    myFile = SD.open("votacaoteste.txt", FILE_WRITE); // Cria / Abre arquivo .txt
    if (myFile) { // Se o Arquivo abrir imprime:
      Serial.println(sequence); 
      myFile.println(sequence); 
      myFile.close(); 
      Serial.println("Terminado."); 
      Serial.println(" ");
      }    
    Mensagem("Voto Nulo"); 
    Mensagem("Aguardando"); 
    sequence = "";
    TelaIni(); 
  }
  if (digitalRead(cancelButtonPin) == LOW) { //Se o botão cancelar for pressionado ir para o proximo passo
    if (sequence.length()>=1){ //Se o usuario  tiver digitado pelo menos um número ir para o proximo passo
      confirmed = true; 
      Musica2();
      sequence = "CANCELAR";
      Mensagem("Voto Cancelado"); 
      Mensagem("Aguardando"); /
      sequence = ""; 
      TelaIni(); 
    }
  }
}    
