#define PED_GREEN 400
#define PED_RED 500
#define RED 100
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

PedestrianLight pedestrianLight(5, 6, 7);

int receivedTrafficState = 0;

void setup() {
  Serial.begin(9600);
  pedestrianLight.setup();
}

void loop() {
  if (Serial.available() > 0) {
    receivedTrafficState = Serial.read();
    pedestrianLight.update(receivedTrafficState);
  }
  pedestrianLight.checkButtonPress();
}
