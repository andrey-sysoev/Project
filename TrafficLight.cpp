#define RED 100
#define YELLOW 200
#define GREEN 300

class TrafficLight {
  private:
    int led_red;
    int led_yellow;
    int led_green;
    int currentState=RED;
    
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

    void switchLights() {
      switch (currentState) {
        case RED:
          digitalWrite(led_red, HIGH);
          digitalWrite(led_yellow, LOW);
          digitalWrite(led_green, LOW);
          delay(20000);  
          currentState = YELLOW;  
          break;
          
        case YELLOW:
          digitalWrite(led_red, LOW);
          digitalWrite(led_yellow, HIGH);
          digitalWrite(led_green, LOW);
          delay(5000); 
          currentState = GREEN; 
          break;
          
        case GREEN:
          digitalWrite(led_red, LOW);
          digitalWrite(led_yellow, LOW);
          digitalWrite(led_green, HIGH);
          delay(20000);  
          currentState = RED;  
          break;
      }
    }
};
class PedestrianLight {
  private:
    int led_ped_red;
    int led_ped_green;
    int pedestrianButton;
    int switchState = 0;  

  public:
    PedestrianLight(int red_ped, int green_ped, int button) {
      led_ped_red = red_ped;
      led_ped_green = green_ped;
      pedestrianButton = button;
    }

    
    void setup() {
      pinMode(led_ped_red, OUTPUT);    
      pinMode(led_ped_green, OUTPUT);  
      pinMode(pedestrianButton, INPUT_PULLUP);    
    }

    
    void manage() {
      switchState = digitalRead(pedestrianButton);  

      if (switchState == LOW) {  
        digitalWrite(led_ped_red, LOW);    
        digitalWrite(led_ped_green, HIGH);
        delay (5000);
      } else {  
        digitalWrite(led_ped_red, HIGH);   
        digitalWrite(led_ped_green, LOW);
      }
    }
};


PedestrianLight pedestrianLight(5, 6, 7);  
TrafficLight trafficLight(2, 3, 4);

void setup() {
  trafficLight.setup();
  pedestrianLight.setup();
}

void loop() {
  trafficLight.switchLights();
   pedestrianLight.manage();
}
