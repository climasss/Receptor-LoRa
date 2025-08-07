#include <SoftwareSerial.h>

// Configura os pinos para o módulo E220
#define E220_RX 7
#define E220_TX 8
#define PINO_GND 19

SoftwareSerial e220Serial(E220_RX, E220_TX); // RX, TX do E220

void setup() {
  Serial.begin(9600);       // Porta serial para monitoramento no PC
  e220Serial.begin(9600);   // Porta serial para o E220
  pinMode(PINO_GND, OUTPUT);
  digitalWrite(PINO_GND, LOW); // coloca o pino em 0V
  Serial.println("Iniciando E220...");
}

void loop() {
  if (e220Serial.available() > 0) {
    uint8_t data[64]; // Buffer para os dados recebidos
    int len = 0;

    // Lê todos os bytes disponíveis
    while (e220Serial.available() > 0) {
      data[len++] = e220Serial.read();
      delay(10); // Aguarda pequenos atrasos entre bytes
    }

    if (len > 0 && data[0] == 'C' && data[1] == 'A' && data[2] == 'P' && data[3] == 'I'  ) {
      // Exibe os dados recebidos
      Serial.print("Dados recebidos: ");
      for (int i = 6; i < len - 1; i++) { // Exclui o RSSI e a mensagem de codificação
        Serial.print((char)data[i]);
      }
      Serial.println();

      // Último byte é o RSSI
      uint8_t rssi = data[len - 1];
      Serial.print("RSSI (bruto): ");
      Serial.println(rssi);

      // Opcional: Mapeia o RSSI para dBm (se a fórmula estiver disponível)
      int rssi_dbm = -(256 - rssi); // Exemplo genérico, consulte o datasheet para ajustar
      Serial.print("RSSI (em dBm): ");
      Serial.println(rssi_dbm);
    }

    else{
      Serial.print("Dados do capibaja não recebidos!!\n");
    }
  }
}
