#include <Servo.h>

// Initialize servo objects
Servo myservo1;
Servo myservo2;
Servo myservo3;

float pos = 0.0;    // Variable to store the servo position

// States for sensors - 1 means light is detected
int sensorState1;
int sensorState2;
int sensorState3;

// Values read by each light sensor
int lightValue1;
int lightValue2;
int lightValue3;

// Baseline ambient light value for sensors
int lightBaseline1 = 0;
int lightBaseline2 = 0;
int lightBaseline3 = 0;

int threshold = 20;

void setup() {
  Serial.begin(9600);

  myservo1.attach(9);  // Attaches the servo on pin 9 to the servo object
  myservo2.attach(10);  // Attaches the servo on pin 10 to the servo object
  myservo3.attach(11);  // Attaches the servo on pin 11 to the servo object

  sensorState1 = 0;
  sensorState2 = 0;
  sensorState3 = 0;

  calibrateLightSensors();  
}

void loop() {
  checkSensorStates();
  
  Serial.print("sensorState1: ");
  Serial.print(sensorState1);
  Serial.print(", ");
  Serial.print(lightValue1);
  Serial.print(" sensorState2: ");
  Serial.print(sensorState2);
  Serial.print(", ");
  Serial.print(lightValue2);
  Serial.print(" sensorState3: ");
  Serial.print(sensorState3);
  Serial.print(", ");
  Serial.println(lightValue3);
  
  for (pos = 50; pos < 180; pos = pos + 0.005) {
    // Go from 0 degrees to 180 only if sensorState = 1
    if (sensorState1 == 1) {
      myservo1.write(pos);
    }
    if (sensorState2 == 1) {
      myservo2.write(pos);
    }
    if (sensorState3 == 1) {
      myservo3.write(pos);
    }
  }
  
  for (pos = 180; pos > 50; pos = pos - 0.005) {
    // Go from 180 degrees to 0 degrees only if sensorState = 1
    if (sensorState1 == 1) {
      myservo1.write(pos);
    }
    if (sensorState2 == 1) {
      myservo2.write(pos);
    }
    if (sensorState3 == 1) {
      myservo3.write(pos);
    }
  }
}

void checkSensorStates() {
  lightValue1 = analogRead(A0);
  lightValue2 = analogRead(A1);
  lightValue3 = analogRead(A2);

  // Check whether current light values are greater than ambient light
  if (lightValue1 > (lightBaseline1 + threshold)) {
    sensorState1 = 1;
  } else {
    sensorState1 = 0;
  }

  if (lightValue2 > (lightBaseline2 + threshold)) {
    sensorState2 = 1;
  } else {
    sensorState2 = 0;
  }

  if (lightValue3 > (lightBaseline3 + threshold)) {
    sensorState3 = 1;
  } else {
    sensorState3 = 0;
  }
}

void calibrateLightSensors() {
  Serial.println("Calibrating sensors...");

  // Turn onboard LED on for calibration indicator
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Calibrate for 5 seconds (scale high/low values to environment to use max range of values)
  while (millis() < 5000) {
     lightBaseline1 = analogRead(A0);
     lightBaseline2 = analogRead(A1);
     lightBaseline3 = analogRead(A2);
  }
  Serial.print("Baseline 1: ");
  Serial.print(lightBaseline1);

  Serial.print(" Baseline 2: ");
  Serial.print(lightBaseline2);
  
  Serial.print(" Baseline 3: ");
  Serial.println(lightBaseline3);
  
  digitalWrite(13, LOW); // Finished calibrating
}
