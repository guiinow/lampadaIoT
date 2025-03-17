# Explicação do Código

## Conexão Wi-Fi
O código começa conectando a Wemos D1 à rede Wi-Fi usando as credenciais fornecidas (`ssid` e `password`).

## Controle do Relé
O relé está conectado ao pino `D1` da Wemos D1. O relé é controlado por meio dos comandos `digitalWrite(relayPin, LOW)` para ligar e `digitalWrite(relayPin, HIGH)` para desligar. Isso depende do tipo de relé que você está usando (ativo em LOW ou HIGH).

## Servidor Web
O servidor web é configurado para responder a três rotas:

- **`/`**: Rota principal que retorna uma mensagem de boas-vindas.
- **`/control`**: Rota que recebe comandos POST para ligar (`on`) ou desligar (`off`) a lâmpada.
- **`/status`**: Rota que retorna o status atual da lâmpada (`on` ou `off`).

## Manipulação de Requisições
A função `handleControl` processa os comandos recebidos e controla o relé de acordo. A função `handleStatus` retorna o estado atual da lâmpada.

# Como Funciona
- Quando você envia uma requisição POST para a rota `/control` com o comando `on` ou `off`, a Wemos D1 altera o estado do relé e, consequentemente, da lâmpada.
- A rota `/status` pode ser usada para verificar o estado atual da lâmpada.

# Testes e Melhorias
- **Status em Tempo Real**: Você pode atualizar a interface HTML para consultar periodicamente a rota `/status` e exibir o estado atual da lâmpada.
- **Timer**: Implemente um temporizador na Wemos D1 ou no servidor Node.js para desligar a lâmpada após um determinado tempo.
- **Histórico de Comandos**: Adicione uma funcionalidade no servidor Node.js para registrar as ações e exibi-las na interface.

# Próximos Passos
1. Carregue o código na Wemos D1.
2. Certifique-se de que o servidor Node.js está configurado para enviar os comandos corretos para a Wemos D1.
3. Teste o fluxo completo (interface → servidor → Wemos → lâmpada).

# Configure o Arduino IDE para a Wemos D1
1. **Instale o pacote do ESP8266 no Arduino IDE** (se ainda não tiver feito):
   - Vá em `Arquivo` → `Preferências`.
   - No campo "URLs Adicionais para Gerenciadores de Placas", adicione: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`.
   - Clique em `OK`.
   - Vá em `Ferramentas` → `Placa` → `Gerenciador de Placas`.
   - Procure por `esp8266` e instale a versão mais recente.
2. **Selecione a placa correta**:
   - Vá em `Ferramentas` → `Placa` → `ESP8266 Boards` → `Wemos D1 R1`.

# Carregue o código na Wemos D1
1. Conecte a Wemos D1 ao computador via USB.
2. No Arduino IDE, selecione a porta correta em `Ferramentas` → `Porta`.
3. Clique no botão de upload (seta para a direita) para carregar o código na placa.

# Verifique o funcionamento
1. Após o upload, abra o **Serial Monitor** (`Ctrl+Shift+M`) para ver as mensagens de depuração.
2. Verifique se a Wemos D1 se conecta ao Wi-Fi e inicia o servidor web.


--
Aqui está o texto em formato Markdown (`.md`) e, em seguida, vou te explicar como criar o diagrama visual.

---

### **Circuito para Montagem com Lâmpada de 127V**

#### **Componentes Necessários:**
1. **Wemos D1** (ESP8266).
2. **Módulo Relé 5V** (compatível com a Wemos D1).
3. **Lâmpada de 127V**.
4. **Fonte de Alimentação 127V** (tomada).
5. **Jumpers e Protoboard** (para conexões de baixa tensão).
6. **Diodo 1N4007** (opcional, para proteção do relé).

---

### **Esquema do Circuito**

1. **Conexão da Wemos D1 ao Relé:**
   - **Pino D1** da Wemos D1 → **Pino de Sinal (IN)** do relé.
   - **GND** da Wemos D1 → **GND** do relé.
   - **VCC (5V)** da Wemos D1 → **VCC** do relé.

2. **Conexão do Relé à Lâmpada de 127V:**
   - **Terminal COM (Common)** do relé → **Fase (Live)** da tomada 127V.
   - **Terminal NO (Normally Open)** do relé → **Fio da Lâmpada**.
   - **Neutro (Neutral)** da tomada 127V → **Neutro da Lâmpada**.

3. **Alimentação da Wemos D1:**
   - Conecte a Wemos D1 ao computador ou a um carregador USB para alimentação.

---

### **Diagrama Visual**

Aqui está uma descrição textual do circuito. Para criar um diagrama visual, você pode usar ferramentas como **Fritzing**, **Tinkercad** ou **EasyEDA**:

1. **Wemos D1:**
   - Conecte o **pino D1** ao **pino IN** do relé.
   - Conecte o **GND** da Wemos ao **GND** do relé.
   - Conecte o **5V** da Wemos ao **VCC** do relé.

2. **Relé:**
   - Conecte o **COM** do relé ao **fio fase** da tomada 127V.
   - Conecte o **NO** do relé ao **fio da lâmpada**.
   - Conecte o **neutro** da tomada diretamente ao **neutro da lâmpada**.

3. **Lâmpada de 127V:**
   - Conecte os fios da lâmpada ao relé e à tomada, como descrito acima.

---

### **Funcionamento do Circuito:**
- Quando a Wemos D1 recebe o comando `on`, o pino `D1` é colocado em **LOW**, ativando o relé e ligando a lâmpada.
- Quando a Wemos D1 recebe o comando `off`, o pino `D1` é colocado em **HIGH**, desativando o relé e desligando a lâmpada.

---

### **Cuidados Importantes:**
1. **Alta Tensão (127V):**
   - **Tome muito cuidado** ao fazer as conexões de alta tensão. Use fiação adequada e isole bem os fios.
   - Se não tiver experiência com alta tensão, recomendo pedir ajuda a alguém com conhecimento.

2. **Proteção do Relé:**
   - Para proteger o relé de picos de tensão, adicione um diodo (como o 1N4007) em paralelo com a bobina do relé.

---

### **Próximos Passos:**
1. Monte o circuito conforme o esquema.
2. Conecte a Wemos D1 ao computador e carregue o código `.ino`.
3. Teste o sistema enviando comandos da interface HTML.

---

### **Como Criar o Diagrama Visual:**
1. Use uma ferramenta como **Fritzing** ou **Tinkercad**.
2. Adicione os componentes (Wemos D1, relé, lâmpada, fiação).
3. Conecte os componentes conforme o esquema descrito.
4. Exporte o diagrama como imagem (PNG ou JPG).

Se precisar de ajuda para criar o diagrama visual, é só avisar! 😊

---


Como ligar uma lampada com relé:
https://www.youtube.com/watch?v=dPffe7HvyBE

Projeto no Tinkercad: https://www.tinkercad.com/things/4tZLbfxSfTW/editel?sharecode=az9ygDZ3AJ-f6Z3BsYOX2g1nxCJR06t5jxiKztGDQuI