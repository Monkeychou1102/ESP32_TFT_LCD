#ifndef __PORT_H
#define __PORT_H		
/******************************************************
���߷�ʽ
VCC=3.3V
GND=GND
P22=RES
P23=DC
P24=CS1
P25=CLK
P26=MOSI

������ô������������ſ��Բ���
P31=MISO
P33=CS2
P34=PEN


******************************************************/


sbit LCD_CS     =P2^4;     //Ƭѡ	
sbit LCD_DC     =P2^3;	  //����/�����л�
sbit LCD_SDI    =P2^6;	  //����
sbit LCD_SCK    =P2^5;	  //ʱ��
sbit LCD_REST   =P2^2;	  //��λ 

  
sbit TOUCH_CS        =    P3^3;
sbit TOUCH_DOUT      =    P3^1;																						   
sbit Penirq    =    P3^4;   //��ⴥ������Ӧ�ź�
sbit key1=P2^0;				  		 
#endif  ��