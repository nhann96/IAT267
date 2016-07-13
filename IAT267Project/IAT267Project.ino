const int forceBackRight = A0;
const int forceBackLeft = A1;
const int forceFrontRight = A2;
const int forceFrontLeft = A3;
const int lightSensor = A4;
const int tempSensors = A5;

int forceBackRightVal;
int forceBackLeftVal;
int forceFrontRightVal;
int forceFrontLeftVal;
int lightSensorVal;
int tempSensorBackRightVal;
int tempSensorBackLeftVal;
int tempSensorFrontRightVal;
int tempSensorFrontLeftVal;

boolean readyToExercise;
boolean alarmOff;

void setup() {
  // put your setup code here, to run once:
  forceBackRightVal = 0;
  forceBackLeftVal = 0;
  forceFrontRightVal = 0;
  forceFrontLeftVal = 0;
  lightSensorVal = 0;
  tempSensorBackRightVal = 0;
  tempSensorBackLeftVal = 0;
  tempSensorFrontRightVal = 0;
  tempSensorFrontLeftVal = 0;

  readyToExercise = false;
  alarmOff = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
   * Check if correct time and if they do not have their feet on the sensors
   * If those conditions are true alarm will go off
   * boolean for "alarm is off" is true
   */
  
  // Read Values of 2 back sensors
  if (forceBackRightVal > 200 && forceBackLeftVal > 200) {
    /*
     * turn alarm off
     */
     alarmOff = true;
  } else {
    /*
     * Turn alarm back on 
     */
     alarmOff = false;
  }
   
  /*
   * If the "alarm is off" boolean is true
   * Check if the light is bright enough
   * If not then prompt to brighten the lights
   * If it is then change condition of the alarm to go off to having no contact with force mats !(BR || BL || FR || FL)
   * Allow for user to begin exercising (boolean true)
   */
   if (alarmOff) {
     lightSensorVal = analogRead(lightSensor);
     if (lightSensorVal < 200) {
        readyToExercise = false;
        /*
         * Prompt to brighten the lights
         */
     } else {
        readyToExercise = true;
     }
   }
}
   
  /*
   * Check for boolean to be true to be ready for exercising
   * Give prompt to exercise
   */

   /*
    * 
    */
}
