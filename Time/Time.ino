const unsigned long milliSecondsInAnHour = 3600000;
const unsigned long milliSecondsInAMinute = 60000;

const int minuteButton = 8;
const int hourButton = 7;
const int lightSensor = A4;
const int timeAdjustmentSlider = A5;

unsigned long timeInMilliSeconds;
unsigned long alarmInMilliSeconds;
unsigned long lastUpdateInMilliSeconds;
boolean alarmOn;
int minuteButtonVal;
int hourButtonVal;
int lightSensorVal;
int timeAdjustmentSliderVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(hourButton, INPUT);
  pinMode(minuteButton, INPUT);
  lightSensorVal = 0;
  timeAdjustmentSliderVal = 0;
  alarmInMilliSeconds = 0;
  timeInMilliSeconds = 0;
  alarmOn = false;
  lastUpdateInMilliSeconds = millis();
  setTime(0, 0);
  setAlarm(0,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  timeAdjustmentSliderVal = analogRead(timeAdjustmentSlider);
  Serial.println(timeAdjustmentSliderVal);
  updateTime();
  String currentTime = getTime();
  String alarmTime = getAlarm();
  Serial.println(currentTime);
  Serial.println(alarmTime);
  //Gives time a range of 1 sec
  if (!alarmOn && (timeInMilliSeconds >= alarmInMilliSeconds - 500) && (timeInMilliSeconds <= alarmInMilliSeconds + 500)) {
    alarmOn = true;
  }
  if (alarmOn) {
    Serial.println("BEEEEEP BEEEEEP");
  }
  if (timeAdjustmentSliderVal >= 950) {
    minuteButtonVal = digitalRead(minuteButton);
    if (minuteButtonVal == HIGH) {
      setTime(getCurrentHour(), getCurrentMinute() + 1);
    }
    hourButtonVal = digitalRead(hourButton);
    if (hourButtonVal == HIGH) {
      setTime(getCurrentHour() + 1, getCurrentMinute());
    }
    if (alarmOn) {
      lightSensorVal = analogRead(lightSensor);
      if (lightSensorVal < 200) {
        Serial.println("Turn lights on before turning off alarm!");
      } else {
        alarmOn = false;
      }
    }
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
  }
  delay(500);
}

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

void setAlarm(unsigned long hour, unsigned long minutes) {
  alarmInMilliSeconds = (hour * milliSecondsInAnHour) + (minutes * milliSecondsInAMinute);
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

