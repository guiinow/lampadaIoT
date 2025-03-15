const express = require("express");
const cors = require("cors");

const app = express();
const port = 3000;

app.use(cors()); // Habilita o CORS
app.use(express.json());

let lampState = "off";
let commandHistory = [];

app.post("/lamp", (req, res) => {
  const { action, timer } = req.body;
  lampState = action;
  commandHistory.unshift(
    `Lâmpada ${action.toUpperCase()} às ${new Date().toLocaleTimeString()}`
  );

  if (action === "on" && timer > 0) {
    setTimeout(() => {
      lampState = "off";
      commandHistory.unshift(
        `Desligamento automático às ${new Date().toLocaleTimeString()}`
      );
    }, timer * 60000); // Converte minutos para milissegundos
  }

  res.json({ message: "Comando recebido" });
});

app.get("/status", (req, res) => {
  res.json({ lampState, commandHistory });
});

app.listen(port, () => {
  console.log(`Servidor rodando em http://localhost:${port}`);
});


/*
📌 Como executar:
1. Certifique-se de ter o Node.js instalado.
2. Crie uma pasta, salve este arquivo como 'server.js'.
3. No terminal:
   - npm install
   - node server.js
4. Acesse: http://localhost:3000
*/
