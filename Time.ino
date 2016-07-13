unsigned long timeInSeconds;

unsigned long hour = 2;
unsigned long minute = 12;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  timeInSeconds = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  setTime(hour, minute);
  //Serial.println(timeInSeconds);
  updateTime();
  delay(2000);
}

void setTime(unsigned long hour, unsigned long minutes) {
  timeInSeconds = (hour * 3600) + (minutes * 60);
}

void updateTime() {
  unsigned long addedTime = millis();
  unsigned long addedSeconds = millis() / 1000;
  timeInSeconds += addedSeconds;
  Serial.print("Time in Seconds: ");
  Serial.println(timeInSeconds);
  unsigned long hours = timeInSeconds / 3600;
  if (hours >= 24) {
    hour -= 24;
    hours -= 24;
    timeInSeconds = timeInSeconds -  (24 * 3600);
  }
  unsigned long leftoverMinutes = timeInSeconds % 3600;
  unsigned long minutes = leftoverMinutes / 60;
  Serial.print(hours);
  if (minutes < 10) {
    Serial.print(":0");
  } else {
    Serial.print(":");
  }
  Serial.print(minutes);
  unsigned long seconds = timeInSeconds - (hours * 3600 + minutes * 60) ;
  if (seconds < 10) {
    Serial.print(":0");
  } else {
    Serial.print(":");
  }
  Serial.println(seconds);
}
