#define RED 100
#define YELLOW_GREEN 200
#define YELLOW_RED 400
#define GREEN 300
#define PED_GREEN 500
#define PED_RED 600
class TrafficLight {
  private:
    int led_red, led_yellow, led_green, buttonPin;
    const long redDuration = 10000;
    const long yellowDuration = 5000;
    const long greenDuration = 10000;
    const long pedGreenDuration = 6000;
    int currentState = RED;
    unsigned long previousMillis = 0;
    bool buttonPressed = false;
    bool pedestrianCycleActive = false;
    unsigned long pedGreenStartTime = 0;
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
            currentState = YELLOW_GREEN;
            digitalWrite(led_red, LOW);
            digitalWrite(led_yellow, HIGH);
          }
          break;
        case YELLOW_GREEN:
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
            currentState = YELLOW_RED;
            digitalWrite(led_green, LOW);
            digitalWrite(led_yellow, HIGH);
          }
          break;
        case YELLOW_RED:
          if (currentMillis - previousMillis >= yellowDuration) {
            previousMillis = currentMillis;
            currentState = RED;
            digitalWrite(led_yellow, LOW);
            digitalWrite(led_red, HIGH);
          }
          break;
      }
    }

    int getCurrentState() {
      return currentState;
    }
};

TrafficLight trafficLight(2, 3, 4, 7);

void setup() {
  Serial.begin(9600);
  trafficLight.setup();
}

void loop() {
  trafficLight.checkButtonPress();
  trafficLight.update();
}
