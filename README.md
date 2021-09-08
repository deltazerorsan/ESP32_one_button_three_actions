# ESP32_one_button_three_actions
Using only one button you can achieve three actions: Click, Double Click and Long Click

The goal is to send some kind of mqtt or ESPNow message to a system. In this case you can send three diffrent messages using only one button and only one GPIO.
The ESP32 goes to sleep on power on or reset and waits for the action over the button. In this example only prints the result to Serial and goes to sleep again.
