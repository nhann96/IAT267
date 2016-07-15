#include <LiquidCrystal.h>

const unsigned long milliSecondsInAnHour = 3600000;
const unsigned long milliSecondsInAMinute = 60000;

const int hourButton = 7;
const int minuteButton = 8;
const int forceBackRight = A0;
const int forceBackLeft = A1;
const int forceFrontRight = A2;
const int forceFrontLeft = A3;
const int lightSensor = A4;
const int timeAdjustmentSlider = A5;

int forceBackRightVal;
int forceBackLeftVal;
int forceFrontRightVal;
int forceFrontLeftVal;
int lightSensorVal;
int timeAdjustmentSliderVal;
int tempSensorBackRightVal;
int tempSensorBackLeftVal;
int tempSensorFrontRightVal;
int tempSensorFrontLeftVal;

boolean readyToExercise;

//Clock
unsigned long timeInMilliSeconds;
unsigned long alarmInMilliSeconds;
unsigned long lastUpdateInMilliSeconds;
boolean alarmOn;
int minuteButtonVal;
int hourButtonVal;

int speakerPin = 6;

LiquidCrystal lcd(1, 0, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  // put your setup code here, to run once:
  forceBackRightVal = 0;
  forceBackLeftVal = 0;
  forceFrontRightVal = 0;
  forceFrontLeftVal = 0;
  lightSensorVal = 0;
  timeAdjustmentSliderVal = 0;
  tempSensorBackRightVal = 0;
  tempSensorBackLeftVal = 0;
  tempSensorFrontRightVal = 0;
  tempSensorFrontLeftVal = 0;

  readyToExercise = false;
  alarmOn = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
     Shows time and the ability to change the time and alarm

  */
  timeAdjustmentSliderVal = analogRead(timeAdjustmentSlider);
  Serial.println(timeAdjustmentSliderVal);
  updateTime();
  String currentTime = getTime();
  String alarmTime = getAlarm();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentTime);

  /*
     Gives time a range of 1 sec to check the if the alarm will go off
  */
  if (!alarmOn && (timeInMilliSeconds >= alarmInMilliSeconds - 500) && (timeInMilliSeconds <= alarmInMilliSeconds + 500)) {
    alarmOn = true;
  }
  /*
     When the alarm goes off  make appropriate noises
  */
  if (alarmOn) {
    Serial.println("BEEEEEP BEEEEEP");
    for (int i = 0; i < 3; i++) {
      tone(speakerPin, 2093, 100);
      delay(150);
    }
  }

  /*
     Uses the slider with 2 buttons to be able to adjust the current time and the alarm time
  */
  if (timeAdjustmentSliderVal >= 950) {
    minuteButtonVal = digitalRead(minuteButton);
    if (minuteButtonVal == HIGH) {
      setTime(getCurrentHour(), getCurrentMinute() + 1);
    }
    hourButtonVal = digitalRead(hourButton);
    if (hourButtonVal == HIGH) {
      setTime(getCurrentHour() + 1, getCurrentMinute());
    }
    lcd.setCursor(0, 0);
    lcd.print(currentTime);
  }

  if (timeAdjustmentSliderVal >= 425 && timeAdjustmentSliderVal <= 625) {
    minuteButtonVal = digitalRead(minuteButton);
    if (minuteButtonVal == HIGH) {
      setAlarm(getAlarmHour(), getAlarmMinute() + 1);
    }
    hourButtonVal = digitalRead(hourButton);
    if (hourButtonVal == HIGH) {
      setAlarm(getAlarmHour() + 1, getAlarmMinute());
    }
    lcd.setCursor(0, 0);
    lcd.print(alarmTime);
  }
  delay(500);
  /*
     Check if correct time and if they do not have their feet on the sensors
     If those conditions are true alarm will go off
     boolean for "alarm is off" is true
  */

  // Read Values of 2 back sensors
  if (alarmOn && forceBackRightVal > 200 && forceBackLeftVal > 200) {
    /*
       turn alarm off
    */
    readyToExercise = true;
  } else {
    /*
       Turn alarm back on
    */
    readyToExercise = false;
  }

  /*
     If the "alarm is off" boolean is true
     Check if the light is bright enough
     If not then prompt to brighten the lights
     If it is then change condition of the alarm to go off to having no contact with force mats !(BR || BL || FR || FL)
     Allow for user to begin exercising (boolean true)
  */
  if (alarmOn) {
    lightSensorVal = analogRead(lightSensor);
    if (lightSensorVal < 200) {
      readyToExercise = false;
      /*
         Prompt to brighten the lights
      */
    } else {
      readyToExercise = true;
    }
  }
}

