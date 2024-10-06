class TrafficLight {
  private:
    int led_red;
    int led_yellow;
    int led_green;
  public:
    TrafficLight(int red, int yel, int gre) {
      led_red = red;
      led_yellow = yel;
      led_green = gre;
    }
    void setup() {
      pinMode(led_red, OUTPUT);
      pinMode(led_yellow, OUTPUT);
      pinMode(led_green, OUTPUT);
     
    }
    void switchingLights() {
      digitalWrite(led_red, HIGH);
      digitalWrite(led_yellow, LOW);
      digitalWrite(led_green, LOW);
      delay(20000);

      digitalWrite(led_red, LOW);
      digitalWrite(led_yellow, HIGH);
      digitalWrite(led_green, LOW);
      delay(5000);  

      digitalWrite(led_red, LOW);
      digitalWrite(led_yellow, LOW);
      digitalWrite(led_green, HIGH);
      delay(20000); 
    }
};
TrafficLight trafficLight(0,1,2);
void setup() {
  trafficLight.setup();
}

void loop() {
  trafficLight.switchingLights();
}
