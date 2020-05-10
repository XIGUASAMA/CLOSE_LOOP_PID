#include<function.h>

uchar Tm;

void main()
{
	 Init();
	 while(1)
	 {
	 	CS1=0x00;
		delay(10);
		switch(show_flag)
		{
			case 0:  display_temp();  break;
			case 1:
			case 2:
			case 3:
			case 4:  display_setting(); break;
		}
		keyboard_checking();
		if(ctrl_flag) loopctrl();
		else output_t_room();
	 }
}

void input() interrupt 0
{
	EA=0;
	vol=CS1;
	Tm=(uchar)(0.390625*vol);
	EA=1;
}