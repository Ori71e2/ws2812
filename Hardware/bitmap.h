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

#ifndef __BITMAP_H
#define __BITMAP_H

#include <stdint.h>

struct RGB
{
  uint8_t r, g, b;  // r, g, b 取值1-255
};

struct HSV
{
  int16_t h;        // h取值0-360
  uint8_t s, v;     // s, v 取值1-255, 不是1-100
};

typedef struct RGB RGB_t;
typedef struct HSV HSV_t;
typedef uint32_t HEX_t;

void HSV2RGB(HSV_t *hsv, RGB_t *rgb);
void HEX2RGB(HEX_t hex, RGB_t *rgb);
void HEX2HSV(HEX_t hex, HSV_t *hsv);
void RGB2HEX(RGB_t *rgb, HEX_t *hex);
void RGB2HSV(RGB_t *rgb, HSV_t *hsv);
void HSV2HEX(HSV_t *hsv, HEX_t *hex);

void ARR_HSV2RGB(HSV_t *ledsHsv, RGB_t *ledsRgb ,int count);
void ARR_HEX2RGB(HEX_t *ledsHex, RGB_t *ledsRgb ,int count);

void ARR_RGB2HSV(RGB_t *ledsRgb, HSV_t *ledsHsv ,int count);
void ARR_HEX2HSV(HEX_t *ledsHex, HSV_t *ledsHsv ,int count);
#endif //__BITMAP_H
