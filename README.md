# GS-Hora-Da-Protecao-IA# 
-Projeto: Simulador de Clima com Arduino, Ethernet e MQTT no Wokwi

## Visão Geral

-Este projeto simula, no ambiente virtual **Wokwi**, um sistema embarcado baseado em **Arduino Uno**. Ele realiza a **publicação de dados de temperatura** via protocolo **MQTT**, exibe os dados em um **LCD I²C 20x4**, e simula o uso de um **shield Ethernet** para representar conectividade de rede.

## Funcionalidades

- Simulação de leitura de temperatura via JSON mockado (OpenWeatherMap).
- Publicação periódica da temperatura no tópico MQTT `home/sala/temperatura`.
- Exibição no LCD das condições climáticas simuladas.
- Comunicação com o broker público MQTT: `test.mosquitto.org`.

## Componentes Utilizados

- Arduino Uno (virtual – Wokwi)
- LCD 20x4 com interface I2C
- Shield Ethernet (virtual)
- Bibliotecas:
  - `LiquidCrystal_I2C`
  - `Ethernet`
  - `PubSubClient`
  - `ArduinoJson`

## Estrutura do Projeto

### sketch.ino

(Código completo do sketch fornecido na descrição)

### hardware.json (Wokwi)

(Código JSON de hardware fornecido na descrição)

## Como Testar no Wokwi

1. Acesse o site [https://wokwi.com](https://wokwi.com).
2. Crie um novo projeto → “Import Project from JSON”.
3. Cole o conteúdo de `hardware.json` no editor.
4. Cole o código `.ino` no editor do sketch.
5. Clique em “Start Simulation”.

> **Nota**: O Wokwi simula as bibliotecas e componentes, mas não realiza conexão real com a internet ou o broker MQTT. Toda a lógica é mockada, útil para testes e aprendizado.
