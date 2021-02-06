#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>

// hardware type, search for google :)
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
// count led matrix you have
// ex: like 32x8 panels, just divide 32/8, it will return 4
#define MAX_DEVICES 8
// don't use D3 ! it make you can't write program to the esp
// Pin D8 = GPIO 15
#define CS_PIN 15

// indonesia
char daysOfTheWeek[7][7] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
// english
// char dayOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// for reference when show date and time
long clkTime = 0;

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
RTC_DS3231 rtc;

void setup()
{
  Serial.begin(115200);

  delay(3000);
  if (!rtc.begin())
  {
    Serial.println("RTC tidak terbaca");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    // adjust time if lost power
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // manual adjustment using this
    // January 21, 2019 jam 10:30:00
    // rtc.adjust(DateTime(2019, 1, 25, 10, 30, 0));
  }

  // begin display
  myDisplay.begin();
  // set brightness
  myDisplay.setIntensity(0);
  // clear display first
  myDisplay.displayClear();

  myDisplay.setTextAlignment(PA_CENTER);
  char opening[16] = "Hello World!";
  myDisplay.print(opening);

  delay(2000);
}

String print_time(DateTime timestamp)
{
  char message[8];
  int Hour = timestamp.hour();
  int Minute = timestamp.minute();
  int Second = timestamp.second();

  sprintf(message, "%02d : %02d : %02d", Hour, Minute, Second);

  return message;
}

void loop()
{
  DateTime now = rtc.now();
  // show  time
  myDisplay.print(print_time(now));

  // display date every 20 seconds
  if (millis() - clkTime > 20000)
  {
    char date[12];

    sprintf(date, "%s", daysOfTheWeek[now.dayOfTheWeek()]);
    myDisplay.print(date);
    delay(1500);

    sprintf(date, "%d-%d-%d", now.day(), now.month(), now.year());
    myDisplay.print(date);
    delay(2500);

    clkTime = millis();
  }

  delay(1000);
}
