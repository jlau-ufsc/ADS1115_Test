#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("A iniciar leitura do ADS1115...");

  // Inicializa o ADS1115 no endereço 0x48
  if (!ads.begin(0x48)) {
    Serial.println("Falha ao encontrar o ADS1115. Verifique as ligações!");
    while (1);
  }

  // Configura o ganho para aceitar de 0V até 4.096V (ideal para alimentação de 3.3V)
  ads.setGain(GAIN_ONE); 
  
  Serial.println("ADS1115 pronto!");
}

void loop() {
  int16_t adc0;
  float volts0;

  // Lê o canal A0
  adc0 = ads.readADC_SingleEnded(0);
  
  // Converte a leitura do ADC para Volts
  volts0 = ads.computeVolts(adc0);

  Serial.print("Bruto: "); Serial.print(adc0);
  Serial.print(" | Tensão no A0: "); Serial.print(volts0, 4); Serial.println(" V");

  delay(500);
}