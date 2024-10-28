#include <Arduino.h>

// Store joint values as integers
int shoulder_joint = 0;
int upper_arm_joint = 0;
int elbow_joint = 0;
int wrist_joint = 0;

void setup() {
  Serial.begin(115200);  // Communication with ROS 2 node
  Serial.println("ESP32 ready to receive joint data.");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming data
    String data = Serial.readStringUntil('\n');  // Read until newline
    parseJointData(data);
    printJointValues();
  }
}

void parseJointData(String data) {
  // Separate individual joint data
  int start = 0;
  while (start < data.length()) {
    int end = data.indexOf(';', start);
    if (end == -1) end = data.length();
    String jointData = data.substring(start, end);

    // Extract joint name and value
    int separator = jointData.indexOf(':');
    if (separator > 0) {
      String jointName = jointData.substring(0, separator);
      int jointValue = round(jointData.substring(separator + 1).toFloat());

      // Store values in appropriate variables
      if (jointName == "shoulder_joint") {
        shoulder_joint = jointValue;
      } else if (jointName == "upper_arm_joint") {
        upper_arm_joint = jointValue;
      } else if (jointName == "elbow_joint") {
        elbow_joint = jointValue;
      } else if (jointName == "wrist_joint") {
        wrist_joint = jointValue;
      }
    }

    start = end + 1;
  }
}

void printJointValues() {
  Serial.println();
  Serial.print("  Shoulder: "); Serial.println(shoulder_joint);
  Serial.print("  Upper Arm: "); Serial.println(upper_arm_joint);
  Serial.print("  Elbow: "); Serial.println(elbow_joint);
  Serial.print("  Wrist: "); Serial.println(wrist_joint);
}
