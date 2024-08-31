#include <ButtonDebounce.h>

#define GPIO_PIN (10)

ButtonDebounce button(GPIO_PIN, 250 /* milli Seconds */);

void setup() {
  Serial.begin(115200);
}

void loop() {
  static bool last = button.state();

  if(button.state() != last) {
    last = button.state();
    Serial.println(last ? "HIGH" : "LOW");
  }
  delay(500);
}
