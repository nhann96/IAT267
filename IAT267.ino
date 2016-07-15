const int forceBackRight = A0;
const int forceBackLeft = A1;
const int forceFrontRight = A2;
const int forceFrontLeft = A3;
const int lightSensor = A4;
const int tempSensors = A5;

const int forceBackRightVal = 0;
const int forceBackLeftVal = 0;
const int forceFrontRightVal = 0;
const int forceFrontLeftVal = 0;
const int lightSensorVal = 0;
const int tempSensorBackRightVal = 0;
const int tempSensorBackLeftVal = 0;
const int tempSensorFrontRightVal = 0;
const int tempSensorFrontLeftVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print("bleft");
//  Serial.print(analogRead(forceBackLeft));
//  Serial.println("bleft");
// 
//  Serial.print("bright");
//  Serial.print(analogRead(forceBackRight));
//  Serial.println("bright");
//  
//  Serial.print("fleft");
//  Serial.print(analogRead(forceFrontLeft));
//  Serial.println("fleft");
  
//  Serial.print("fright");
//  Serial.print(analogRead(forceFrontRight));
//  Serial.println("fright");
  /*
   * Check if correct time and if they do not have their feet on the sensors
   * If those conditions are true alarm will go off
   * boolean for turning off alarm is true
   */
   
  /*
   * If the alarm boolean is true
   * Check if the light is bright enough
   * If not then prompt to brighten the lights
   * If it is then change condition of the alarm to go off to having no contact with force mats !(BR || BL || FR || FL)
   * Allow for user to begin exercising (boolean true)
   */
   
  /*
   * Check for boolean to be true to be ready for exercising
   * Give prompt to exercise
   */

   /*
    * 
    */
}
