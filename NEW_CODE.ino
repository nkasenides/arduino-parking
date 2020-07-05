//#include <FirebaseESP8266.h>
//#include <FirebaseESP8266HTTPClient.h>
//#include <FirebaseJson.h>
//#include <jsmn.h>
//#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>


/*
  IR Proximity Sensor interface code
  Turns on an LED on when obstacle is detected, else off.
  blog.circuits4you.com 2016
 */

//#define FIREBASE_HOST "https://parking-e64c7.firebaseio.com/" 
//#define FIREBASE_AUTH "yS5Uk7IYdCQshffdWUbBHb5dzqQj927UWSPwiMEI" 
//#define WIFI_SSID "ComWiz" 
//#define WIFI_PASSWORD "fraoulitsa" 

class Sensor {
  
  protected:
    int pinID;
  
  public:
  Sensor(const int pinID) {
    this->pinID = pinID;
  }

  int getPinID() {
    return pinID;
  }
  
};

class Bulb : public Sensor {
  private:
    String bulbName;
    
  public:
    Bulb(const String bulbName, const int pinID) : Sensor(pinID) {
      pinMode(pinID, OUTPUT);
    }

    void setOn() {
      digitalWrite(pinID, HIGH);
    }

    void setOff() {
      digitalWrite(pinID, LOW);
    }

    void isOn() {
      return digitalRead(pinID) == HIGH;
    }
    
};

class ProximitySensor : public Sensor {

  private:
    String sensorName;
    Bulb* bulb;

  public:
  ProximitySensor(const String sensorName, const int pinID, const Bulb* bulb) : Sensor(pinID) {
    this->sensorName = sensorName;
    this->bulb = bulb;
    pinMode(pinID, INPUT);
  }
  
  bool checkProximity() {
    bool currentRead = digitalRead(pinID) == LOW;
    if (currentRead) {
      bulb->setOn();
    }
    else {
      bulb->setOff();
    }
    
  }
  
};

ProximitySensor* ps1;
ProximitySensor* ps2;
ProximitySensor* ps3;
ProximitySensor* ps4;
ProximitySensor* ps5;
Bulb* bulb1;
Bulb* bulb2;
Bulb* bulb3;
Bulb* bulb4;
Bulb* bulb5;
//Sensor* buzzerSensor;

inline const String boolToString(bool b) {
  return b ? "true" : "false";
}

void setup() {

  Serial.begin(9600);

//  pinMode(8, OUTPUT);

  Serial.print("Initializing bulbs...");
  bulb1 = new Bulb("Bulb1", 9);
  bulb2 = new Bulb("Bulb2", 10);
  bulb3 = new Bulb("Bulb3", 11);
  bulb4 = new Bulb("Bulb4", 12);
  bulb5 = new Bulb("Bulb5", 13); 

  Serial.print("Initializing sensors...");
  ps1 = new ProximitySensor("PS1", 2, bulb1);
  ps2 = new ProximitySensor("PS2", 3, bulb2);
  ps3 = new ProximitySensor("PS3", 4, bulb3);
  ps4 = new ProximitySensor("PS4", 5, bulb4);
  ps5 = new ProximitySensor("PS5", 6, bulb5);

//  buzzerSensor = new Sensor(13);
         
  //Initialize pins:
//  pinMode(buzzerSensor->getPinID(), OUTPUT);

  Serial.println(" [DONE]");
  
}

void loop() {

//  digitalWrite(8, HIGH);

  bool s1 = ps1->checkProximity();
  bool s2 = ps2->checkProximity();
  bool s3 = ps3->checkProximity();
  bool s4 = ps4->checkProximity();
  bool s5 = ps5->checkProximity();
    
  
  Serial.println("[" + boolToString(s1) + "," + boolToString(s2) + "," + boolToString(s3) + "," + boolToString(s4) + "," + boolToString(s5) + "]");

  
}
