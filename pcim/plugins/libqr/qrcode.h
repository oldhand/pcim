#pragma once

#include <iostream>
#include <string.h>
#include <errno.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>

#include "qrencode.h"

#define OUT_FILE_PIXEL_PRESCALER    8                                           // Prescaler (number of pixels in bmp file for each QRCode pixel, on each dimension)

#define PIXEL_COLOR_R               0                                           // Color of bmp pixels
#define PIXEL_COLOR_G               0
#define PIXEL_COLOR_B               0xff

// BMP defines

typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef signed long     LONG;

#define BI_RGB          0L


class QrCode
{
public:
	static bool make(std::string text, std::string imagepath);

};

