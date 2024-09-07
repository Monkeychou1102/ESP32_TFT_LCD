//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : TFT_LCD 接口演示例程(stm32系列)
//              说明: 
//              -此部分为不带触摸接口，BLK为背光开关，默认可以不接---------------------------------------------------------------
//              GND    电源地
//              VCC    3.3v电源
//              CLK    接PD6
//              MOSI   接PD7
//              RES    接PD4
//              DC     接PD5
//              CS1    接PD3               
//              -以下为触摸控制接口；如果不用出没功能可以不接---------------------------------------------------------------
//              MISO  接PC2
//              CS2   接PC0
//              PEN   接PC10  
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/

#ifndef __TOUCH_H
#define __TOUCH_H	

/* touch panel interface define */
#define  CMD_RDX  0xD0	 //触摸IC读坐标积存器
#define  CMD_RDY  0x90
#define	u8 unsigned char
#define	u16 unsigned int
#define	u32 unsigned long


#define PEN  	PCin(10)  	//PC10 INT
#define MISO 	PCin(2)   	//PC2  MISO
//#define DIN 	PCout(3)  	//PC3  MOSI
//#define CLK 	PCout(1)  	//PC1  SCLK
#define CS2  	PCout(0)  	//PC0  CS 
struct tp_pix_
{
	u16 x;
	u16 y;
};
struct tp_pixu32_
{
	u32 x;
	u32 y;
};
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //当前触控坐标的AD值,前触控坐标的像素值   
extern u16 vx,vy;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
extern u16 chx,chy;//默认像素点坐标为0时的AD起始值
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //绘图函数
u16 ReadFromCharFrom7843();         //SPI 读数据
u8 TP_Init(void);
#endif  
	 
	 



