#include<function.h>

int te_1,te_2;
uchar tc_data;

void loopctrl()
{
    int val,data_inc;
    //long temp;
    float t;
    val=Tset;		                  //温度设置值扩展1倍
    if(Tm<val)	                  //当前温度小于设定温度,增温处理
    {	
        t=val-Tm;		              //计算目标温差
        if(t>tvu)	                //目标温差大于阀值的处理
        {
            hold=0;		            //清除温度保持控制标志
            tc_data=255;	        //强制DAC数据为255
            CS2=tc_data;          //刷新DAC控制数据
        }
				else			//目标温差小于等于阀值的处理
				{
					if(hold==0)		//初次进入温度保持控制状态的处理
					{
							if(val>=t_room)   tc_data=dbasa;         //目标温度大于等于室温初值
							else		          tc_data=dbasb;         //目标温度小于室温的初值
							hold=1;		                               //置位温度保持控制标志
					}		
					data_inc=2.0*(t-te_1)+0.1*t+1.0*(t-2*te_1+te_2);    //PID控制增量计算
					tc_data=tc_data+data_inc;	                          //计算DAC控制数据
					if(tc_data+5>255)  CS2=255;		                      //刷新DAC控制数据
					else               CS2=tc_data+5;
				}
		}
    else				//当前温度大于等于设定温度,减温处理
    {
        t=Tm-val;			//计算目标温差
        if(t>tvd)			//目标温差大于阀值的处理
        {
            hold=0;			  //清除温度保持控制标志
            tc_data=0;		//强制DAC数据为0
            CS2=tc_data;	//刷新DAC控制数据
        }
        else				//目标温差小于等于阀值的处理
        {
            if(hold==0)		//温度保持操作
            {
								if(val>=t_room)   tc_data=dbasa;       //目标温度大于等于室温初值
								else	            tc_data=dbasb;       //目标温度小于室温初值
								hold=1;		                             //置位温度保持控制标志
            }
            t=-t;	//目标温差取负值
            data_inc=2.0*(t-te_1)+0.1*t+1.0*(t-2*te_1+te_2);//PID控制增量计算
            tc_data=tc_data+data_inc;		                    //计算DAC控制数据
					  if(tc_data+5>255)  CS2=255;		                      //刷新DAC控制数据
					  else               CS2=tc_data+5;
        }
    }
    te_2=te_1;
    te_1=t;
}

int dbasa,dbasb;
float tvu,tvd;

void calculate_pid()
{
	if(Tset>t_room) //当前温度小于设定温度
	{
		//dbasa=(int)(40+(112/(100.0-t_room))*(Tset-t_room));  //156
		dbasa=(int)(Tset*256/100);
		if(dbasa>255)  dbasa=255;
		tc_data=dbasa;
	}
	else
	{
		dbasb=(int)(128-(112/(t_room+10))*(t_room-Tset));  //408
		if(dbasb<0)  dbasb=0;
	}
	tvu=(100-Tset)*0.07+1; 
	tvd=1+Tset*0.07;
	tc_data=dbasa;
}



void output_t_room()
{
	 CS2=(uchar)(t_room * 256) / 100;
} 