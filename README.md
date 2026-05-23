# pet-detector-clyvoday
# 🐾 Pet Detector — IoT & Visão Computacional

> Projeto desenvolvido para a disciplina **Disruptive Architectures: IoT, IoB & Generative IA** — FIAP 2TDSPI

---

## 📌 Descrição do Projeto

O **Pet Detector** é um sistema inteligente de monitoramento de pets que combina **IoT com ESP32** e **Visão Computacional com Python/YOLOv8** para detectar a presença de animais de estimação em tempo real.

Quando o pet se aproxima a menos de **30cm** do sensor, o sistema:
- Acende um **LED de alerta**
- Envia os dados para um **Dashboard no Blynk** via HTTP
- Detecta e identifica o pet visualmente usando **IA (YOLOv8)**

---

## 🎯 Problema que resolve

O Pet Detector resolve a falta de monitoramento e rotina no cuidado com pets — detectando a presença e atividade do animal em tempo real através de IoT e Visão Computacional, integrado a um sistema de gamificação que engaja o tutor nas tarefas diárias do pet.
---

## 🛠️ Tecnologias Utilizadas

### IoT
| Tecnologia | Função |
|---|---|
| **ESP32** | Microcontrolador principal |
| **HC-SR04** | Sensor ultrassônico de distância |
| **LED** | Alerta visual de presença |
| **Wokwi** | Simulador do circuito |
| **Blynk** | Dashboard IoT via HTTP |

### Visão Computacional
| Tecnologia | Função |
|---|---|
| **Python 3.11+** | Linguagem principal |
| **YOLOv8 (Ultralytics)** | Modelo de detecção de objetos |
| **OpenCV** | Captura de câmera e output visual |

---

## 🏗️ Arquitetura do Sistema

```
┌─────────────────────────────────────────────────────┐
│                   PET DETECTOR                      │
│                                                     │
│  [HC-SR04] ──► [ESP32 - Wokwi] ──► [LED acende]   │
│                      │                              │
│                      ▼ HTTP                         │
│               [Blynk Dashboard]                     │
│               • Gauge: distância                    │
│               • LED virtual: alerta                 │
│               • Gráfico histórico                   │
│                                                     │
│  [Câmera/Vídeo] ──► [YOLOv8] ──► [OpenCV]         │
│                      │                              │
│                      ▼                              │
│            [Bounding Box na tela]                   │
│            🐶 Cachorro 94%                          │
└─────────────────────────────────────────────────────┘
```

---

## 📁 Estrutura do Repositório

```
pet-detector/
│
├── iot/
│   ├── sketch.ino          # Código ESP32 completo
│   ├── diagram.json        # Diagrama do circuito Wokwi
│   └── wokwi.toml          # Configuração das bibliotecas
│
├── visao-computacional/
│   ├── detector.py         # Script principal de detecção
│   └── requirements.txt    # Dependências Python
│
├── assets/
│   ├── circuito.png        # Print do circuito no Wokwi
│   ├── dashboard.png       # Print do Dashboard Blynk
│   └── deteccao.jpg        # Resultado da detecção com bounding box
│
└── README.md
```

---

## ⚙️ Como Executar

### Parte 1 — IoT (Wokwi + Blynk)

**1. Acesse o simulador:**
- Abra [wokwi.com](https://wokwi.com) e crie um novo projeto ESP32

**2. Configure o Blynk:**
- Crie uma conta em [blynk.cloud](https://blynk.cloud)
- Crie um Template → Hardware: ESP32
- Adicione os Datastreams:
  - `V0` → Distância (Double, 0–400)
  - `V1` → Movimento (Integer, 0–1)
  - `V2` → Visitas do Pet (Integer, 0-9999)
- Copie seu `BLYNK_AUTH_TOKEN`

**3. Cole o código:**
- Copie o conteúdo de `iot/sketch.ino` no editor do Wokwi
- Substitua `seu_auth_token` pelo token do Blynk

**4. Cole o diagrama:**
- Copie o conteúdo de `iot/diagram.json` na aba diagram do Wokwi

**5. Execute:**
- Clique em ▶ Play
- Arraste o slider do sensor HC-SR04 para menos de 30cm
- Veja o LED acender e o Dashboard Blynk atualizar!

---

### Parte 2 — Visão Computacional

**1. Instale as dependências:**
```bash
pip install ultralytics opencv-python
```

**2. Execute o detector:**
```bash
cd visao-computacional
python detector.py
```

**3. Aponte para um pet:**
- Use a webcam ou substitua pela linha do vídeo/imagem no código
- O sistema detecta e desenha o bounding box automaticamente
- Pressione `Q` para sair

---

## 🔌 Esquema do Circuito

| Componente | Pino ESP32 |
|---|---|
| HC-SR04 VCC | 3.3V |
| HC-SR04 GND | GND |
| HC-SR04 TRIG | GPIO 5 |
| HC-SR04 ECHO | GPIO 18 |
| LED Anodo (+) | GPIO 2 (via resistor 1kΩ) |
| LED Catodo (-) | GND |

---

## 📊 Dashboard Blynk

O dashboard exibe em tempo real:
- **Gauge** — distância atual em cm
- **LED virtual** — acende quando pet detectado (≤ 30cm)
- **Gráfico** — histórico de distância ao longo do tempo
- **Rótulo** - contador de visitas ao sensor 
---

## 🤖 Visão Computacional — Como funciona

O modelo **YOLOv8n** (nano) é pré-treinado no dataset COCO e reconhece as seguintes classes de pets:

| ID | Animal |
|---|---|
| 15 | Gato |
| 16 | Cachorro |
| 17 | Cavalo |
| 18 | Ovelha |

O script filtra apenas detecções com **confiança acima de 50%** e desenha:
- Retângulo verde em volta do animal
- Nome da espécie + percentual de confiança
- Alerta "🐾 PET DETECTADO!" no topo da tela

---

## 📹 Vídeo de Demonstração

🎥 [Assistir no YouTube](https://youtu.be/fj1PwvogYFk?si=Jnu9cvxSa40WakwK)

---

## 👥 Integrantes

| Nome | RM |
|---|---|
| Beatriz Franco | RM563686 |
| Maria Fernanda Mendes | RM565277 |
| Giovana Souza Vieira | RM564430 |

---

## 📚 Referências

- [Documentação Wokwi](https://docs.wokwi.com)
- [Blynk Documentation](https://docs.blynk.io)
- [Ultralytics YOLOv8](https://docs.ultralytics.com)
- [OpenCV Python](https://opencv.org)
- [Dataset COCO Classes](https://cocodataset.org)
