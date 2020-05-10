#include<function.h>

uchar code table[]={		    //存储数字和小数点
0xC0,//0
0xF9,//1
0xA4,//2
0xB0,//3
0x99,//4
0x92,//5
0x82,//6
0xF8,//7
0x80,//8
0x90,//9
0x40,//0.
0x79,//1.
0x24,//2.
0x30,//3.
0x19,//4.
0x12,//5.
0x02,//6.
0x78,//7.
0x00,//8.
0x10,//9.
0xFF,//熄灭
0x7F,//小数点
};

void display_temp() //显示当前温度
{ 
	int  b;
	int x1,x2,x3,x4;	//分别为十位，个位，小数点后一位和小数点后两位
	b=(int)(0.390625*vol*100); //0x00-0xff转换为0-100
	x1=(int)b%10;				//小数点后第二位
	x2=(b%100)/10;			//小数点后第一位
	x3=(b%1000)/100;	  //个位
	x4=b/1000;			    //十位
	CS00=table[x1];
	CS01=table[x2];
	CS02=~((~table[x3])|(~table[21])); //在个位数字后加入小数点
	CS03=table[x4];
}

void display_setting() //显示设定温度
{
	CS00=table[ge];
	CS01=table[shi];
	CS02=table[bai];
	CS03=table[qian];
}