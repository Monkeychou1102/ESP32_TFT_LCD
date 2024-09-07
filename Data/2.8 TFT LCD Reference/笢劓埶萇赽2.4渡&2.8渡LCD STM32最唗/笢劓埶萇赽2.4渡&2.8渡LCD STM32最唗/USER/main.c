//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : TFT_LCD �ӿ���ʾ����(stm32ϵ��)
//              ˵��: 
//              -�˲���Ϊ���������ӿڣ�BLKΪ���⿪�أ�Ĭ�Ͽ��Բ���---------------------------------------------------------------
//              GND    ��Դ��
//              VCC    3.3v��Դ
//              CLK    ��PD6
//              MOSI   ��PD7
//              RES    ��PD4
//              DC     ��PD5
//              CS1    ��PD3               
//              -����Ϊ�������ƽӿڣ�������ó�û���ܿ��Բ���---------------------------------------------------------------
//              MISO  ��PC2
//              CS2   ��PC0
//              PEN   ��PC10  
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "touch.h"
u8 ref=0;//ˢ����ʾ

void xianshi()//��ʾ��Ϣ
{   
	u16 lx,ly;
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	showhanzi(10,0,0);  //��
	showhanzi(45,0,1);  //ҫ
  LCD_ShowString(10,35,"2.4 TFT SPI 240*320");
	LCD_ShowString(10,55,"LCD_W:");	LCD_ShowNum(70,55,LCD_W,3);
	LCD_ShowString(110,55,"LCD_H:");LCD_ShowNum(160,55,LCD_H,3);	
	lx=10;ly=75;			
	LCD_ShowString(lx,ly,"VX:");lx+=40;LCD_ShowNum(lx,ly,vx,5);					
	lx+=60;
	LCD_ShowString(lx,ly,"Vy:");lx+=40;LCD_ShowNum(lx,ly,vy,5);					
	lx=10;ly=95; 
	LCD_ShowString(lx,ly,"CHX:");lx+=40;LCD_ShowNum(lx,ly,chx,5);					
	lx+=60; 
	LCD_ShowString(lx,ly,"CHY:");lx+=40;LCD_ShowNum(lx,ly,chy,5);
}

u8 jiance() //��ⴥ���Ͱ���
{
	if (tpstate()==0) //����������£�������ͼ����
	 {
	 	LCD_Clear(WHITE); //����
		BACK_COLOR=WHITE;
		POINT_COLOR=RED;
	 	point();
		return 1;
	 }	

	   return 0;
}

void showimage() //��ʾ40*40ͼƬ
{
  	int i,j,k; 
	LCD_Clear(WHITE); //����  
	xianshi(); //��ʾ��Ϣ
	for(k=3;k<8;k++)
	{
	   	for(j=0;j<6;j++)
		{	
			Address_set(40*j,40*k,40*j+39,40*k+39);		//��������
		    for(i=0;i<1600;i++)
			 { 	
				 if(jiance()) //��ⴥ���Ͱ���
				 {	
				 	ref=1;
				  	return;	
				 }		
			  	 LCD_WR_DATA8(image[i*2+1]);	 
				 LCD_WR_DATA8(image[i*2]);				
			 }	
		 }
	}
	ref=0;				
}
 int main(void)
 {	u8 t;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	TP_Init();
	 spistar()  ;//ģ��SPI��ʼ��
	 Lcd_Init();			//��ʼ��OLED  
	
	LCD_Clear(WHITE); //����
	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 
    showimage(); //��ʾ40*40ͼƬ
	 jiance();
//Touch_Adjust();//У׼
	while(1)
	{ if(jiance()) //��ⴥ���Ͱ���
	  {	
	  	showimage(); //��ʾ40*40ͼƬ
	  }
	  if(ref){showimage();} //��ʾ40*40ͼƬ

    }
}

