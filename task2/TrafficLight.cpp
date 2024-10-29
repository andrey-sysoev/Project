#define RED 100
#define YELLOW 200
#define GREEN 300
#define PED_GREEN 400
#define PED_RED 500

class TrafficLight {
  private:
    int led_red, led_yellow, led_green;
    const long redDuration = 10000;
    const long yellowDuration = 5000;
    const long greenDuration = 10000;
    int currentState = RED;
    unsigned long previousMillis = 0;

  public:
    TrafficLight(int red, int yellow, int green) {
      led_red = red;
      led_yellow = yellow;
      led_green = green;
    }

    void setup() {
      pinMode(led_red, OUTPUT);
      pinMode(led_yellow, OUTPUT);
      pinMode(led_green, OUTPUT);
      digitalWrite(led_red, HIGH);
      digitalWrite(led_yellow, LOW);
      digitalWrite(led_green, LOW);
    }

    void update() {
      unsigned long currentMillis = millis();

      switch (currentState) {
        case RED:
          if (currentMillis - previousMillis >= redDuration) {
            previousMillis = currentMillis;
            currentState = YELLOW;
            digitalWrite(led_red, LOW);
            digitalWrite(led_yellow, HIGH);
          }
          break;

        case YELLOW:
          if (currentMillis - previousMillis >= yellowDuration) {
            previousMillis = currentMillis;
            currentState = GREEN;
            digitalWrite(led_yellow, LOW);
            digitalWrite(led_green, HIGH);
          }
          break;

        case GREEN:
          if (currentMillis - previousMillis >= greenDuration) {
            previousMillis = currentMillis;
            currentState = RED;
            digitalWrite(led_green, LOW);
            digitalWrite(led_red, HIGH);
          }
          break;
      }
    }

    int getCurrentState() {
      return currentState;
    }
};

class PedestrianLight {
  private:
    int pRed, pGreen, buttonPin;
    int currentPedState = PED_RED;
    bool buttonPressed = false;

  public:
    PedestrianLight(int red, int green, int button) {
      pRed = red;
      pGreen = green;
      buttonPin = button;
    }

    void setup() {
      pinMode(pRed, OUTPUT);
      pinMode(pGreen, OUTPUT);
      pinMode(buttonPin, INPUT_PULLUP);
      digitalWrite(pRed, HIGH);
      digitalWrite(pGreen, LOW);
    }

    void checkButtonPress() {
      if (digitalRead(buttonPin) == LOW) {
        buttonPressed = true;
      }
    }

    void update(int trafficState) {
      switch (currentPedState) {
        case PED_RED:
          if (buttonPressed && trafficState == RED) {
            currentPedState = PED_GREEN;
            buttonPressed = false;
            digitalWrite(pRed, LOW);
            digitalWrite(pGreen, HIGH);
          }
          break;

        case PED_GREEN:
          delay(6000);
          currentPedState = PED_RED;
          digitalWrite(pGreen, LOW);
          digitalWrite(pRed, HIGH);
          break;
      }
    }
};

TrafficLight trafficLight(2, 3, 4);
PedestrianLight pedestrianLight(5, 6, 7);

void setup() {
  trafficLight.setup();
  pedestrianLight.setup();
}

void loop() {
  trafficLight.update();
  pedestrianLight.checkButtonPress();
  pedestrianLight.update(trafficLight.getCurrentState());
}
