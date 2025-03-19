#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <fauxmoESP.h> // Biblioteca para integração com Alexa

// Configurações de Wi-Fi
const char* ssid = "MansaoLuxuria_2.4G"; // Nome da sua rede Wi-Fi, DA SUA CASA
const char* password = "luXuria.1010"; // Senha da sua rede Wi-Fi, DA SUA CASA

// Cria uma instância do servidor web
ESP8266WebServer server(8080);

// Pinos
const int relayPin = D1; // Pino do relé


// Cria uma instância do FauxmoESP (Alexa)
fauxmoESP fauxmo;

// Variável para armazenar o estado da lâmpada
bool lampState = false;

// Função para alternar o estado da lâmpada
void setLamp(bool state) {
    lampState = state;
    digitalWrite(relayPin, lampState ? LOW : HIGH); // Relé ativo em LOW
    Serial.println(lampState ? "Lâmpada ligada" : "Lâmpada desligada");
}

void setup() {
    // Inicializa a comunicação serial
    Serial.begin(115200);

    // Conecta ao Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
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

    // Configura o dispositivo para Alexa
    fauxmo.addDevice("lampada"); // Nome que a Alexa reconhecerá
    fauxmo.onSetState([](unsigned char device_id, const char *device_name, bool state, unsigned char value) {
        Serial.printf("[Alexa] Comando recebido para: %s\n", device_name);
        setLamp(state);
    });

    // Configura o pino do relé como saída
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH); // Começa com a lâmpada desligada
}

void loop() {
    // Mantém o servidor web ativo
    server.handleClient();

    // Atualiza o fauxmo para responder à Alexa
    fauxmo.handle();
}

// Função para a rota principal
void handleRoot() {
    server.send(200, "text/plain", "Bem-vindo ao controle de lâmpada!");
}

// Função para controlar a lâmpada via POST
void handleControl() {
    if (server.method() == HTTP_POST) {
        String command = server.arg("command");

        if (command == "on") {
            setLamp(true);
            server.send(200, "text/plain", "Lâmpada ligada");
        } else if (command == "off") {
            setLamp(false);
            server.send(200, "text/plain", "Lâmpada desligada");
        } else {
            server.send(400, "text/plain", "Comando inválido");
        }
    } else {
        server.send(405, "text/plain", "Método não permitido");
    }
}

// Função para retornar o status da lâmpada
void handleStatus() {
    String status = lampState ? "on" : "off";
    server.send(200, "text/plain", status);
}
