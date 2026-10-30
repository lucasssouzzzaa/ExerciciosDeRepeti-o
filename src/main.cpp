// #include <Arduino.h>
// #include <BluetoothSerial.h>

// Endereço Bluetooth: 
// F4:65:0B:54:A3:86

// BluetoothSerial BT;

// void setup() {
//   Serial.begin(115200);
//   Serial.setTimeout(5000); // Timeout para não soltar o codigo a todo momento 

//   if (BT.begin("arroganthiSlave")) // verifica se o bluetooth da esp32 está funcionando // inicia o Bluetooth
//   {
//     Serial.println("Bluetooth iniciado com sucesso!");
//     Serial.println("Endereço Bluetooth: ");
//     Serial.println(BT.getBtAddressString()); // Função para pegar o endereço do bluetooth e trazer como string 
//   }
//   else{
//     Serial.println("Falha ao iniciar o Bluetooth!");
//   }
// }

// void loop() {

//   if(BT.available()){  //Verifica se chegou algo ao bluetooth e mostra na serial

//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s", msgRecebida);

//   }
  
//   if (Serial.available()) //Verifica oque está escrito na minha serial
//   {
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }
// }


// -------------------------------BLUETOOTH   MASTER------------------------------------
// #include <Arduino.h>
// #include <BluetoothSerial.h>

// BluetoothSerial BT;

// uint8_t endslave[] = {0X14, 0x33, 0x5C, 0x0B, 0x2B, 0x76}; // Endereço Bluetooth do dispositivo slave

// void setup() {
//   Serial.begin(115200);
//   Serial.setTimeout(5000); // Timeout para não soltar o codigo a todo momento

//   if (BT.begin("arroganthiMaster", true)) 
//   {
//     Serial.println("Bluetooth iniciado com sucesso!");
//   }
//   else {
//     Serial.println("Falha ao iniciar o Bluetooth!");
//   }

//   if (BT.connect(endslave)) // Conecta ao dispositivo slave
//   {
//     Serial.println("Conectado ao dispositivo!");
//   }
//   else {
//     Serial.println("Falha ao conectar ao dispositivo!");
//   }

// }

// void loop() {

//   if (BT.available()) { // Verifica se chegou algo ao bluetooth e mostra na serial
//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s\n", msgRecebida.c_str());
//   }

//   if (Serial.available()) { // Verifica o que está escrito na minha serial
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }

// }

// -------------------BLUETOOTH SLAVE ex2 --------------------------

// crie um programa que atraves da conexão bluetooth, faça um led acender e apagar, conforme o botão do outro esp for pressionado.

// #include <Arduino.h>
// #include <BluetoothSerial.h>

// int ledPin = 2; // Pino do LED
// int botao = 4; // Pino do botão
// int estadoBT = 0; // Estado do botão
// int estadoLed = 0; // Estado do LED
// int estadoAnBT = 0; // Estado anterior do botão

// //  Endereço Bluetooth: 
// // F4:65:0B:54:A3:86

// BluetoothSerial BT;

// void setup() {
//   Serial.begin(115200);
//   Serial.setTimeout(5000); // Timeout para não soltar o codigo a todo momento 
//   pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída

//   if (BT.begin("arroganthiSlave")) // verifica se o bluetooth da esp32 está funcionando // inicia o Bluetooth
//   {
//     Serial.println("Bluetooth iniciado com sucesso!");
//     Serial.println("Endereço Bluetooth: ");
//     Serial.println(BT.getBtAddressString()); // Função para pegar o endereço do bluetooth e trazer como string 
//   }
//   else{
//     Serial.println("Falha ao iniciar o Bluetooth!");
//   }
// }

// void loop() {

//   if(BT.available()){  //Verifica se chegou algo ao bluetooth e mostra na serial

//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s", msgRecebida);

//     if (msgRecebida == "Led Ligado") {
//       digitalWrite (ledPin, HIGH);
//     }else if (msgRecebida == "Led Desligado") {
//       digitalWrite (ledPin, LOW);
//     }

//   }
  
//   if (Serial.available()) //Verifica oque está escrito na minha serial
//   {
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }
//   estadoBT = digitalRead(botao);

