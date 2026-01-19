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

int checkColor(){
  //0 = R //1 = G //2 = B //3 = Y //4 = W

  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  int colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  // Optional: normalize RGB using clear channel
  if (c > 0) {
    r = (uint16_t)((float)r / c * 65535.0f);
    g = (uint16_t)((float)g / c * 65535.0f);
    b = (uint16_t)((float)b / c * 65535.0f);
  }

  float hue = rgbToHue(r, g, b);

  if ((hue <= 30) || (hue >= 330))  {return 0;}
  else if (hue <= 90 && colorTemp <= 2800)  {return 3;}
  else if (hue <= 90 && colorTemp > 3200) {return 4;}
  else if (hue <= 150)  {return 1;}
  else if (hue <= 270)  {return 2;}
}