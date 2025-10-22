#define PIN_VERM 9
#define PIN_VERD 7
#define PIN_AZUL 3
#define PIN_AMAR 2

class Luzes {
private:
  int pinos[4];
  int ledAtivoIndex;

public:
  Luzes(int pinoVerm, int pinoVerd, int pinoAzul, int pinoAmar) {
    pinos[0] = pinoVerm;
    pinos[1] = pinoVerd;
    pinos[2] = pinoAzul;
    pinos[3] = pinoAmar;

    for (int i = 0; i < 4; i++) {
      pinMode(pinos[i], OUTPUT);
    }
    
    ledAtivoIndex = -1;
    apagarTodas();
  }

  void atualizarLuzes() {
    for (int i = 0; i < 4; i++) {
      if (i == ledAtivoIndex) {
        digitalWrite(pinos[i], HIGH);
      } else {
        digitalWrite(pinos[i], LOW);
      }
    }
  }

  void moverEsquerda() {
    if (ledAtivoIndex == -1) {
      ledAtivoIndex = 0;
    } else {
      ledAtivoIndex--;
    }

    if (ledAtivoIndex < 0) {
      ledAtivoIndex = 3; 
    }

    Serial.print("Luz ativa: ");
    Serial.println(ledAtivoIndex);
    
    atualizarLuzes();
  }

  void moverDireita() {
    if (ledAtivoIndex == -1) {
      ledAtivoIndex = 0;
    } else {
      ledAtivoIndex++;
    }

    ledAtivoIndex = ledAtivoIndex % 4;

    Serial.print("Luz ativa: ");
    Serial.println(ledAtivoIndex);

    atualizarLuzes();
  }

  void apagarTodas() {
    for (int i = 0; i < 4; i++) {
      digitalWrite(pinos[i], LOW);
    }
  }
};

Luzes sistemaDeLuzes(PIN_VERM, PIN_VERD, PIN_AZUL, PIN_AMAR);

void setup() {
  Serial.begin(9600);
  Serial.println("Sistema de Luzes iniciado.");
  Serial.println("Digite 'a' (esquerda) ou 'd' (direita).");
}

void loop() {
  if (Serial.available()) {
    
    String comando = Serial.readStringUntil('\n');
    comando.trim(); 

    if (comando == "a" || comando == "A") {
      Serial.println("Comando: Esquerda");
      sistemaDeLuzes.moverEsquerda();
      
    } else if (comando == "d" || comando == "D") {
      Serial.println("Comando: Direita");
      sistemaDeLuzes.moverDireita();
    }
  }
}
