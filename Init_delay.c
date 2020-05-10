#include<function.h>

uchar vol,hold;

void Init()
{
	vol=0;	
	EA=1;
	EX0=1;	
	CS00=CS01=CS02=CS03=0xFF;
	show_flag=0;
	ctrl_flag=0;
	expect_vol=0x40;//³õÊ¼»¯Ä¬ÈÏ¿ØÎÂ25C
	Tset=25;
	qian_saved=qian=2;
	bai_saved=bai=5+10;
	shi_saved=shi=0;
	ge_saved=ge=0;
	hold=0;
	calculate_pid();
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

