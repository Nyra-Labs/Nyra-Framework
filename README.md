# Nyra Agent Framework

[![Watch the Showcase Video](https://img.youtube.com/vi/Uz8djygCPCY/maxresdefault.jpg)](https://youtu.be/Uz8djygCPCY)

## Prerequisites

| Category | Requirements |
|----------|-------------|
| **Keys** | • Agora App ID and App Certificate (free minutes every month) <br>• OpenAI API key<br>• Deepgram ASR (free credits available with signup)<br>• FishAudio TTS (free credits available with signup)|
| **Installation** | • Docker / Docker Compose<br>• Node.js(LTS) v18 |
| **Minimum System Requirements** | • CPU >= 2 Core<br>• RAM >= 4 GB |

## Local Setup

### 1. Create `.env` file
```bash
cp ./.env.example ./.env
```

### 2. Setup Agora App ID and App Certificate in `.env`
```bash
AGORA_APP_ID=
AGORA_APP_CERTIFICATE=
```

### 3. Start agent development containers
```bash
docker compose up -d
```

### 4. Enter container
```bash
docker exec -it nyra_agent_playground bash
```

### 5. Build agent 
```bash
task use
```

### 6. Start the web server
```bash
task run
```

### 7. Edit playground settings
Open the playground at localhost:3000 to configure your agent.
1. Select a graph type (e.g. Voice Agent, Realtime Agent)
2. Choose a corresponding module
3. Select an extension and configure its API key settings

## License

This project is licensed under the Apache 2.0 License - see the LICENSE file for details.
