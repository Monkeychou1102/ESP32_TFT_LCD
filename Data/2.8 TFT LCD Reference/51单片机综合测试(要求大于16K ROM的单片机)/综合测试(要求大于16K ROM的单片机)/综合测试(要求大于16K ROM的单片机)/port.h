#ifndef __PORT_H
#define __PORT_H		
/******************************************************
接线方式
VCC=3.3V
GND=GND
P22=RES
P23=DC
P24=CS1
P25=CLK
P26=MOSI

如果不用触摸下面三个脚可以不接
P31=MISO
P33=CS2
P34=PEN


******************************************************/


sbit LCD_CS     =P2^4;     //片选	
sbit LCD_DC     =P2^3;	  //数据/命令切换
sbit LCD_SDI    =P2^6;	  //数据
sbit LCD_SCK    =P2^5;	  //时钟
sbit LCD_REST   =P2^2;	  //复位 

  
sbit TOUCH_CS        =    P3^3;
sbit TOUCH_DOUT      =    P3^1;																						   
sbit Penirq    =    P3^4;   //检测触摸屏响应信号
sbit key1=P2^0;				  		 
#endif  ·