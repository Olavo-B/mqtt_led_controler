#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SuaSSID";
const char* password = "SuaSenha";
const char* mqtt_server = "mqtt.cool";
const int mqtt_port = 1883;
const char* mqtt_user = "";  // Deixe em branco se não precisar de autenticação
const char* mqtt_password = "";  // Deixe em branco se não precisar de autenticação
const char* topic = "led/control";

const int ledPin = 13;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se à rede WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: " + WiFi.localIP().toString());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida do tópico: ");
  Serial.println(topic);

  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (message == "ligar") {
    digitalWrite(ledPin, HIGH);
  } else if (message == "desligar") {
    digitalWrite(ledPin, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando se reconectar ao MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado");
      client.subscribe(topic);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
