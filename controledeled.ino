#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "nomeDoWifi";
const char* password = "senhaDoWifi";

const int pinoLed = 2; // Pino do LED (O Pino 2 é o LED integrado do ESP-32) 

WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(pinoLed, OUTPUT);   // Definindo pino do led como saida
  digitalWrite(pinoLed, LOW); // Pino no LED inicia desligado

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando no WiFi...");
  }
  Serial.println("WiFi Conectado");

  server.on("/", HTTP_GET, paginaInicial);
  server.on("/on", HTTP_GET, ligaLed);
  server.on("/off", HTTP_GET, desligaLed);

  server.begin();
}

void loop() {
  server.handleClient();
}

void paginaInicial() {
  String html = "<html><body>";
  html += "<h1>ESP32 Controle de Led - Internet das Coisas</h1>";

  // Botão para ligar o LED
  html += "<button onclick=\"location.href='/on'\">Ligar LED</button>";

  // Botão para desligar o LED
  html += "<button onclick=\"location.href='/off'\">Desligar LED</button>";

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void ligaLed() {
  digitalWrite(pinoLed, HIGH);
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "LED Ligado");
}

void desligaLed() {
  digitalWrite(pinoLed, LOW);
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "LED Desligado");
}
