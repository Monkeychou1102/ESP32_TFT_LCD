https://coxxect.blogspot.com/2023/05/128x160-tftst7735-spi-wih-ep32c3.html

128x160 TFT/ST7735 SPI wih EP32C3 (arduino-esp32) using Arduino_GFX Library
May 19, 2023
Previous post show 3.5 inch 480x320 TFT/ILI9488 SPI wih EP32C3 (arduino-esp32) 
using Arduino_GFX Library, here is how it display on 1.8 inch 128x160 ST7735 SPI TFT.

Both the 3.5 inch 480x320 ILI9488 SPI TFT 
and 1.8 inch 128x160 ST7735 SPI TFT have 
the same pins assignment on TFT part, 
keep the connection keep no change.

c3_st7735_test.ino, for color and resolution test.
/*******************************************************************************
 * Exercise of Arduino_GFX, color testing.
 * Run on Xiao ESP32C3 + 1.8 inch 128x160 ST7735 SPI TFT
 ******************************************************************************/
#include <Arduino_GFX_Library.h>

#define TFT_CS    5   //GPIO5
#define TFT_RESET 3   //GPIO3
#define TFT_DC    4   //GPIO4
#define TFT_MOSI  10  //GPIO10/MOSI
#define TFT_SCK   8   //GPIO8/SCK
#define TFT_LED   2   //GPIO2
#define TFT_MISO  -1  // not used for TFT

#define GFX_BL TFT_LED // backlight pin

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_HWSPI(TFT_DC, TFT_CS);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_ST7735(
  bus, TFT_RESET, 3 /* rotation */, false /* IPS */,
  128 /* width */, 160 /* height */,
  0 /* col offset 1 */, 0 /* row offset 1 */,
  0 /* col offset 2 */, 0 /* row offset 2 */,
  false /* BGR */);

/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/
 
void setup(void)
{
    gfx->begin();
    gfx->fillScreen(BLACK);

#ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
#endif
    gfx->setTextColor(WHITE);
    gfx->setTextSize(1, 1, 2);

    gfx->setCursor(10, 10);
    gfx->println("XIAO ESP32C3 (in Arduino framework)");

    gfx->setCursor(10, 30);
    gfx->println("+ ILI9488 SPI TFT");

    gfx->setCursor(10, 50);
    gfx->println("using Arduino_GFX Library");

    int w = gfx->width();
    int h = gfx->height();

    gfx->setCursor(10, 70);
    gfx->printf("%i x %d", w, h);
    gfx->drawRect(0, 0, w, h, WHITE);

    delay(3000);

    for(int i=0; i<w; i++){
      int d = (int)(255 * i/w);
      gfx->drawLine(i, 0, i, h, RGB565(d, 0, 0));
      delay(10);
    }
	
	    for(int i=0; i<w; i++){
      int d = (int)(255 * i/w);
      gfx->drawLine(w-i, 0, w-i, h, RGB565(0, d, 0));
      delay(10);
    }
	
    for(int i=0; i<w; i++){
      int d = (int)(255 * i/w);
      gfx->drawLine(i, 0, i, h, RGB565(0, 0, d));
      delay(10);
    }
}

void loop()
{
    gfx->setTextColor(WHITE);
    gfx->setTextSize(2, 2, 2);

    gfx->fillScreen(RED);
    gfx->setCursor(100, 100);
    gfx->printf("RED");
    delay(2000);

    gfx->fillScreen(GREEN);
    gfx->setCursor(100, 100);
    gfx->printf("GREEN");
    delay(2000);

    gfx->fillScreen(BLUE);
    gfx->setCursor(100, 100);
    gfx->printf("BLUE");
    delay(2000);
}



	