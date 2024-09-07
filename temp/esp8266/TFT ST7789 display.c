// WROOM_ST_7789_240x240TFT_ESP32D_radar_nn
// Floris Wouterlood 21 December 2019
// public domain
// sketch for ESP-WROOM-32D
// upload to board type DOIT ESP32 DEVKIT V1
// display on a 1.3 inch 3.3V TFT_display with ST7789 controller
// 240 x 240 pixels in this confguration
//
// all x and y coordinates relative to center coordinates x=120 and y=120
// is your screen bigger than 240x240 -- change the center coordinates
// pin layout:
// GND ---- GND
// VCC ---- 3.3V
// SCL ---- D18
// SDA ---- D23
// RES ---- D4
// DC ----- D2
// BLK -- not connected

#include <Arduino_ST7789.h> // hardware-specific library for ST7789
#include <SPI.h>

#define TFT_DC 2 // pin of your choice
#define TFT_RST 4 // pin of your choice
#define TFT_MOSI 23 // fixed pin
#define TFT_SCLK 18 // fixed pin

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);

#define SCOPE 0x3206 // scope glass color - CRT like luminescent

// center coordinates
// for screens bigger than 240x240 - change these x-y coordinates

float center_x = 120; // center x of radar scope on 240x320 TFT display
float center_y = 120; // center y of radar scope on 240x320 TFT display
float edge_x = 0;
float edge_y = 0;
float edge_x_old = 0; // remember previous edge x coordinate
float edge_y_old = 0; // remember previous edge y coordinate
float edge_x_out = 0;
float edge_y_out = 0;
int j; // for for-next loops
float angle = 0;
int radius = 90;
int scope_x = 0;
int scope_y = 0;

void setup(void) {

Serial.begin (9600);
Serial.println (); // cut out the gibberish
Serial.println ();
Serial.println ("Hello! ST7789 TFT radar test"); // test Serial Monitor
Serial.println ("on NodeMCU ESP8266");

tft.init (240, 240); // initialize a ST7789 chip, 240x240 pixels
tft.fillScreen (BLACK);
tft.setCursor (10, 10);
tft.setTextColor (YELLOW);
tft.setTextSize (3);
tft.println ("radar scope initializing"); // initialization message on the TFT display
tft.println ("............");
delay (500);
tft.fillScreen (BLACK);

// =========== construct the radar scope =====================================================

edge_x = (center_x);
edge_y = (center_y);
scope_x = (center_x-119);scope_y = (center_y-119);
tft.drawRect (scope_x,scope_y,239,239,RED); // rectangular scope outer contour
scope_x = (center_x+90); scope_y = (center_y-100); // right upper screw
screw();
scope_x = (center_x-90); scope_y = (center_y-100); // left upper screw
screw();
scope_x = (center_x-90); scope_y = (center_y+100); // left lower screw
screw();
scope_x = (center_x+90); scope_y = (center_y+100); // right lower screw
screw();

angle=0;

// scope CRT
tft.drawCircle (center_x,center_y, (radius+1), RED);
tft.drawCircle (center_x,center_y, (radius+2), RED);
tft.fillCircle (center_x,center_y, radius, SCOPE);
tft.fillCircle (center_x,center_y, radius, SCOPE);
tft.fillCircle (center_x,center_y, 2, GREEN);
tft.drawCircle (center_x,center_y, 60, GREEN);
tft.drawCircle (center_x,center_y, 90, GREEN);
draw_scale();
}

void loop (){

for (j=0;j<360;j++) {
angle = (j*0.01745331); // angle is expressed in radians - 1 degree = 0,01745331 radians
edge_coord (); // calculate beam
sweep_beam ();
tft.fillCircle (center_x,center_y,2,GREEN); // restore centerpoint
yield(); // resest ESP8266 timer and prevents WDT-necessary for NodeMCU

}
}

// =============== SUBROUTINES ===============================================================

// calculate beam radial end coordinates and remember previous end coordinates
void edge_coord (){
edge_x_old = edge_x;
edge_y_old = edge_y;
edge_x = (center_x+(radiuscos(angle)));
edge_y = (center_y+(radiussin(angle)));
}

// erase old beam and draw new beam
void sweep_beam (){
// overdraw previous beam with scope color
tft.drawLine (center_x,center_y,edge_x_old,edge_y_old,SCOPE);
// draw new beam position with scope color
tft.drawLine (center_x,center_y,edge_x,edge_y,GREEN);
}

// draw screw subroutine
void screw (){
tft.drawCircle (scope_x,scope_y, 6,RED);
tft.drawLine ((scope_x-11),scope_y,(scope_x+11),(scope_y),RED);
tft.drawLine (scope_x,(scope_y-11),scope_x,(scope_y+11),RED);
}

// draw scale marker line segments subroutine
void draw_scale (){
j = 0;
do {
angle = (j0.01745331); // angle expressed in radians - 1 degree = 0,01745331 radians
edge_x = (center_x+(radiuscos(angle)));
edge_y = (center_y+(radius*sin(angle)));
edge_x_out = (center_x+((radius+8)*cos(angle)));
edge_y_out = (center_y+((radius+8)*sin(angle)));
tft.drawLine (edge_x,edge_y, edge_x_out, edge_y_out,RED);
j = j+10;
} while (j<360);
}