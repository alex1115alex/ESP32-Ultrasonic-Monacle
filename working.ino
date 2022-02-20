#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library

//////////////////////////
// MicroOLED Definition //
//////////////////////////
#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17

const int pingPin = 12; // TRIG Pin of Ultrasonic Sensor
const int echoPin = 14; // ECHO Pin of Ultrasonic Sensor

const int piezoPin = 13;

int sensorReading = 0;      // variable to store the value read from the sensor pin

MicroOLED oled(OLED_RESET, OLED_DC, OLED_CS);

void setup()
{
  delay(100);
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.clear(PAGE); // Clear the buffer.
  randomSeed(analogRead(A0));
  writeSplashScreen();
}

void loop()
{
  long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);

  if (inches <= 150)
  {
    printTitle(String(inches) + "in", 1);
  }
  else
  {
    printTitle("Error", 0);
  }

  delay(50);
}

// Center and print a small title... Only works for titles one line long.
void printTitle(String title, int font)
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;

  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length() / 2)),
                 middleY - (oled.getFontHeight() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
  delay(1500);
  oled.clear(PAGE);
}

// Print some text with a nice outline around the screen
void writeSexyText(String text){
  oled.clear(PAGE);
  oled.rect(0,0,64,48);
  oled.setCursor(2,2);
  oled.printf(text.c_str()); //why the hell do c-like languages still exist
  oled.display();
}

void writeSplashScreen(){
  const char *lines[] = {
    "AlexOS"
  };
  
  oled.clear(PAGE);
  oled.rect(0,0,64,48);
  oled.setCursor(2,2);

  for(int i = 0; i < sizeof(lines); i++)
  {
    oled.println(lines[i]);
    oled.display();
    delay(900);
  }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}