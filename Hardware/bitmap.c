// The MIT License (MIT)
//
// Copyright (c) 2015 Aleksandr Aleshin <silencer@quadrius.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdint.h>

#include "bitmap.h"

void HEX2RGB(HEX_t hex, RGB_t *rgb)
{
  rgb->r = ((hex >> 16) & 0xFF);
  rgb->g = ((hex >> 8) & 0xFF);
  rgb->b = ((hex) & 0xFF);
}
void RGB2HEX(RGB_t *rgb, HEX_t *hex)
{
	*hex = (rgb->r << 16) + (rgb->g << 8) + (rgb->b);
}

void HEX2HSV(HEX_t hex, HSV_t *hsv)
{
	RGB_t rgb;
	HEX2RGB(hex, &rgb);
	RGB2HSV(&rgb, hsv);
}

void HSV2HEX(HSV_t *hsv, HEX_t *hex)
{
	RGB_t rgb;
	HSV2RGB(hsv, &rgb);
	RGB2HEX(&rgb, hex);
}
void HSV2RGB(HSV_t *hsv, RGB_t *rgb)
{
  if (!hsv->v)
  {
    rgb->r = rgb->g = rgb->b = 0;
  }
  else if (!hsv->s)
  {
    rgb->r = rgb->g = rgb->b = hsv->v;
  }
  else
  {
    int16_t hue = hsv->h % 360;
		hue = hue < 0 ? 360 + hue : hue;

    int sector = hue / 60;
    int angle = sector & 1 ? 60 - hue % 60 : hue % 60;

    int high = hsv->v;
    int low = (255 - hsv->s) * high / 255;
    int middle = low + (high - low) * angle / 60;

    switch (sector)
    {
    case 0: // red -> yellow
      rgb->r = high;
      rgb->g = middle;
      rgb->b = low;

      break;

    case 1: // yellow -> green
      rgb->r = middle;
      rgb->g = high;
      rgb->b = low;

      break;

    case 2: // green -> cyan
      rgb->r = low;
      rgb->g = high;
      rgb->b = middle;

      break;

    case 3: // cyan -> blue
      rgb->r = low;
      rgb->g = middle;
      rgb->b = high;

      break;

    case 4: // blue -> magenta
      rgb->r = middle;
      rgb->g = low;
      rgb->b = high;

      break;

    case 5: // magenta -> red
      rgb->r = high;
      rgb->g = low;
      rgb->b = middle;
    }
  }
}

void RGB2HSV(RGB_t *rgb, HSV_t *hsv)
{
    uint8_t rgbMin, rgbMax;

    rgbMin = rgb->r < rgb->g ? (rgb->r < rgb->b ? rgb->r : rgb->b) : (rgb->g < rgb->b ? rgb->g : rgb->b);
    rgbMax = rgb->r > rgb->g ? (rgb->r > rgb->b ? rgb->r : rgb->b) : (rgb->g > rgb->b ? rgb->g : rgb->b);
    
    hsv->v = rgbMax;
    if (hsv->v == 0)
    {
        hsv->h = 0;
        hsv->s = 0;
        return;
    }

    hsv->s = 255 * (uint32_t)(rgbMax - rgbMin) / hsv->v;
    if (hsv->s == 0)
    {
        hsv->h = 0;
        return;
    }

    if (rgbMax == rgb->r)
        hsv->h = 0 + 43 * (rgb->g - rgb->b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb->g)
        hsv->h = 85 + 43 * (rgb->b - rgb->r) / (rgbMax - rgbMin);
    else
        hsv->h = 171 + 43 * (rgb->r - rgb->g) / (rgbMax - rgbMin);
    return;
}

void ARR_HSV2RGB(HSV_t *ledsHsv, RGB_t *ledsRgb ,uint32_t count)
{
	for (int i = 0; i < count; i++)
	{
		HSV2RGB(ledsHsv + i, ledsRgb + i);
 	}
}

void ARR_HEX2RGB(HEX_t *ledsHex, RGB_t *ledsRgb ,uint32_t count)
{
	for (int i = 0; i < count; i++)
	{
		HEX2RGB(*(ledsHex + i), ledsRgb + i);
 	}
}

void ARR_RGB2HSV(RGB_t *ledsRgb, HSV_t *ledsHsv ,uint32_t count)
{
	for (int i = 0; i < count; i++)
	{
		RGB2HSV(ledsRgb + i, ledsHsv + i);
 	}
}

void ARR_HEX2HSV(HEX_t *ledsHex, HSV_t *ledsHsv ,uint32_t count)
{
	for (int i = 0; i < count; i++)
	{
		HEX2HSV(*(ledsHex + i), ledsHsv + i);
 	}
}
