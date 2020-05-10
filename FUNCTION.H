#include<reg51.h>
#include<absacc.h>
#define uint unsigned int
#define uchar unsigned char

#define CS00 XBYTE[0x0000]	    //数码管控制
#define CS01 XBYTE[0x0001]
#define CS02 XBYTE[0x0002]
#define CS03 XBYTE[0x0003]
#define CS04 XBYTE[0x0004]	    //按键控制
#define CS05 XBYTE[0x0005]
#define CS06 XBYTE[0x0006]
#define CS07 XBYTE[0x0007]   
#define CS1  XBYTE[0x20FF]		  //AD
#define CS2  XBYTE[0x40FF]	  	//DA
#define CS3  XBYTE[0x60FF]	 

#define t_room 0

void Init();
void display_temp();
void display_setting();
void output_t_room();
void delay(uint z);
void keyboard_checking();
void loopctrl();
void calculate_pid();

extern uchar vol;
extern uchar qian,bai,shi,ge;
extern uchar show_flag,ctrl_flag;
extern uchar expect_vol;
extern float expect_temp;
extern uchar qian_saved,bai_saved,shi_saved,ge_saved;

extern uchar Tset,Tm;
extern int   dbasa,dbasb;
extern float tvu,tvd;
extern int   te_1,te_2;
extern uchar tc_data;

extern uchar hold;
            