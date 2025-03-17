# 📡 Controle de Lâmpada com Wemos D1, Wi-Fi e Alexa

Este projeto permite controlar uma lâmpada usando a placa **Wemos D1 (ESP8266)** de duas maneiras:

1. **Via Wi-Fi**: Através de requisições POST em um servidor web local.
2. **Via Alexa**: Usando comandos de voz através do app da Alexa ou dispositivos compatíveis.

## 📋 Funcionalidades
- **Ligar/Desligar a lâmpada** através de comandos HTTP.
- **Integração com Alexa** utilizando a biblioteca **FauxmoESP**.
- **Consultar o status atual** da lâmpada.

---

## 🛠️ Componentes Necessários
- **Wemos D1 (ESP8266)**
- **Módulo Relé 5V** (compatível com a Wemos D1)
- **Lâmpada (127V ou 220V)**
- **Fonte de alimentação USB (5V)**
- **Jumpers e Protoboard**

---

## 📊 Esquema de Ligação

1. **Conexão do Relé com a Wemos D1:**
   - **D1** → **Pino de Sinal (IN)** do Relé
   - **GND** → **GND** do Relé
   - **5V** → **VCC** do Relé

2. **Conexão do Relé com a Lâmpada:**
   - **COM** → **Fase da tomada (127V/220V)**
   - **NO** → **Fio da lâmpada**
   - **Neutro** da lâmpada → **Neutro da tomada**


---

## 🚀 Configuração do Ambiente

### 1. Instalar o pacote ESP8266 no Arduino IDE:
1. Vá para: `Arquivo` → `Preferências`
2. No campo **URLs Adicionais para Gerenciadores de Placas**, adicione:

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

3. Em `Ferramentas` → `Placa` → `Gerenciador de Placas`, pesquise **esp8266** e instale.

### 2. Instalar a biblioteca FauxmoESP:
- Vá em: `Ferramentas` → `Gerenciar Bibliotecas`
- Pesquise por **FauxmoESP** e instale a versão mais recente.

---

## 📄 Como Carregar o Código na Wemos D1

1. Conecte a **Wemos D1** ao seu computador via USB.
2. No **Arduino IDE**, selecione:
   - Placa: `Wemos D1 R1`
   - Porta: A porta serial correspondente.
3. Atualize as configurações de Wi-Fi no código:

```cpp
const char* ssid = "SEU_SSID";      // Nome da sua rede Wi-Fi
const char* password = "SUA_SENHA"; // Senha da sua rede Wi-Fi
```

4. Clique em **Upload** para enviar o código para a placa.

---

## 🔎 Testando o Sistema

### 1. Verificar a Conexão com o Wi-Fi
Após o upload do código, abra o **Serial Monitor** (`Ctrl + Shift + M`) e verifique:

```
Conectando ao Wi-Fi...
Conectado ao Wi-Fi
Endereço IP: 192.168.x.x
```

### 2. Controlar a Lâmpada via Wi-Fi
- Envie uma requisição **POST** para o IP da Wemos:

#### Para ligar a lâmpada:
```bash
curl -X POST http://192.168.x.x/control -d "command=on"
```

#### Para desligar a lâmpada:
```bash
curl -X POST http://192.168.x.x/control -d "command=off"
```

#### Para verificar o status da lâmpada:
```bash
curl http://192.168.x.x/status
```

### 3. Controlar a Lâmpada via Alexa

1. No **app da Alexa**, vá em:
   - **Dispositivos** → **Adicionar dispositivo** → **Luz** → **Outro**
   - Clique em **Detectar dispositivos**

2. Após a detecção, você poderá usar comandos como:
   - "Alexa, ligue a lâmpada"
   - "Alexa, desligue a lâmpada"

---

## 🔧 Resolução de Problemas

1. **A Alexa não encontra o dispositivo:**
   - Certifique-se de que o dispositivo está na **mesma rede Wi-Fi** que o app da Alexa.
   - Reinicie a Wemos D1.

2. **A lâmpada não liga/desliga:**
   - Verifique a **conexão do relé**.
   - Certifique-se de que o relé é compatível com **nível lógico de 3,3V**.

---

## 📌 Recursos Adicionais

- **Documentação do FauxmoESP:** https://github.com/vintlabs/fauxmoESP
- **Exemplo de controle Wi-Fi com ESP8266:** https://arduino-esp8266.readthedocs.io/

