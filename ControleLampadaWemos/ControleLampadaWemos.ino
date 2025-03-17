#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configurações de Wi-Fi
const char *ssid = "SEU_SSID";      // Substitua pelo nome da sua rede Wi-Fi
const char *password = "SUA_SENHA"; // Substitua pela senha da sua rede Wi-Fi

// Pinos
const int relayPin = D1; // Pino do relé
const int micPin = A0;   // Pino do microfone analógico

// Limiar de som para detectar o acionamento (ajuste conforme necessário)
const int soundThreshold = 500;

// Ruído de fundo: ~300
// Som alto (palma ou estalo): ~800

// Cria uma instância do servidor web na porta 80
ESP8266WebServer server(80);

// Variável para armazenar o estado da lâmpada
bool lampState = false;

// Função para alternar a lâmpada
void toggleLamp()
{
  lampState = !lampState;
  digitalWrite(relayPin, lampState ? LOW : HIGH);
}

void setup()
{
  // Inicializa a comunicação serial
  Serial.begin(115200);

  // Configura o pino do relé como saída
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Inicia com o relé desligado

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi");
  Serial.println(WiFi.localIP());

  // Configura as rotas do servidor web
  server.on("/", handleRoot);
  server.on("/control", handleControl);
  server.on("/status", handleStatus);

  // Inicia o servidor web
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop()
{
  // Mantém o servidor web ativo
  server.handleClient();

  // Lê o valor do microfone
  int micValue = analogRead(micPin);
  // O analogRead(micPin) retorna valores entre 0 e 1023(10 bits de resolução do ADC do ESP8266).

    // Se o som ultrapassar o limiar, alterna a lâmpada
    if (micValue > soundThreshold)
  {
    toggleLamp();
    Serial.println("Som detectado! Alternando lâmpada.");
    delay(500); // Pequeno atraso para evitar múltiplas detecções rápidas
  }

  int micValue = analogRead(micPin);
  Serial.println(micValue);
  delay(100);
}

// Função para lidar com a rota principal
void handleRoot()
{
  server.send(200, "text/plain", "Bem-vindo ao controle de lâmpada!");
}

// Função para lidar com a rota de controle da lâmpada
void handleControl()
{
  if (server.method() == HTTP_POST)
  {
    String command = server.arg("command");

    if (command == "on")
    {
      digitalWrite(relayPin, LOW); // Liga a lâmpada
      lampState = true;
      server.send(200, "text/plain", "Lâmpada ligada");
    }
    else if (command == "off")
    {
      digitalWrite(relayPin, HIGH); // Desliga a lâmpada
      lampState = false;
      server.send(200, "text/plain", "Lâmpada desligada");
    }
    else
    {
      server.send(400, "text/plain", "Comando inválido");
    }
  }
  else
  {
    server.send(405, "text/plain", "Método não permitido");
  }
}

// Função para lidar com a rota de status da lâmpada
void handleStatus()
{
  String status = lampState ? "on" : "off";
  server.send(200, "text/plain", status);
}
