#include <Wire.h>
#include "Adafruit_TCS34725.h"

/*
 * TCS34725 configuration
 * Adjust integration time and gain if needed
 */
Adafruit_TCS34725 tcs =
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS,
                    TCS34725_GAIN_4X);

/*
 * Convert RGB to Hue (0–359 degrees)
 */
float rgbToHue(uint16_t r, uint16_t g, uint16_t b)
{
  float rf = (float)r;
  float gf = (float)g;
  float bf = (float)b;

  float maxc = max(rf, max(gf, bf));
  float minc = min(rf, min(gf, bf));
  float delta = maxc - minc;

  // Grayscale (no chroma)
  if (delta == 0.0f) {
    return 0.0f;
  }

  float hue;

  if (maxc == rf) {
    hue = 60.0f * fmodf((gf - bf) / delta, 6.0f);
  }
  else if (maxc == gf) {
    hue = 60.0f * (((bf - rf) / delta) + 2.0f);
  }
  else {
    hue = 60.0f * (((rf - gf) / delta) + 4.0f);
  }

  if (hue < 0.0f) {
    hue += 360.0f;
  }

  return hue;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial); // Needed for some boards

  if (!tcs.begin()) {
    Serial.println("TCS34725 not found. Check wiring.");
    while (1);
  }

  Serial.println("TCS34725 ready");
}

void loop()
{
  uint16_t r, g, b, c;

  // Read raw sensor data
  tcs.getRawData(&r, &g, &b, &c);

  // Optional: normalize RGB using clear channel
  if (c > 0) {
    r = (uint16_t)((float)r / c * 65535.0f);
    g = (uint16_t)((float)g / c * 65535.0f);
    b = (uint16_t)((float)b / c * 65535.0f);
  }

  float hue = rgbToHue(r, g, b);

  // Serial.print("R: "); Serial.print(r);
  // Serial.print("  G: "); Serial.print(g);
  // Serial.print("  B: "); Serial.print(b);
  // Serial.print("  Hue: "); Serial.print(hue);
  // Serial.println(" deg");

  if ((hue <= 30) || (hue >= 330))        Serial.println("Red");
  else if (hue <= 90)                    Serial.println("Yellow");
  else if (hue <= 150)                   Serial.println("Green");
  else if (hue <= 210)                   Serial.println("Cyan");
  else if (hue <= 270)                   Serial.println("Blue");
  else                                   Serial.println("Magenta");

  delay(250);
}
