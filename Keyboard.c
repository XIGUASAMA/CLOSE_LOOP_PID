#include<function.h>

uchar code position[4][5]={		    //存储矩阵键盘信息
{0x01,0x02,0x03,0x88,0xCC},
{0x04,0x05,0x06,0x99,0xDD},
{0x07,0x08,0x09,0xAA,0xEE},
{0x10,0x00,0x10,0xBB,0xFF},
}; 

uchar show_flag,ctrl_flag;
uchar qian,bai,shi,ge;
uchar qian_saved,bai_saved,shi_saved,ge_saved;
uchar expect_vol;
float expect_temp;
uchar Tset;

void keyboard_checking()
{
	uchar r_val,c_val,key_state,temp;
	for(r_val=4; r_val<8; r_val++)
	{
		if(key_state=(~XBYTE[r_val] & 0x1F))
		{
			for(c_val=0,temp=1; c_val<5;++c_val, temp=temp<<1)
			{
				if((key_state&temp)!=0 && show_flag==0 && position[r_val-4][c_val]<0x10)
				{
					delay(800);
					show_flag=1;
					qian=bai=shi=20;
					ge=position[r_val-4][c_val];
				}
				else if((key_state&temp)!=0 && show_flag==1 && position[r_val-4][c_val]<0x10)
				{
					delay(800);
					show_flag=2;
					shi=ge;
					ge=position[r_val-4][c_val];
				}
				else if((key_state&temp)!=0 && show_flag==2 && position[r_val-4][c_val]<0x10)
				{
					delay(800);
					show_flag=3;
					bai=shi;
					shi=ge;
					ge=position[r_val-4][c_val];
				}
				else if((key_state&temp)!=0 && show_flag==3 && position[r_val-4][c_val]<0x10)
				{
					delay(800);
					show_flag=4;
					qian=bai;
					bai=shi;
					shi=ge;
					ge=position[r_val-4][c_val];
				}
				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0x10)  //输入小数点
				{
					delay(800);
					ge+=10;
				}
				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0xCC)  //输入100C
				{
					delay(800);
					show_flag=0;
					expect_vol=0xFF;
					qian=1;
					bai=0;
					shi=10;
					ge=0;
					Tset=100;
					calculate_pid();
				}
				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0x99)  //停止控制
				{
					ctrl_flag=0;
				}
				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0xDD)  //启动控制
				{
					ctrl_flag=1;
				}				
				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0xAA)  //查看当前温度
				{
					delay(800);
					show_flag=0;
				}
				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0xEE)  //查看设置温度
				{
					delay(800);
					show_flag=4;
				}

				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0xBB)  //取消输入
				{
					delay(800);
					qian=qian_saved;
					bai=bai_saved;
					shi=shi_saved;
					ge=ge_saved;
					show_flag=0;
				}
				else if((key_state&temp)!=0 && position[r_val-4][c_val]==0xFF)  //确认输入
				{
					delay(800);
					switch(show_flag)
					{
						case 1:
							expect_temp=ge%10;
							break;
						case 2:
							if(shi>=10)  expect_temp=(shi%10)+(ge%10)*0.1;
							else         expect_temp=(shi%10)*10+(ge%10);
							break;
						case 3:
							if(bai>=10)      expect_temp=(bai%10)+(shi%10)*0.1+(ge%10)*0.01;
							else if(shi>=10) expect_temp=(bai%10)*10+(shi%10)+(ge%10)*0.1;
							break;
						case 4:
							if(qian>=10)      expect_temp=(qian%10)+(bai%10)*0.1+(shi%10)*0.01+(ge%10)*0.001;
							else if(bai>=10)  expect_temp=(qian%10)*10+(bai%10)+(shi%10)*0.1+(ge%10)*0.01;
							break;
					}
					Tset=(uchar)expect_temp;
					calculate_pid();
					expect_vol=(unsigned char)(expect_temp*2.56);
					qian_saved=qian;
					bai_saved=bai;
					shi_saved=shi;
					ge_saved=ge;
					show_flag=0;
				}
			}
		}    
  }
}
