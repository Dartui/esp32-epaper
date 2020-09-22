#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.h>
#include <GxIO/GxIO.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>

#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60       /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootTime = -1;

GxIO_Class io(SPI, SS, 22, 21);
GxEPD_Class display(io, 16, 4);


void setup(){
  init();

  bootTime++;

  draw();

  deep_sleep();
}

void init() {
  Serial.begin(115200);
  display.init(115200);

  delay(100);

  Serial.println("Initialize.");
}

void draw() {
  char timer[9];
  unsigned int days = bootTime / (60 * 24);
  unsigned int hours = (bootTime / 60) % 24;
  unsigned int minutes = bootTime % 60;

  sprintf(timer, "%dd %02d:%02d", days, hours, minutes);

  Serial.println(timer);
  
  const GFXfont* f = &FreeSansBold24pt7b;
  
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  
  display.setCursor(0, 0);
  
  display.println();
  display.println(timer);
  display.update();
}

void deep_sleep() {
  Serial.println("Deep sleep...");

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop(){
  //This is not going to be called
}
