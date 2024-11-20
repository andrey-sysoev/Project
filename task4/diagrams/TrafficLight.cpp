#define D1_D2_RED 100
#define D1_D2_YELLOW_GREEN 200
#define D1_D2_GREEN 300
#define D1_D2_YELLOW_RED 400

class TrafficLight {
  private:
    int d1Red, d1Yellow, d1Green;
    int d2Red, d2Yellow, d2Green;

    const long redDuration = 10000;
    const long yellowGreenDuration = 3000;
    const long greenDuration = 10000;
    const long yellowRedDuration = 3000;
    const long redYellowOverlap = 2000;

    int currentD1D2State = D1_D2_RED;
    unsigned long previousMillis = 0;

  public:
    TrafficLight(int d1_r, int d1_y, int d1_g, int d2_r, int d2_y, int d2_g) {
      d1Red = d1_r;
      d1Yellow = d1_y;
      d1Green = d1_g;

      d2Red = d2_r;
      d2Yellow = d2_y;
      d2Green = d2_g;
    }

    void setup() {
      pinMode(d1Red, OUTPUT);
      pinMode(d1Yellow, OUTPUT);
      pinMode(d1Green, OUTPUT);

      pinMode(d2Red, OUTPUT);
      pinMode(d2Yellow, OUTPUT);
      pinMode(d2Green, OUTPUT);

      digitalWrite(d1Red, HIGH);
      digitalWrite(d1Yellow, LOW);
      digitalWrite(d1Green, LOW);

      digitalWrite(d2Red, HIGH);
      digitalWrite(d2Yellow, LOW);
      digitalWrite(d2Green, LOW);
    }

    void update() {
      unsigned long currentMillis = millis();

      switch (currentD1D2State) {
        case D1_D2_RED:
          if (currentMillis - previousMillis >= redDuration) {
            previousMillis = currentMillis;
            currentD1D2State = D1_D2_YELLOW_GREEN;
            digitalWrite(d1Yellow, HIGH);
            digitalWrite(d2Yellow, HIGH);
          }
          break;

        case D1_D2_YELLOW_GREEN:
          if (currentMillis - previousMillis >= redYellowOverlap) {
            digitalWrite(d1Red, LOW);
            digitalWrite(d2Red, LOW);
          }

          if (currentMillis - previousMillis >= yellowGreenDuration) {
            previousMillis = currentMillis;
            currentD1D2State = D1_D2_GREEN;

            digitalWrite(d1Yellow, LOW);
            digitalWrite(d1Green, HIGH);

            digitalWrite(d2Yellow, LOW);
            digitalWrite(d2Green, HIGH);
          }
          break;

        case D1_D2_GREEN:
          if (currentMillis - previousMillis >= greenDuration) {
            previousMillis = currentMillis;
            currentD1D2State = D1_D2_YELLOW_RED;

            digitalWrite(d1Green, LOW);
            digitalWrite(d1Yellow, HIGH);

            digitalWrite(d2Green, LOW);
            digitalWrite(d2Yellow, HIGH);
          }
          break;

        case D1_D2_YELLOW_RED:
          if (currentMillis - previousMillis >= yellowRedDuration) {
            previousMillis = currentMillis;
            currentD1D2State = D1_D2_RED;

            digitalWrite(d1Yellow, LOW);
            digitalWrite(d1Red, HIGH);

            digitalWrite(d2Yellow, LOW);
            digitalWrite(d2Red, HIGH);
          }
          break;
      }
    }
};

TrafficLight trafficLight(2, 3, 4, 5, 6, 7);

void setup() {
  trafficLight.setup();
}

void loop() {
  trafficLight.update();
}
