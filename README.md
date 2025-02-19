# 🎮 Controle de LEDs e Display com Joystick

## 📌 Descrição do Projeto
Este projeto utiliza um **joystick analógico** para controlar a intensidade luminosa dos **LEDs RGB Azul e Vermelho** de acordo com os valores do eixo Y e X, respectivamente. Além disso, um **display SSD1306** exibe um quadrado de **8x8 pixels** que se move conforme os valores do joystick. O sistema também permite alternar a ativação de saídas com PWM dos LEDs e ativar o modo reboot por meio de botões físicos.

---

## 🛠️ Funcionalidades
- **Controle de intensidade luminosa dos LEDs RGB Azul e Vermelho** baseado no deslocamento do joystick.
- **Controle de LEDs via PWM**, garantindo variação suave de brilho.
- **Movimentação de um quadrado no display SSD1306** de acordo com os valores capturados pelo joystick.
- **Botões físicos para controle do sistema:**
  - **Botão A**: Ativa/desativa a saída PWM do **LED RGB, em Azul e Vermelho**.
  - **Botão do Joystick**: Alterna o estado do **LED RGB Verde** e **alterna a borda do display SSD1306** entre dois modelos.
  - **Botão B**: Habilita o modo **reboot**.
- **Implementação de interrupções (IRQ) para os botões**.
- **Tratamento de bouncing dos botões** via software.
- **Simulação no Wokwi integrada ao VS Code** via UART.
- **Utilização do display SSD1306** via protocolo **I2C**.

---

## 🔧 Hardware Necessário - Presentes na Placa de Desenvolvimento BitDogLab
- **Microcontrolador Raspberry Pi Pico W**
- **Joystick analógico**
- **LED RGB**
- **Display SSD1306 (128x64) - I2C**
- **Botões físicos**:
  - **Botão A** (Ativar/desativar LEDs PWM)
  - **Botão do Joystick** (Alternar LED Verde e borda do display)
  - **Botão B** (Modo reboot)
- **Fonte de alimentação adequada**

---

## 📌 Como Rodar o Projeto
### **Softwares Necessários**
1. **VS Code** com a extensão **Raspberry Pi Pico** instalada.
2. **CMake** e **Ninja** configurados.
3. **SDK do Raspberry Pi Pico** corretamente configurado.
4. Simulador **Wokwi** instalado e integrado ao VS Code.

### **Clonando o Repositório**
Para começar, clone o repositório no seu computador:
```bash
git clone https://github.com/EdnaRodrigues/Joystick.git
cd Joystick
```

---

### **Execução no Projeto no VS Code**

#### **1. Importar o Projeto**
Após clonar o repositório:
1. Abra o **VS Code**.
2. No menu **Raspberry Pi Pico**, selecione **Import Project**.
3. Escolha a pasta clonada e clique em **Import**.

#### **2. Compilar o Código**
1. Clique no ícone **Raspberry Pi Pico** no lado esquerdo do VS Code.
2. Escolha a opção **Compile Project** para compilar o código.

---

### **Execução no Simulador Wokwi**

#### **1. Configurar o Simulador Wokwi**
1. Abra o arquivo `diagram.json` incluído no repositório.
2. Certifique-se de que o arquivo JSON está configurado corretamente para a simulação do hardware necessário:
   - Joystick conectado aos pinos ADC GPIO 26 e 27.
   - Botão do Joystick conectado ao pino GPIO 22.
   - LEDs RGB devidamente conectado aos GPIOs 11, 12 e 13.
   - Botões A e B conectados, respectivamente, aos pinos GPIO 5 e 6.
   - Display SSD1306 via I2C, conectado aos pinos GPIO 14 e 15.

#### **2. Executar a Simulação**
1. Abra o painel do simulador Wokwi no VS Code.
2. Clique em **Play** para iniciar a simulação.

---

### **Execução na Placa BitDogLab**

#### **1. Coloque em Modo Reboot**
1. Aperte o botão **BOOTSEL** no microcontrolador Raspberry Pi Pico W.
2. Ao mesmo tempo, aperte o botão de **Reset**.

#### **2. Upload de Arquivo `Joystick.uf2`**
1. Abra a pasta `build` incluída no repositório.
2. Mova o arquivo `Joystick.uf2` para a placa de desenvolvimento.

#### **3. Acompanhar Execução do Programa**
1. Observe o controle de intensidade dos LEDs RGB via joystick.
2. Monitore a movimentação do quadrado no display SSD1306.
3. Teste os botões e veja as alterações.

---

## 📽️ Vídeo de Demonstração

[Assista ao vídeo explicativo aqui!](conter link)

---

## ✉️ Contato
Caso tenha dúvidas ou sugestões, entre em contato com o desenvolvedor.
