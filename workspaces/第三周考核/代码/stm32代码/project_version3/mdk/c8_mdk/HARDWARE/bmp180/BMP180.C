#include "BMP180.h"
#include "delay.h"
#include "myiic.h"
#include "sys.h"
#include "math.h"
//***BMP085使用
long  result_UT=0;
long  result_UP=0;

short ac1;
short ac2; 
short ac3; 
unsigned short ac4;
unsigned short ac5;
unsigned short ac6;
short b1; 
short b2;
short mb;
short mc;
short md;

//*********************************************************
//读出BMP085内部数据,连续两个
//*********************************************************
u16 Multiple_read(u8 ST_Address)
{   
	u8 msb, lsb;
	u16 _data;
    IIC_Start();                          //起始信号
    IIC_Send_Byte(BMP180_SlaveAddress);    //发送设备地址+写信号
	while(IIC_Wait_Ack());
    IIC_Send_Byte(ST_Address);             //发送存储单元地址
	while(IIC_Wait_Ack());                                 
    IIC_Start();                          //起始信号
    IIC_Send_Byte(BMP180_SlaveAddress+1);         //发送设备地址+读信号
	while(IIC_Wait_Ack());                                        

    msb = IIC_Read_Byte(1);                 //BUF[0]存储                
    lsb = IIC_Read_Byte(0);                //最后一个数据需要回NOACK

    IIC_Stop();                           //停止信号
    delay_ms(5);
    _data = msb << 8;
	_data |= lsb;	
	return _data;
}
//********************************************************************
u16 bmp180ReadTemp(void)
{

    IIC_Start();                  //起始信号
    IIC_Send_Byte(BMP180_SlaveAddress);   //发送设备地址+写信号   BMP180_SlaveAddress  0xee	气压传感器器件地址
	while(IIC_Wait_Ack());
    IIC_Send_Byte(0xF4);	          // write register address
    while(IIC_Wait_Ack());
	IIC_Send_Byte(0x2E);       	// write register data for temp
    while(IIC_Wait_Ack());
	IIC_Stop();                   //发送停止信号
	delay_ms(10);	// max time is 4.5ms
	return Multiple_read(0xF6);
}
//*************************************************************
u16 bmp180ReadPressure(void)
{
	//u16 pressure = 0;

    IIC_Start();                   //起始信号
    IIC_Send_Byte(BMP180_SlaveAddress);   //发送设备地址+写信号
    while(IIC_Wait_Ack());
	IIC_Send_Byte(0xF4);	          // write register address
    while(IIC_Wait_Ack());
	IIC_Send_Byte(0x34);       	  // write register data for pressure
    while(IIC_Wait_Ack());
	IIC_Stop();                    //发送停止信号
	delay_ms(20);    	                  // max time is 4.5ms
	
	//pressure = Multiple_read(0xF6);
	//pressure &= 0x0FFFF;
	
	return Multiple_read(0xF6);//pressure;	
}

//**************************************************************

//初始化BMP085，根据需要请参考pdf进行修改**************
void Init_BMP180()
{
	IIC_Init();
	ac1 = Multiple_read(0xAA);
	ac2 = Multiple_read(0xAC);
	ac3 = Multiple_read(0xAE);
	ac4 = Multiple_read(0xB0);
	ac5 = Multiple_read(0xB2);
	ac6 = Multiple_read(0xB4);
	b1 =  Multiple_read(0xB6);
	b2 =  Multiple_read(0xB8);
	mb =  Multiple_read(0xBA);
	mc =  Multiple_read(0xBC);
	md =  Multiple_read(0xBE);
}
//***********************************************************************
void bmp180Convert()
{
	unsigned int ut;
	unsigned long up;
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;

	ut = bmp180ReadTemp();	   // 读取温度
	up = bmp180ReadPressure();  // 读取压强    return pressure;	
	//*************
	x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
	x2 = ((long) mc << 11) / (x1 + md);
	b5 = x1 + x2;
	result_UT = ((b5 + 8) >> 4);
	//*************		
	b6 = b5 - 4000;
	                         // Calculate B3
	x1 = (b2 * (b6 * b6)>>12)>>11;
	x2 = (ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;	
	                         // Calculate B4
	x1 = (ac3 * b6)>>13;
	x2 = (b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
	
	b7 = ((unsigned long)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
	p = (b7<<1)/b4;
	else
	p = (b7/b4)<<1;
	
	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	result_UP = p+((x1 + x2 + 3791)>>4);
	
	result_UP-=500;//人为篡改
	
}


/****************************************************************
　　　函数名称：BMP085_Get_Altitude			    
　　　函数功能：获取海拔高度值
　　　入口参数：无
　　　出口参数：altitude //int型  2字节，当前海拔高度值
　　　备 注：	 返回的高度值单位为厘米，调用时再换算成带小数的以米为单位的高度值
*****************************************************************/

double BMP085_Get_Altitude()
{
	double altitude;
	double pressure=(double)result_UP;				//获取气压值
	altitude=44330.0*(1-pow((double)pressure/101325,1/5.255));  	//根据芯片手册提供的公式计算海拔高度
	//altitude*=100;	 		//转换成厘米单位的高度值，调用时再换算成带小数的高度值，提高精度
	return altitude;
}
;

void bmp180end(float *x,long *y,double *z){
		bmp180Convert();
		//printf("气温：%f  气压：%ld  海拔：%lf\r\n",(float)result_UT*0.1+1.7,result_UP,BMP085_Get_Altitude());
	  *x=(float)result_UT*0.1+1.7;
	*y=result_UP;
	*z=BMP085_Get_Altitude();
}
;

