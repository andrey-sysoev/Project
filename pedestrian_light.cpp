#define PED_GREEN 500
#define PED_RED 600
#define RED 100
#define YELLOW 200
#define GREEN 300
#define YELLOW_RED 400

class PedestrianLight {
  private:
    int pRed, pGreen;
    int currentPedState = PED_RED;

  public:
    PedestrianLight(int red, int green) {
      pRed = red;
      pGreen = green;
    }

    void setup() {
      pinMode(pRed, OUTPUT);
      pinMode(pGreen, OUTPUT);
      digitalWrite(pRed, HIGH);
      digitalWrite(pGreen, LOW);
    }

    void update() {
      if (Serial.available() > 0) {
        int trafficState = Serial.read();

        switch (currentPedState) {
          case PED_RED:
            if (trafficState == RED) {
              currentPedState = PED_GREEN;
              digitalWrite(pRed, LOW);
              digitalWrite(pGreen, HIGH);
            }
            break;

          case PED_GREEN:
            if (trafficState == YELLOW) {
              currentPedState = PED_RED;
              digitalWrite(pGreen, LOW);
              digitalWrite(pRed, HIGH);
            }
            break;
        }
      }
    }
};

class TrafficLightD3 {
  private:
    int led_red, led_yellow, led_green;
    const long redDuration = 10000;
    const long yellowDuration = 5000;
    const long greenDuration = 10000;

    unsigned long previousMillis = 0;
    int currentState = GREEN;

  public:
    TrafficLightD3(int red, int yellow, int green) {
      led_red = red;
      led_yellow = yellow;
      led_green = green;
    }

    void setup() {
      pinMode(led_red, OUTPUT);
      pinMode(led_yellow, OUTPUT);
      pinMode(led_green, OUTPUT);
      digitalWrite(led_red, LOW);
      digitalWrite(led_yellow, LOW);
      digitalWrite(led_green, HIGH);
    }

    void update() {
      unsigned long currentMillis = millis();

      switch (currentState) {
        case RED:
          digitalWrite(led_red, HIGH);
          digitalWrite(led_yellow, LOW);
          digitalWrite(led_green, LOW);

          if (currentMillis - previousMillis >= redDuration) {
            previousMillis = currentMillis;
            currentState = YELLOW;
          }
          break;

        case YELLOW:
          digitalWrite(led_red, LOW);
          digitalWrite(led_yellow, HIGH);
          digitalWrite(led_green, LOW);

          if (currentMillis - previousMillis >= yellowDuration) {
            previousMillis = currentMillis;
            currentState = GREEN;
          }
          break;

        case GREEN:
          digitalWrite(led_red, LOW);
          digitalWrite(led_yellow, LOW);
          digitalWrite(led_green, HIGH);

          if (currentMillis - previousMillis >= greenDuration) {
            previousMillis = currentMillis;
            currentState = YELLOW_RED;
          }
          break;

        case YELLOW_RED:
          digitalWrite(led_red, LOW);
          digitalWrite(led_yellow, HIGH);
          digitalWrite(led_green, LOW);

          if (currentMillis - previousMillis >= yellowDuration) {
            previousMillis = currentMillis;
            currentState = RED;
          }
          break;
      }
    }
};
PedestrianLight pedestrianLight(5, 6);
TrafficLightD3 trafficLightD3(3, 4, 7); 

void setup() {
  Serial.begin(9600);
  pedestrianLight.setup();
  trafficLightD3.setup();
}

void loop() {
  pedestrianLight.update();
  trafficLightD3.update();
}
