#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configurações de Wi-Fi
const char* ssid = "SEU_SSID"; // Substitua pelo nome da sua rede Wi-Fi
const char* password = "SUA_SENHA"; // Substitua pela senha da sua rede Wi-Fi

// Pino onde o relé está conectado
const int relayPin = D1; // Pino D1 da Wemos D1

// Cria uma instância do servidor web na porta 80
ESP8266WebServer server(80);

// Variável para armazenar o estado da lâmpada
bool lampState = false;

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);

  // Configura o pino do relé como saída
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Inicia com o relé desligado (HIGH para relés ativos em LOW)

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado ao Wi-Fi");
  Serial.println(WiFi.localIP());

  // Configura as rotas do servidor web
  server.on("/", handleRoot); // Rota principal
  server.on("/control", handleControl); // Rota para controlar a lâmpada
  server.on("/status", handleStatus); // Rota para obter o status da lâmpada

  // Inicia o servidor web
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  // Mantém o servidor web ativo
  server.handleClient();
}

// Função para lidar com a rota principal
void handleRoot() {
  server.send(200, "text/plain", "Bem-vindo ao controle de lâmpada!");
}

// Função para lidar com a rota de controle da lâmpada
void handleControl() {
  if (server.method() == HTTP_POST) {
    String command = server.arg("command");

    if (command == "on") {
      digitalWrite(relayPin, LOW); // Liga o relé (LOW para relés ativos em LOW)
      lampState = true;
      server.send(200, "text/plain", "Lâmpada ligada");
    } else if (command == "off") {
      digitalWrite(relayPin, HIGH); // Desliga o relé (HIGH para relés ativos em LOW)
      lampState = false;
      server.send(200, "text/plain", "Lâmpada desligada");
    } else {
      server.send(400, "text/plain", "Comando inválido");
    }
  } else {
    server.send(405, "text/plain", "Método não permitido");
  }
}

// Função para lidar com a rota de status da lâmpada
void handleStatus() {
  String status = lampState ? "on" : "off";
  server.send(200, "text/plain", status);
}
