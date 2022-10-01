#ifndef __BMP180_H__
#define __BMP180_H__

#define	BMP180_SlaveAddress     0xee	//气压传感器器件地址

#define   OSS 0	 //	BMP085使用
#define   REG_Pressure 0x34 // oss=0 4.5


void Init_BMP180(void);//初始化IO   读取校准参数
void bmp180Convert(void);	//校准温度和气压 ，将结果分别存入 result_UP result_UT
double BMP085_Get_Altitude(void);
void bmp180end(float *x,long *y,double *z);
#endif

