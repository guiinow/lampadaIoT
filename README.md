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