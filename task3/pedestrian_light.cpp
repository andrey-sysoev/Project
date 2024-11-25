#define PED_GREEN 500
#define PED_RED 600
#define RED 100
#define YELLOW 200

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

PedestrianLight pedestrianLight(5, 6);

void setup() {
  Serial.begin(9600);
  pedestrianLight.setup();
}

void loop() {
  pedestrianLight.update();
}
