#include <SPI.h>
#include <Ethernet.h>        // Mantemos para satisfazer a dependência do JSON e do shield
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ————— NÃO IMPORTANTE PARA O SIMULADOR —————
// byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// IPAddress ip(192, 168, 0, 177);
// ————————————————————————————————————————

#include <PubSubClient.h>     // <<< 1) Incluir PubSubClient

// Endereço I2C do LCD 20×4 (0x27)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Cliente Ethernet e MQTT
EthernetClient ethClient;
PubSubClient mqtt(ethClient); // <<< 2) Instanciar PubSubClient usando EthernetClient

void setup() {
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Simulando...");

  delay(1000);
  lcd.clear();

  // **Configurar Broker MQTT público (test.mosquitto.org)**
  mqtt.setServer("test.mosquitto.org", 1883); // <<< 3) Aponta para broker público

  // Opcional: exibir no LCD que o MQTT foi configurado
  lcd.setCursor(0, 0);
  lcd.print("MQTT pronto");
  delay(1000);
  lcd.clear();

  // Chama a função que parseia um JSON de exemplo e exibe no LCD
  exibeClimaMock();
}

void loop() {
  // **1) Garantir que esteja conectado ao broker**
  if (!mqtt.connected()) {
    if (mqtt.connect("arduinoUnoMock")) {  // <<< 4) Client ID qualquer
      // conectado com sucesso
    } else {
      // falhou, tenta novamente em 5 segundos
      delay(5000);
      return;
    }
  }

  // **2) Publicar o valor mockado de temperatura**
  // Para simplificar, vamos usar 25.3 como valor fixo (poderia vir do JSON mock)
  float temp = 25.3;
  char buf[10];
  dtostrf(temp, 4, 1, buf); // converte float → string (ex: "25.3")
  mqtt.publish("home/sala/temperatura", buf); // <<< 5) topico home/sala/temperatura

  // Exibir no LCD também (opcional)
  lcd.setCursor(0, 0);
  lcd.print("Pub Temp:");
  lcd.print(buf);
  lcd.print(" C   ");

  mqtt.loop();

  delay(5000); // aguarda 5s antes da próxima publicação
}

// Aqui simulamos a resposta JSON do OpenWeatherMap.
// Este trecho continua igual ao seu mock original, mas
// não precisamos chamar exibeClimaMock() novamente no loop()
void exibeClimaMock() {
  const char* exemploJson = R"rawliteral(
  {
    "main": {
      "temp": 25.3
    },
    "weather": [
      {
        "main": "Clear",
        "description": "céu limpo"
      }
    ]
  }
  )rawliteral";

  StaticJsonDocument<256> doc;
  auto err = deserializeJson(doc, exemploJson);
  if (err) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro JSON mock");
    return;
  }

  float temp = doc["main"]["temp"];
  const char* wm    = doc["weather"][0]["main"];
  const char* wdesc = doc["weather"][0]["description"];

  lcd.clear();
  lcd.setCursor(0, 0);
  char linha1[21];
  snprintf(linha1, sizeof(linha1), "Sao Paulo: %.1fC", temp);
  lcd.print(linha1);

  lcd.setCursor(0, 1);
  if (strcmp(wm, "Rain") == 0) {
    lcd.print("Chovendo!");
  } else if (strcmp(wm, "Clear") == 0) {
    lcd.print("Céu limpo");
  } else if (strcmp(wm, "Clouds") == 0) {
    lcd.print("Nublado");
  } else {
    char linha2[21];
    strncpy(linha2, wdesc, 20);
    linha2[20] = '\0';
    lcd.print(linha2);
  }
}
