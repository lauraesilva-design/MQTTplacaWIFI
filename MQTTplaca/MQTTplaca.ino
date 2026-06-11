#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char* SSID = "SALA_DE_AULA";
const char* PASSWORD = "convidadoforja123";

// MQTT
const char* BROKER = "broker.hivemq.com";
const int PORT = 1883;
const char* TOPIC = "forja/desenvolvimento/tarde";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Conectando WiFi");
  WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado na rede ");
  Serial.println(WiFi.localIP());

  client.setServer(BROKER, PORT);
  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()) {
    while(!client.connected()) {
      Serial.println("Conectando MQTT...");
      String clientId = "ESP32-" + String(random(0xffff), HEX);
      if(client.connect(clientId.c_str())) {
        Serial.println("Conectado ao MQTT");
      } else {
        Serial.print("Conexão falhou: ");
        Serial.println(client.state());
        delay(200);
      }
    }
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Mensagem recebida:");
  String leitura = "";
  for(int i = 0; i < length; i++) {
    leitura += (char)payload[i];
  }
  Serial.println(leitura);

  // Comece seu código aqui

  if(leitura == "Ligar"){
    digitalWrite(LED_BUILTIN, HIGH);
    }
    
  if(leitura == "Desligar"){
    digitalWrite(LED_BUILTIN, LOW);
  }
}
