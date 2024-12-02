#include <LiquidCrystal.h>
// lcd pins
const int RS = 7;
const int E = 6;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
// buttons pins
const int set_pin = A5;
const int up_pin = A4;
const int down_pin = A3;
const int left_pin = A7;
const int right_pin = A6;
// buzzer pins
const int buzzer_pin = A2;
// display object
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
// time variables
const int press_time = 1000; // the pressing time required for a button to work in ms
int h, m, s; // store the time values for the clock
int a_h, a_m; // store the time values for the alarm
int present_second, last_second; // used for updating the time each second
// button pressing times - save the time since the buttons were pressed
unsigned long set_press_time, up_press_time, down_press_time, left_press_time, right_press_time;
// button states
bool set_last_state, up_last_state, down_last_state, left_last_state, right_last_state;
bool set_present_state, up_present_state, down_present_state, left_present_state, right_present_state;
// alarm variables
bool alarm_state, alarm_sound_turned_off = true;
unsigned long alarm_start_time;
// position of index
int clock_index;
int alarm_index;

// button functions
bool set_is_pressed()
{
  set_present_state = analogRead(set_pin);
  if(!(set_present_state && set_last_state))
    set_press_time = millis();
  set_last_state = set_present_state;
  if(millis() - set_press_time  > press_time)
  {
    set_press_time = millis();
    return true;
  }
  return false;
}

bool up_is_pressed()
{
  up_present_state = analogRead(up_pin);
  if(!(up_present_state && up_last_state))
    up_press_time = millis();
  up_last_state = up_present_state;
  if(millis() - up_press_time > press_time)
  {
    up_press_time = millis();
    return true;
  }
  return false;
}

bool down_is_pressed()
{
  down_present_state = analogRead(down_pin);
  if(!(down_present_state && down_last_state))
    down_press_time = millis();
  down_last_state = down_present_state;
  if(millis() - down_press_time > press_time)
  {
    down_press_time = millis();
    return true;
  }
  return false;
}

bool left_is_pressed()
{
  left_present_state = analogRead(left_pin);
  if(!(left_present_state && left_last_state))
    left_press_time = millis();
  left_last_state = left_present_state;
  if(millis() - left_press_time > press_time)
  {
    left_press_time = millis();
    return true;
  }
  return false;
}

bool right_is_pressed()
{
  right_present_state = analogRead(right_pin);
  if(!(right_present_state && right_last_state))
    right_press_time = millis();
  right_last_state = right_present_state;
  if(millis() - right_press_time > press_time)
  {
    right_press_time = millis();
    return true;
  }
  return false;
}

// time functions
void updateTimeEachSecond()
{
  present_second = millis() % 10000 / 1000;
  if(present_second != last_second)
  {
    s++;
    if(s > 59)
    {
      s = 0, m++;
      if(m > 59)
      {
        m = 0, h++;
        if(h > 23)
          h = 0;
      }
    }
  }
  last_second = present_second;
}

void incrementClockHour()
{
  h++;
  if(h > 23)
    h = 0;
}

void decrementClockHour()
{
  h--;
  if(h < 0)
    h = 23;
}

void incrementClockMinute()
{
  m++;
  if(m > 59)
    m = 0;
}

void decrementClockMinute()
{
  m--;
  if(m < 0)
    m = 59;
}

void resetSecond()
{
  s = 0;
}

void incrementAlarmHour()
{
  a_h++;
  if(a_h > 23)
    a_h = 0;
}

void decrementAlarmHour()
{
  a_h--;
  if(a_h < 0)
    a_h = 23;
}

void incrementAlarmMinute()
{
  a_m++;
  if(a_m > 59)
    a_m = 0;
}

void decrementAlarmMinute()
{
  a_m--;
  if(a_m < 0)
    a_m = 59;
}

void toggleAlarmState()
{
  alarm_state = !alarm_state;
}

// index functions
void incrementClockIndex()
{
  clock_index++;
  if(clock_index > 1)
    clock_index = 0;
}

void decrementClockIndex()
{
  clock_index--;
  if(clock_index < 0)
    clock_index = 1;
}

void incrementAlarmIndex()
{
  alarm_index++;
  if(alarm_index > 2)
    alarm_index = 0;
}

void decrementAlarmIndex()
{
  alarm_index--;
  if(alarm_index < 0)
    alarm_index = 2;
}

