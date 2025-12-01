#include <Servo.h>

Servo azimuthServo;
Servo elevationServo;

const int AZIMUTH_SERVO_PIN = 9;
const int ELEVATION_SERVO_PIN = 8;

int azimuthPos = 90;
int elevationPos = 90;

enum Mode { AUTO, MANUAL };
Mode currentMode = AUTO;

unsigned long lastUpdate = 0;
const int UPDATE_INTERVAL = 1000;

void setup() {
  Serial.begin(9600);
  
  azimuthServo.attach(AZIMUTH_SERVO_PIN);
  elevationServo.attach(ELEVATION_SERVO_PIN);
  
  azimuthServo.write(azimuthPos);
  elevationServo.write(elevationPos);
  
  Serial.println("Solar Tracker Initialized");
  Serial.println("Ready for commands");
  sendPosition();
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    processCommand(command);
  }
  
  if (currentMode == AUTO) {
    unsigned long currentTime = millis();
    if (currentTime - lastUpdate >= UPDATE_INTERVAL) {
      lastUpdate = currentTime;
      autoTrack();
    }
  }
}

void processCommand(String command) {
  command.toUpperCase();
  
  if (command.startsWith("SET ")) {
    int spaceIndex = command.indexOf(' ', 4);
    if (spaceIndex > 0) {
      int az = command.substring(4, spaceIndex).toInt();
      int el = command.substring(spaceIndex + 1).toInt();
      
      if (az >= 0 && az <= 180 && el >= 0 && el <= 180) {
        azimuthPos = az;
        elevationPos = el;
        updateServos();
        Serial.println("Position updated");
      } else {
        Serial.println("Error: Values must be 0-180");
      }
    }
  }
  else if (command == "MODE AUTO") {
    currentMode = AUTO;
    Serial.println("Mode: Auto Tracking");
  }
  else if (command == "MODE MANUAL") {
    currentMode = MANUAL;
    Serial.println("Mode: Manual Control");
  }
  else if (command == "RESET") {
    azimuthPos = 90;
    elevationPos = 90;
    updateServos();
    Serial.println("Reset to center position");
  }
  else if (command == "CALIBRATE") {
    calibrate();
  }
  else if (command == "STATUS") {
    sendPosition();
  }
  else {
    Serial.println("Unknown command");
  }
}

void updateServos() {
  azimuthServo.write(azimuthPos);
  elevationServo.write(elevationPos);
  sendPosition();
}

void sendPosition() {
  Serial.print("AZ=");
  Serial.print(azimuthPos);
  Serial.print(" EL=");
  Serial.println(elevationPos);
}

void autoTrack() {
  unsigned long seconds = millis() / 1000;
  int cycle = (seconds % 120) * 1.5;
  
  azimuthPos = constrain(cycle, 0, 180);
  
  float t = (seconds % 120) / 120.0;
  elevationPos = constrain(sin(t * PI) * 90, 0, 90);
  
  updateServos();
}

void calibrate() {
  Serial.println("Starting calibration...");
  
  Serial.println("Moving to 0° position");
  azimuthServo.write(0);
  elevationServo.write(0);
  delay(2000);
  sendPosition();
  
  Serial.println("Moving to 180° position");
  azimuthServo.write(180);
  elevationServo.write(180);
  delay(2000);
  sendPosition();
  
  Serial.println("Returning to center");
  azimuthPos = 90;
  elevationPos = 90;
  updateServos();
  
  Serial.println("Calibration complete");
}