//     if(!estadoBT && estadoAnBT){
//     estadoLed = !estadoLed;
//     if(estadoLed){
//       BT.println("Led Ligado");
//       Serial.println("Botão pressionado 'Led Ligado' ");
//     }
//     else{
//       BT.println("Led Desligado");
//       Serial.println("Botão pressionado 'Led Desligado'");
//     }
//   }
//   estadoAnBT = estadoBT;

// }

// ----------------------------------------------------------------

// #include <Arduino.h>

// // Definição dos pinos conforme sua especificação
// const int PIN_AUX = 13;
// const int PIN_M1  = 12;
// const int PIN_M0  = 14;

// // Pinos nativos da Serial2 no ESP32 (Geralmente marcados como RX2 e TX2 na placa)
// const int PIN_RX2 = 16; 
// const int PIN_TX2 = 17;

// unsigned long ultimoEnvio = 0;
// const long intervalo = 3000; // Envia uma mensagem a cada 3 segundos

// // Função para esperar o módulo E32 ficar pronto (AUX em nível ALTO)
// void aguardarModuloPronto() {
//   while (digitalRead(PIN_AUX) == LOW) {
//     delay(10); // Aguarda o pino AUX subir, indicando que o buffer está livre
//   }
// }

// void setup() {
//   // Inicializa a Serial do Monitor Serial (USB)
//   Serial.begin(115200);
  
//   // Inicializa a Serial2 conectada ao E32-433T20D (9600 bps é o padrão de fábrica do Ebyte)
//   Serial2.begin(9600, SERIAL_8N1, PIN_RX2, PIN_TX2);

//   // Configuração dos pinos de controle
//   pinMode(PIN_AUX, INPUT);
//   pinMode(PIN_M0, OUTPUT);
//   pinMode(PIN_M1, OUTPUT);

//   // Define o módulo para o MODO NORMAL (M0 = 0, M1 = 0)
//   digitalWrite(PIN_M0, LOW);
//   digitalWrite(PIN_M1, LOW);

//   Serial.println("--- Teste do Módulo E32-433T20D Iniciado ---");
//   Serial.println("Aguardando o módulo estabilizar...");
//   delay(1000); 
//   aguardarModuloPronto();
//   Serial.println("Módulo pronto para operação!");
// }

// void loop() {
//   // --- PARTE 1: TRANSMISSÃO (Envia dados a cada 3 segundos) ---
//   if (millis() - ultimoEnvio >= intervalo) {
//     ultimoEnvio = millis();

//     // Garante que o módulo não está processando nada antes de enviar
//     aguardarModuloPronto();

//     String mensagem = "Teste LoRa ESP32 - Tempo ativo: " + String(millis() / 1000) + "s";
    
//     Serial.print("Enviando via rádio: ");
//     Serial.println(mensagem);

//     // Envia o dado para o módulo transmitir pelo ar
//     Serial2.println(mensagem); 
//   }

//   // --- PARTE 2: RECEPÇÃO (Fica ouvindo se chega algo do rádio) ---
//   if (Serial2.available() > 0) {
//     // Quando o pino AUX cai, significa que ele está recebendo dados e jogando para a serial
//     Serial.print("Mensagem recebida do rádio: ");
    
//     // Lê a string recebida até encontrar a quebra de linha (\n)
//     String dadoRecebido = Serial2.readStringUntil('\n');
//     Serial.println(dadoRecebido);
//   }

// }

// #include <Arduino.h>
// #include <BluetoothSerial.h>

// BluetoothSerial SerialBT;

// void setup() {
//   SerialBT.begin("ESP32_Receptor"); 
// }

// const int btn = 2; 
// unsigned long lastPressTime = 0;
// bool lastButtonState = false;

// void setup() {
//   pinMode(btn, INPUT_PULLUP);
// }

// void loop () {
//   int estadoAtual = digitalRead(btn);

//   if (estadoAtual == LOW && !lastButtonState) {
//     lastButtonState = true;
//     lastPressTime = millis();
//   }
//   if (estadoAtual == HIGH && lastButtonState) {
//     lastButtonState = false;

