#include<function.h>

uchar code table[]={		    //�洢���ֺ�С����
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
0xFF,//Ϩ��
0x7F,//С����
};

void display_temp() //��ʾ��ǰ�¶�
{ 
	int  b;
	int x1,x2,x3,x4;	//�ֱ�Ϊʮλ����λ��С�����һλ��С�������λ
	b=(int)(0.390625*vol*100); //0x00-0xffת��Ϊ0-100
	x1=(int)b%10;				//С�����ڶ�λ
	x2=(b%100)/10;			//С������һλ
	x3=(b%1000)/100;	  //��λ
	x4=b/1000;			    //ʮλ
	CS00=table[x1];
	CS01=table[x2];
	CS02=~((~table[x3])|(~table[21])); //�ڸ�λ���ֺ����С����
	CS03=table[x4];
}

void display_setting() //��ʾ�趨�¶�
{
	CS00=table[ge];
	CS01=table[shi];
	CS02=table[bai];
	CS03=table[qian];
}