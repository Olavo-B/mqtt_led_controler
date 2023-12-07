# MQTT LED CONTROLLER

This code demonstrates how to use MQTT and ESP32 to control an LED, turning it on and off.

## Prerequisites:
- ESP32 boar
- MQTT broker (e.g., Mosquitto) running on a server

## Usage:
1. Connect the ESP32 board to the LED.
2. Update the `ssid`, `password`, `mqtt_broker`, `mqtt_port`, `mqtt_topic`, and `led_pin` variables with your own values.
3. Flash the code to the ESP32 board.
4. The ESP32 will connect to the MQTT broker and subscribe to the specified topic.
5. When a message is received on the topic, the ESP32 will toggle the LED accordingly.

## Note: 

Make sure to install the necessary libraries (e.g., umqtt.simple) before running the code.