// display functions
void showClock(bool blink_hour, bool blink_minute, bool blink_column)
{
  bool blink = millis() % 10000 / 1000 % 2;
  lcd.setCursor(4, 0);
  String hour = "";
  if(h < 10)
    hour += "0";
  hour += String(h);
  if(blink_hour && blink)
    hour = "  ";
  lcd.print(hour);
  lcd.setCursor(6, 0);
  String column = ":";
  if(blink_column && blink)
    column = " ";
  lcd.print(column);
  lcd.setCursor(7, 0);
  String minute = "";
  if(m < 10)
    minute += "0";
  minute += String(m);
  if(blink_minute && blink)
    minute = "  ";
  lcd.print(minute);
}

void showAlarm(bool blink_hour, bool blink_minute, bool blink_state)
{
  bool blink = millis() % 10000 / 1000 % 2;
  lcd.setCursor(4, 1);
  String hour = "";
  if(a_h < 10)
    hour += "0";
  hour += String(a_h);
  if(blink_hour && blink)
    hour = "  ";
  lcd.print(hour);
  lcd.setCursor(6, 1);
  lcd.print(":");
  lcd.setCursor(7, 1);
  String minute = "";
  if(a_m < 10)
    minute += "0";
  minute += String(a_m);
  if(blink_minute && blink)
    minute = "  ";
  lcd.print(minute);
  lcd.setCursor(13, 1);
  String state = "on ";
  if(alarm_state == false)
    state = "off";
  if(blink_state && blink)
    state = "   ";
  lcd.print(state);
}

// buzzer function
bool alarmTime()
{
  if(h == a_h && m == a_m && s == 0)
  {
    alarm_sound_turned_off = false;
    return true;
  }
  return false;
}

void soundOn()
{
  (s % 2 == 0) ? tone(buzzer_pin, 1000) : noTone(buzzer_pin);
}

void soundOff()
{
  noTone(buzzer_pin);
}

// main functions
void setup()
{
  pinMode(set_pin, INPUT);
  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);
  pinMode(up_pin, INPUT);
  pinMode(down_pin, INPUT);
  lcd.begin(16, 2);
  showAlarm(false, false, false);
}

void loop() 
{
  updateTimeEachSecond();
  showClock(false, false, true);
  // starting the alarm sound if the clock matches the alarm
  if(alarmTime() && alarm_state)
  {
    alarm_start_time = millis();
    while(alarm_sound_turned_off == false)
    {
      updateTimeEachSecond();
      showClock(false, false, true);
      soundOn();
      if(set_is_pressed() || millis() >= alarm_start_time + 60000) // press "Set" or wait 60 seconds
      {
        alarm_sound_turned_off = true;
        soundOff();
      }
    }
  }
  // modifying the values of the clock/alarm
  if(set_is_pressed())
  {
    while(!set_is_pressed()) // set the clock
    {
      updateTimeEachSecond();
      if(left_is_pressed())
        decrementClockIndex();
      if(right_is_pressed())
        incrementClockIndex();
      if(clock_index == 0)
      {
        if(up_is_pressed())
          incrementClockHour();
        if(down_is_pressed())
          decrementClockHour();
        showClock(true, false, false);
      }
      if(clock_index == 1)
      {
        if(up_is_pressed())
        {
          incrementClockMinute();
          resetSecond();
        }
        if(down_is_pressed())
        {
          decrementClockMinute();
          resetSecond();
        }
        showClock(false, true, false);
      }
    }
    while(!set_is_pressed()) // set the alarm
    {
      updateTimeEachSecond();
      showClock(false, false, false);
      if(left_is_pressed())
        decrementAlarmIndex();
      if(right_is_pressed())
        incrementAlarmIndex();
      if(alarm_index == 0)
      {
        if(up_is_pressed())
          incrementAlarmHour();
        if(down_is_pressed())
          decrementAlarmHour();
        showAlarm(true, false, false);
      }
      if(alarm_index == 1)
      {
        if(up_is_pressed())
          incrementAlarmMinute();
        if(down_is_pressed())
          decrementAlarmMinute();
        showAlarm(false, true, false);
      }
      if(alarm_index == 2)
      {
        if(up_is_pressed() || down_is_pressed())
          toggleAlarmState();
        showAlarm(false, false, true);
      }
    }
    clock_index = alarm_index = 0;
    showAlarm(false, false, false);
  }
}