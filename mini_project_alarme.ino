#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#define PIEZO_PIN 9 // Pin connected to the piezo sensor
Adafruit_SSD1306 display(OLED_RESET);

const signed int buttonPin = 2;   // Pin connected to the button
const signed int sensorPin = 3;   // Pin connected to the door sensor
const signed int hz = 2500;

signed int buttonState = 0;       // Current state of the button
signed int lastButtonState = 0;   // Previous state of the button
signed bool toggleVariable = 0;    // Variable to toggle the alarm (on or off)
signed int sensorState = 0; 

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(sensorPin, INPUT_PULLUP); // Use internal pull-up resistor
  display.display(); // show splashscreen
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
}

void display_print(String mensagem) {
    display.clearDisplay();
    display.setTextSize(2);                // Text size (1 = smallest)
    display.setTextColor(SSD1306_WHITE);  // Text color
    display.setCursor(0, 0);              // Top-left corner
    display.println(mensagem);   // Display text
    display.display();
}

void loop() {
  sensorState = digitalRead(sensorPin);
  // Read the current state of the button
  buttonState = digitalRead(buttonPin);

  // Check if the button state has changed from HIGH to LOW (button press)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Toggle the variable
    toggleVariable = !toggleVariable; // Toggle between 0 and 1
  }

  // Update the last button state
  lastButtonState = buttonState;

  if(toggleVariable){
      
      if (sensorState == HIGH) {
          tone(PIEZO_PIN, hz);
          delay(100);
          noTone(PIEZO_PIN);
          display_print("O INTRUSO\nLigue 112");
      } else {
          display_print("ALARME\nLIGADO!");
          noTone(PIEZO_PIN);
      }
      
  } else {
      display_print("ALARME\nDESLIGADO!");
  }

  delay(50);
}
