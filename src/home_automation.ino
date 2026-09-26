#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- PIN DEFINITIONS ----------

#define FLAME_PIN 4
#define WATER_PIN 5

#define RED_PIN 6
#define GREEN_PIN 7
#define YELLOW_PIN 15

#define RELAY1_PIN 10
#define RELAY2_PIN 11
#define RELAY3_PIN 12
#define RELAY4_PIN 13

#define OLED_SDA 8
#define OLED_SCL 9

// ---------- OLED ----------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// ---------- SETUP ----------

void setup() {

  Serial.begin(115200);

  // Sensors
  pinMode(FLAME_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);

  // Traffic light
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);

  // Relays
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);

  // Turn everything OFF initially
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);

  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  digitalWrite(RELAY3_PIN, LOW);
  digitalWrite(RELAY4_PIN, LOW);

  // OLED
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
  }
  else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("HOME AUTOMATION");
    display.println();
    display.println("System Starting...");
    display.display();
  }

  delay(2000);
}

// ---------- LOOP ----------

void loop() {

  int flame = digitalRead(FLAME_PIN);
  int water = digitalRead(WATER_PIN);

  Serial.print("Flame: ");
  Serial.print(flame);

  Serial.print(" | Water: ");
  Serial.println(water);

  // --------------------------------
  // FLAME DETECTED
  // --------------------------------

  if (flame == LOW) {

    Serial.println("🔥 FLAME DETECTED!");

    // Red ON
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);

    // Activate relay K1
    // Motor/fan turns ON through K1
    digitalWrite(RELAY1_PIN, HIGH);

    // OLED
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("WARNING!");
    display.println();
    display.println("FLAME DETECTED");
    display.println();
    display.println("FAN: ON");

    display.display();
  }

  // --------------------------------
  // WATER DETECTED
  // --------------------------------

  else if (water == HIGH) {

    Serial.println("💧 WATER DETECTED!");

    // Yellow ON
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);

    // Turn relay ON
    digitalWrite(RELAY1_PIN, HIGH);

    // OLED
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("WARNING!");
    display.println();
    display.println("WATER DETECTED");
    display.println();
    display.println("SYSTEM ACTIVE");

    display.display();
  }

  // --------------------------------
  // NORMAL CONDITION
  // --------------------------------

  else {

    Serial.println("System Normal");

    // Green ON
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);

    // Motor/fan OFF
    digitalWrite(RELAY1_PIN, LOW);

    // OLED
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("SWEETIE AUTOMATION..");
    display.println();
    display.println("System Normal");
    display.println();
    display.println("Fan: OFF");

    display.display();
  }

  delay(500);
}