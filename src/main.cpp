#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("A iniciar leitura do ADS1115 com Filtro de Média Móvel...");

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
  long soma = 0;
  int amostras = 10; // Número de leituras para tirar a média

  // Recolhe várias amostras rápidas para suavizar o ruído
  for (int i = 0; i < amostras; i++) {
    soma += ads.readADC_SingleEnded(0);
    delay(5); // Pequena pausa entre as amostras
  }
  
  // Calcula a média aritmética
  int16_t adc0 = soma / amostras;
  
  // Converte a leitura média do ADC para Volts
  float volts0 = ads.computeVolts(adc0);

  Serial.print("Média Bruta: "); Serial.print(adc0);
  Serial.print(" | Tensão Média: "); Serial.print(volts0, 4); Serial.println(" V");

  delay(500);
}