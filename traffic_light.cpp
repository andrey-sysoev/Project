#define RED 100
#define YELLOW 200
#define GREEN 300
#define YELLOW_RED 400

class TrafficLight {
  private:
    int led_red, led_yellow, led_green, buttonPin;
    const long redDuration = 10000;
    const long yellowDuration = 5000;
    const long greenDuration = 10000;
    
    unsigned long previousMillis = 0;
    bool buttonPressed = false;
    int currentState = RED;
  
  public:
    TrafficLight(int red, int yellow, int green, int button) {
      led_red = red;
      led_yellow = yellow;
      led_green = green;
      buttonPin = button;
    }

    void setup() {
      pinMode(led_red, OUTPUT);
      pinMode(led_yellow, OUTPUT);
      pinMode(led_green, OUTPUT);
      pinMode(buttonPin, INPUT_PULLUP);
      digitalWrite(led_red, HIGH);
      digitalWrite(led_yellow, LOW);
      digitalWrite(led_green, LOW);
    }

    void checkButtonPress() {
      if (digitalRead(buttonPin) == LOW) {
        buttonPressed = true;
      }
    }

    void update() {
      unsigned long currentMillis = millis();

      switch (currentState) {
        case RED:
          if (buttonPressed) {
            Serial.write(100); 
            buttonPressed = false;
          }
         digitalWrite(led_yellow, LOW);
         digitalWrite(led_red, HIGH);
          
        if (currentMillis - previousMillis >= redDuration) {
            previousMillis = currentMillis;
            currentState = YELLOW;
            
          }
          break;

        case YELLOW:
        digitalWrite(led_yellow, HIGH);
        Serial.write(200);
        delay(2000);
        digitalWrite(led_red, LOW);
        
          if (currentMillis - previousMillis >= yellowDuration) {
            previousMillis = currentMillis;
            currentState = GREEN;
            
          }
          break;

        case GREEN:
        digitalWrite(led_yellow, LOW);
        digitalWrite(led_green, HIGH);
          
        if (currentMillis - previousMillis >= greenDuration) {
            previousMillis = currentMillis;
            currentState = YELLOW_RED;
            
          }
          break;

        case YELLOW_RED:
        digitalWrite(led_green, LOW);
        digitalWrite(led_yellow, HIGH);
          
        if (currentMillis - previousMillis >= yellowDuration) {
            previousMillis = currentMillis;
            currentState = RED;
          }
          break;
      }
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