/*
   Check for boolean to be true to be ready for exercising
   Give prompt to exercise
*/

/*

*/

unsigned long getCurrentHour() {
  unsigned long hour = timeInMilliSeconds / milliSecondsInAnHour;
  return hour;
}

unsigned long getCurrentMinute() {
  unsigned long leftoverMinutes = timeInMilliSeconds % milliSecondsInAnHour;
  unsigned long minutes = leftoverMinutes / milliSecondsInAMinute;
  return minutes;
}

unsigned long getAlarmHour() {
  unsigned long hour = alarmInMilliSeconds / milliSecondsInAnHour;
  return hour;
}

unsigned long getAlarmMinute() {
  unsigned long leftoverMinutes = alarmInMilliSeconds % milliSecondsInAnHour;
  unsigned long minutes = leftoverMinutes / milliSecondsInAMinute;
  return minutes;
}

String getAlarm() {
  String alarm = "";
  unsigned long hours = alarmInMilliSeconds / milliSecondsInAnHour;
  alarm += hours;
  unsigned long leftoverMinutes = alarmInMilliSeconds % milliSecondsInAnHour;
  unsigned long minutes = leftoverMinutes / milliSecondsInAMinute;
  if (minutes < 10) {
    alarm += ":0";
  } else {
    alarm += ":";
  }
  alarm += minutes;
  unsigned long seconds = (alarmInMilliSeconds - (hours * milliSecondsInAnHour + minutes * milliSecondsInAMinute)) / 1000 ;
  if (seconds < 10) {
    alarm += ":0";
  } else {
    alarm += ":";
  }
  alarm += seconds;
  return alarm;
}

String getTime() {
  String curTime = "";
  unsigned long hours = timeInMilliSeconds / milliSecondsInAnHour;
  curTime += hours;
  unsigned long leftoverMinutes = timeInMilliSeconds % milliSecondsInAnHour;
  unsigned long minutes = leftoverMinutes / milliSecondsInAMinute;
  if (minutes < 10) {
    curTime += ":0";
  } else {
    curTime += ":";
  }
  curTime += minutes;
  unsigned long seconds = (timeInMilliSeconds - (hours * milliSecondsInAnHour + minutes * milliSecondsInAMinute)) / 1000 ;
  if (seconds < 10) {
    curTime += ":0";
  } else {
    curTime += ":";
  }
  curTime += seconds;
  return curTime;
}

void setTime(unsigned long hour, unsigned long minutes) {
  timeInMilliSeconds = (hour * milliSecondsInAnHour) + (minutes * milliSecondsInAMinute);
}

void setAlarm(unsigned long hour, unsigned long minutes) {
  alarmInMilliSeconds = (hour * milliSecondsInAnHour) + (minutes * milliSecondsInAMinute);
}

void updateTime() {
  unsigned long addedTime = millis();
  unsigned long addedMilliSeconds = addedTime - lastUpdateInMilliSeconds;
  lastUpdateInMilliSeconds = addedTime;
  timeInMilliSeconds += addedMilliSeconds;
  unsigned long hours = timeInMilliSeconds / milliSecondsInAnHour;
  if (hours == 24) {
    unsigned long daySubtraction = hours * milliSecondsInAnHour;
    timeInMilliSeconds = timeInMilliSeconds - daySubtraction;
    hours -= 24;
  }
}

