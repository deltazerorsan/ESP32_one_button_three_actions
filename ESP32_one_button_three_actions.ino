/* https://github.com/deltazerorsan

 * Only RTC IO can be used as a source for external wake source.
 *  
 * They are pins: 0,2,4,12-15,25-27,32-39.
 * BUT DO NOT USE 0, cause Double is fooled (GPIO 0 is used to put ESP32 in upload mode)


 *    +3.3v ---- PULLUP RESISTOR --|
 * GPIO_PIN -----------------------|-- BUTTON
 *      GND -------------------------- BUTTON                
 *      
 * If you want to avoid after reset serial information, connect GPIO 15 to GND
*/

#define BUTTON_PIN GPIO_NUM_12

void setup(){
  Serial.begin(115200);                           // Only to show testing result
  pinMode(BUTTON_PIN, INPUT);                     // Used to test button status post wake up
  String result;                                  // Only to show testing result
  
  esp_sleep_wakeup_cause_t wakeup_reason;         // We want to know if it is the first power on
  wakeup_reason = esp_sleep_get_wakeup_cause();   //
  esp_sleep_enable_ext0_wakeup(BUTTON_PIN,0);     // Prepare for wakeup, 0 = going to Low
  
  if (wakeup_reason == 0) esp_deep_sleep_start(); // If normal reset or first power on, go to sleep
  
  Serial.print("> ");                             // Only to show testing result
  
  long int long_ms = millis() + 1500;             // Duration in ms of the Long click
  long int double_ms = long_ms - 1000;            // Duration in ms of the Double click
  
  // Those are the lines where the analysis of the button behavior occurs
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  while ((digitalRead(BUTTON_PIN) == 0) and (millis() < long_ms));
  
  if (millis() < long_ms) {
    result = "Click";
    while (millis() < double_ms) {
      if (digitalRead(BUTTON_PIN) == 0) result = "Double";
    }
  } 
  else result = "Long";
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ End

  Serial.println(result);                         // Only to show testing result
  
  while (digitalRead(BUTTON_PIN) == 0);           // Wait until the button is released
  delay(200);                                     // Avoid spurious clicks
  esp_deep_sleep_start();                         // Ready for next cycle
}

void loop(){
}
