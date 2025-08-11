#include <HardwareSerial.h>

// Configura os pinos para o módulo E220
#define E220_RX 16    // RX do ESP32 (recebe do TX do E220)
#define E220_TX 17    // TX do ESP32 (envia para RX do E220)
#define PINO_GND 19
#define PINO_GND2 18

HardwareSerial e220Serial(2); // Usando UART2 do ESP32

void setup() {
  Serial.begin(9600);       
  e220Serial.begin(9600, SERIAL_8N1, E220_RX, E220_TX); // Configura UART2 nos pinos definidos
  
  pinMode(PINO_GND, OUTPUT);
  digitalWrite(PINO_GND, LOW); 
  pinMode(PINO_GND2, OUTPUT);
  digitalWrite(PINO_GND2, LOW); 

  Serial.println("Iniciando E220...");
}

void loop() {
  if (e220Serial.available() > 0) {
    uint8_t data[64]; 
    int len = 0;

    while (e220Serial.available() > 0) {
      data[len++] = e220Serial.read();
      delay(10); 
    }

    if (len > 0 && data[0] == 'C' && data[1] == 'A' && data[2] == 'P' && data[3] == 'I') {
      //Serial.print("Dados recebidos: ");
      for (int i = 6; i < len - 1; i++) { 
        Serial.print((char)data[i]);
      }
      uint8_t rssi = data[len - 1];
      int rssi_dbm = -(256 - rssi);
      String rssi_virgula = ", " + String(rssi_dbm);
      Serial.print(rssi_virgula);
      Serial.println();

      //uint8_t rssi = data[len - 1];
      //Serial.print("RSSI (bruto): ");
      //Serial.println(rssi);

      //int rssi_dbm = -(256 - rssi);
      //Serial.print("RSSI (em dBm): ");
      //Serial.println(rssi_dbm);
    }
    else {
      Serial.print("Dados do capibaja não recebidos!!\n");
    }
  }
}