//     unsigned long duracao = millis() - lastPressTime;

//     if (duracao >= 3000) {
      
//       SerialBT.write('B'); 
//     } 
//     else if (duracao > 50) {
      
//       SerialBT.write('A'); 
//     }
//   }
// }


// -----------------------------------------------------------------------------------

// EPS 1 
// #include "BluetoothSerial.h"
// #include "DHT.h"

// DHT dht(4, DHT11);
// BluetoothSerial bluetooth;

// void setup() {
//   Serial.begin(115200);
//   dht.begin();
  
//   bluetooth.begin("Meu_ESP_Transmissor", true);
//   bluetooth.connect("Meu_ESP_Receptor");
// }

// void loop() {
//   float umidade = dht.readHumidity();
//   float temperatura = dht.readTemperature();

//   bluetooth.print("Temperatura: ");
//   bluetooth.print(temperatura);
//   bluetooth.print(" C | Umidade: ");
//   bluetooth.print(umidade);
//   bluetooth.println(" %");

//   delay(2000);
// }

// --------------------------------------------------------------------------------

// ESP 2
// #include "BluetoothSerial.h"

// BluetoothSerial bluetooth;

// void setup() {
//   Serial.begin(115200);
//   bluetooth.begin("Meu_ESP_Receptor");
// }

// void loop() {
//   if (bluetooth.available()) {
//     char letra = bluetooth.read();
//     Serial.print(letra);
//   }
// }

// ---------ETAPA 2------------------------------------------

// EPS 1
// #include "BluetoothSerial.h"
// #include "DHT.h"

// DHT dht(4, DHT11);
// BluetoothSerial bluetooth;

// float tempAnterior = 0;
// float umidAnterior = 0;
// unsigned long tempoAnterior = 0;

// void setup() {
//   Serial.begin(115200);
//   dht.begin();
  
//   bluetooth.begin("Meu_ESP_Transmissor", true);
//   bluetooth.connect("Meu_ESP_Receptor");
// }

// void loop() {
//   float umidade = dht.readHumidity();
//   float temperatura = dht.readTemperature();

//   // Verifica se passou 2 segundos OU se o valor mudou
//   if ((millis() - tempoAnterior >= 2000) || (temperatura != tempAnterior) || (umidade != umidAnterior)) {
    
//     tempoAnterior = millis();
//     tempAnterior = temperatura;
//     umidAnterior = umidade;

//     bluetooth.print(temperatura);
//     bluetooth.print(",");
//     bluetooth.println(umidade);
//   }

//   delay(100);
// }

// --------------------------------------------------------------------------------

// ESP 2
// #include "BluetoothSerial.h"
// #include <LiquidCrystal_I2C.h>

// float tAnterior = 0;
// float uAnterior = 0;

// BluetoothSerial BT;
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// void setup() {
//   Serial.begin(115200);
  
//   lcd.init();
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("Temp: ");
//   lcd.setCursor(0, 1);
//   lcd.print("Umid: ");


//   if (BT.begin("ESP32"))
//   {
//     Serial.println("Bluetooth iniciado com sucesso");
//     Serial.print("Endereço Bluetooth: ");
//     Serial.println(BT.getBtAddressString());
//   }
//   else{
//     Serial.println("Erro ao iniciar o bluetooth");
//   }

// }

// void loop() {
//   if (BT.available()) {
//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s", msgRecebida);

//     int virgula = msgRecebida.indexOf(',');

//       String strU = msgRecebida.substring(0, virgula);
      
//       String strT = msgRecebida.substring(virgula + 1);

   
//       float u = strU.toFloat();
//       float t = strT.toFloat();


//       if (t != tAnterior) {
//         if (t > 0.000) {
//           lcd.setCursor(6, 0);
//           lcd.print(t);
//         }
//         tAnterior = t; 
//       }

//       if (u != uAnterior) {
//         if (u > 0.000) {
//           lcd.setCursor(6, 1);
//           lcd.print(u);
//         }
//         tAnterior = u; // 
//       }
//   }

//   if(Serial.available()){
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }

// }